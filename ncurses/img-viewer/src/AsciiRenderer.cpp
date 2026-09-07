#include "AsciiRenderer.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <utility>

namespace
{
    constexpr double CHAR_ASPECT_RATIO = 0.5;

    constexpr int COLOR_LEVELS = 16;

    /*
     * Convert an RGB pixel to grayscale.
     */
    uint8_t grayscale(
        uint8_t r,
        uint8_t g,
        uint8_t b)
    {
        return static_cast<uint8_t>(
            0.2126 * r +
            0.7152 * g +
            0.0722 * b
        );
    }

    /*
     * Average a horizontal range of pixels.
     */
    void averageRGB(
        const Image& image,
        int y,
        int x0,
        int x1,
        uint8_t& r,
        uint8_t& g,
        uint8_t& b)
    {
        uint64_t totalR = 0;
        uint64_t totalG = 0;
        uint64_t totalB = 0;

        int count = 0;

        for (int x = x0; x < x1; ++x)
        {
            const uint8_t* p =
                image.pixel(x, y);

            totalR += p[0];
            totalG += p[1];
            totalB += p[2];

            ++count;
        }

        if (count == 0)
        {
            r = 0;
            g = 0;
            b = 0;
            return;
        }

        r = static_cast<uint8_t>(
            totalR / count
        );

        g = static_cast<uint8_t>(
            totalG / count
        );

        b = static_cast<uint8_t>(
            totalB / count
        );
    }

    int grayscaleToLevel(
        uint8_t value)
    {
        return
            static_cast<int>(
                value *
                (COLOR_LEVELS - 1) /
                255
            );
    }
}

/*
 * ASCII renderer.
 */
std::vector<std::string> AsciiRenderer::render(
    const Image& image,
    int maxWidth,
    int maxHeight,
    const RenderConfig& config)
{
    std::vector<std::string> result;

    if (image.width <= 0 ||
        image.height <= 0 ||
        maxWidth <= 0 ||
        maxHeight <= 0)
    {
        return result;
    }

    /*
     * Character cells are approximately twice as high
     * as they are wide.
     *
     * CHAR_ASPECT_RATIO = width / height.
     */

    /*
     * First determine the largest image that fits.
     */
    int fitWidth = maxWidth;

    int fitHeight =
        static_cast<int>(
            image.height *
            fitWidth *
            CHAR_ASPECT_RATIO /
            static_cast<double>(image.width)
        );

    if (fitHeight > maxHeight)
    {
        fitHeight = maxHeight;

        fitWidth =
            static_cast<int>(
                image.width *
                fitHeight /
                static_cast<double>(image.height) /
                CHAR_ASPECT_RATIO
            );
    }

    fitWidth =
        std::max(1, fitWidth);

    fitHeight =
        std::max(1, fitHeight);

    /*
     * Apply zoom AFTER fitting.
     *
     * This is important:
     *
     * 1.0 -> maximum size
     * 0.9 -> 90%
     * 0.8 -> 80%
     * ...
     *
     * The zoom therefore cannot get lost when the
     * image is height-constrained.
     */
    int targetWidth =
        static_cast<int>(
            fitWidth * config.size
        );

    int targetHeight =
        static_cast<int>(
            fitHeight * config.size
        );

    targetWidth =
        std::max(1, targetWidth);

    targetHeight =
        std::max(1, targetHeight);

    /*
     * ASCII ramp from dark to light.
     */
    constexpr const char* RAMP =
        "@%#*+=-:. ";

    constexpr int RAMP_SIZE = 10;

    result.resize(targetHeight);

    for (int y = 0;
         y < targetHeight;
         ++y)
    {
        result[y].reserve(targetWidth);

        /*
         * Map terminal Y range to source image.
         */
        int y0 =
            (y * image.height) /
            targetHeight;

        int y1 =
            ((y + 1) * image.height) /
            targetHeight;

        y1 =
            std::max(
                y0 + 1,
                y1
            );

        y1 =
            std::min(
                image.height,
                y1
            );

        for (int x = 0;
             x < targetWidth;
             ++x)
        {
            int x0 =
                (x * image.width) /
                targetWidth;

            int x1 =
                ((x + 1) * image.width) /
                targetWidth;

            x1 =
                std::max(
                    x0 + 1,
                    x1
                );

            x1 =
                std::min(
                    image.width,
                    x1
                );

            uint64_t totalGray = 0;
            int count = 0;

            /*
             * Area-average the source pixels.
             */
            for (int sy = y0;
                 sy < y1;
                 ++sy)
            {
                for (int sx = x0;
                     sx < x1;
                     ++sx)
                {
                    const uint8_t* p =
                        image.pixel(sx, sy);

                    totalGray +=
                        grayscale(
                            p[0],
                            p[1],
                            p[2]
                        );

                    ++count;
                }
            }

            int gray =
                count > 0
                    ? static_cast<int>(
                          totalGray / count)
                    : 0;

            /*
             * Brightness adjustment.
             */
            gray =
                static_cast<int>(
                    gray * config.brightness
                );

            gray =
                std::clamp(
                    gray,
                    0,
                    255
                );

            /*
             * Convert to ASCII ramp.
             */
            int index =
                gray *
                (RAMP_SIZE - 1) /
                255;

            result[y] +=
                std::string(
                    1,
                    RAMP[index]
                
            );
        }
    }

    return result;
}

/*
 * Half-block / rectangle renderer.
 *
 * Each terminal character represents TWO vertical
 * image samples:
 *
 *      upper sample
 *           ↓
 *          ▀
 *           ↑
 *      lower sample
 *
 * The foreground color represents the upper half.
 * The background color represents the lower half.
 */
RenderedImage AsciiRenderer::renderColored(
    const Image& image,
    int maxWidth,
    int maxHeight,
    const RenderConfig& config)
{
    RenderedImage result;

    if (image.width <= 0 ||
        image.height <= 0 ||
        maxWidth <= 0 ||
        maxHeight <= 0)
    {
        return result;
    }

    /*
     * --------------------------------------------------
     * FIT IMAGE TO TERMINAL
     * --------------------------------------------------
     *
     * A terminal character cell is approximately
     * twice as high as it is wide.
     *
     * Since the half-block represents half a character
     * vertically, each terminal row represents two
     * image rows.
     */

    /*
     * First determine the maximum width.
     */
    int fitWidth = maxWidth;

    /*
     * Calculate corresponding terminal height.
     *
     * We use the terminal cell aspect ratio here,
     * not "two pixels per character", because two
     * half-blocks occupy the same physical character cell.
     */
    constexpr double TERMINAL_CELL_ASPECT = 0.5;

    int fitHeight =
        static_cast<int>(
            image.height *
            fitWidth *
            TERMINAL_CELL_ASPECT /
            static_cast<double>(image.width)
        );

    /*
     * If height is the limiting dimension,
     * calculate width from height.
     */
    if (fitHeight > maxHeight)
    {
        fitHeight = maxHeight;

        fitWidth =
            static_cast<int>(
                image.width *
                fitHeight /
                static_cast<double>(image.height) /
                TERMINAL_CELL_ASPECT
            );
    }

    fitWidth =
        std::max(1, fitWidth);

    fitHeight =
        std::max(1, fitHeight);

    /*
     * Apply zoom AFTER the terminal-fit calculation.
     */
    int targetWidth =
        static_cast<int>(
            fitWidth * config.size
        );

    int targetHeight =
        static_cast<int>(
            fitHeight * config.size
        );

    targetWidth =
        std::max(1, targetWidth);

    targetHeight =
        std::max(1, targetHeight);

    /*
     * --------------------------------------------------
     * RENDER
     * --------------------------------------------------
     */

    result.resize(targetHeight);

    for (int y = 0;
         y < targetHeight;
         ++y)
    {
        result[y].reserve(targetWidth);

        /*
         * Each terminal row contains TWO vertical
         * samples.
         *
         * The source coordinate is based on the
         * physical vertical position represented by
         * this half-block cell.
         */

        int upperY =
            static_cast<int>(
                (2.0 * y) *
                image.height /
                (2.0 * targetHeight)
            );

        int lowerY =
            static_cast<int>(
                (2.0 * y + 1.0) *
                image.height /
                (2.0 * targetHeight)
            );

        upperY =
            std::clamp(
                upperY,
                0,
                image.height - 1
            );

        lowerY =
            std::clamp(
                lowerY,
                0,
                image.height - 1
            );

        for (int x = 0;
             x < targetWidth;
             ++x)
        {
            /*
             * Map terminal column to a source
             * horizontal range.
             */
            int x0 =
                static_cast<int>(
                    x *
                    image.width /
                    static_cast<double>(
                        targetWidth
                    )
                );

            int x1 =
                static_cast<int>(
                    (x + 1) *
                    image.width /
                    static_cast<double>(
                        targetWidth
                    )
                );

            x0 =
                std::clamp(
                    x0,
                    0,
                    image.width - 1
                );

            x1 =
                std::clamp(
                    x1,
                    x0 + 1,
                    image.width
                );

            /*
             * Average the upper and lower source rows.
             */
            uint8_t upperR;
            uint8_t upperG;
            uint8_t upperB;

            uint8_t lowerR;
            uint8_t lowerG;
            uint8_t lowerB;

            averageRGB(
                image,
                upperY,
                x0,
                x1,
                upperR,
                upperG,
                upperB
            );

            averageRGB(
                image,
                lowerY,
                x0,
                x1,
                lowerR,
                lowerG,
                lowerB
            );

            /*
             * Convert to grayscale.
             */
            int upperGray =
                grayscale(
                    upperR,
                    upperG,
                    upperB
                );

            int lowerGray =
                grayscale(
                    lowerR,
                    lowerG,
                    lowerB
                );

            /*
             * Brightness.
             */
            upperGray =
                static_cast<int>(
                    upperGray *
                    config.brightness
                );

            lowerGray =
                static_cast<int>(
                    lowerGray *
                    config.brightness
                );

            upperGray =
                std::clamp(
                    upperGray,
                    0,
                    255
                );

            lowerGray =
                std::clamp(
                    lowerGray,
                    0,
                    255
                );

            /*
             * Quantize to 16 grayscale levels.
             */
            int upperLevel =
                grayscaleToLevel(
                    static_cast<uint8_t>(
                        upperGray
                    )
                );

            int lowerLevel =
                grayscaleToLevel(
                    static_cast<uint8_t>(
                        lowerGray
                    )
                );

            /*
             * Encode both colors in one ncurses
             * color pair.
             *
             * 16 x 16 = 256 combinations.
             *
             * Pair 0 is reserved by ncurses, so:
             *
             * 1 + upper * 16 + lower
             */
            int colorPair =
                1 +
                upperLevel *
                    COLOR_LEVELS +
                lowerLevel;

            /*
             * ncurses on macOS normally provides
             * 256 color-pair slots:
             *
             * 0 ... 255
             *
             * Clamp the final combination.
             */
            colorPair =
                std::min(
                    colorPair,
                    255
                );

            RenderCell cell;

            /*
             * ▀:
             *
             * foreground = upper half
             * background = lower half
             */
            cell.character = "▀";
            cell.colorPair = colorPair;

            result[y].push_back(
                std::move(cell)
            );
        }
    }

    return result;
}