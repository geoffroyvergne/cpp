#include "AsciiRenderer.h"

#include <algorithm>
#include <cmath>

namespace
{
    constexpr char ASCII_RAMP[] = "@%#*+=-:. ";
    constexpr int RAMP_SIZE = sizeof(ASCII_RAMP) - 1;

    constexpr double CHAR_ASPECT_RATIO = 0.5;

    /*
     * Convert RGB to perceived luminance.
     */
    uint8_t grayscale(const uint8_t* pixel)
    {
        const double r = pixel[0];
        const double g = pixel[1];
        const double b = pixel[2];

        return static_cast<uint8_t>(
            0.2126 * r +
            0.7152 * g +
            0.0722 * b
        );
    }

    /*
     * Average a rectangular region of the source image.
     */
    uint8_t averageGrayscale(
        const Image& image,
        int x0,
        int x1,
        int y0,
        int y1)
    {
        double total = 0.0;
        int count = 0;

        x0 = std::clamp(x0, 0, image.width);
        x1 = std::clamp(x1, 0, image.width);
        y0 = std::clamp(y0, 0, image.height);
        y1 = std::clamp(y1, 0, image.height);

        for (int y = y0; y < y1; ++y)
        {
            for (int x = x0; x < x1; ++x)
            {
                total += grayscale(
                    image.pixel(x, y)
                );

                ++count;
            }
        }

        if (count == 0)
            return 0;

        return static_cast<uint8_t>(
            total / count
        );
    }

    /*
     * Convert grayscale into a thresholded value.
     *
     * We deliberately use several thresholds rather
     * than a single 128 threshold.
     *
     * The small offset creates a Bayer-like ordered
     * dithering effect.
     */
    bool pixelOn(
        uint8_t gray,
        int x,
        int y)
    {
        /*
         * 4x4 Bayer matrix.
         *
         * Values are distributed between 0 and 15.
         */
        constexpr int BAYER[4][4] =
        {
            {  0,  8,  2, 10 },
            { 12,  4, 14,  6 },
            {  3, 11,  1,  9 },
            { 15,  7, 13,  5 }
        };

        const int threshold =
            BAYER[y % 4][x % 4] * 16;

        return gray > threshold;
    }
}

std::vector<std::string> AsciiRenderer::render(
    const Image& image,
    int maxWidth,
    int maxHeight,
    const RenderConfig& config)
{
    if (image.width <= 0 || image.height <= 0)
        return {};

    if (maxWidth <= 0 || maxHeight <= 0)
        return {};

    /*
     * =========================================================
     * ASCII MODE
     * =========================================================
     */

    if (config.mode == RenderMode::ASCII)
    {
        const double imageAspect =
            static_cast<double>(image.width) /
            static_cast<double>(image.height);

        double fitWidth =
            static_cast<double>(maxWidth);

        double fitHeight =
            fitWidth /
            imageAspect *
            CHAR_ASPECT_RATIO;

        if (fitHeight > maxHeight)
        {
            fitHeight =
                static_cast<double>(maxHeight);

            fitWidth =
                fitHeight *
                imageAspect /
                CHAR_ASPECT_RATIO;
        }

        double outputWidth =
            fitWidth * config.size;

        double outputHeight =
            fitHeight * config.size;

        int width = std::max(
            1,
            static_cast<int>(
                std::round(outputWidth)
            )
        );

        int height = std::max(
            1,
            static_cast<int>(
                std::round(outputHeight)
            )
        );

        width = std::min(
            width,
            maxWidth
        );

        height = std::min(
            height,
            maxHeight
        );

        std::vector<std::string> result(height);

        for (int y = 0; y < height; ++y)
        {
            result[y].reserve(width);

            int y0 =
                y * image.height / height;

            int y1 =
                (y + 1) * image.height / height;

            y1 = std::max(
                y1,
                y0 + 1
            );

            y1 = std::min(
                y1,
                image.height
            );

            for (int x = 0; x < width; ++x)
            {
                int x0 =
                    x * image.width / width;

                int x1 =
                    (x + 1) * image.width / width;

                x1 = std::max(
                    x1,
                    x0 + 1
                );

                x1 = std::min(
                    x1,
                    image.width
                );

                uint8_t gray =
                    averageGrayscale(
                        image,
                        x0,
                        x1,
                        y0,
                        y1
                    );

                double value =
                    gray * config.brightness;

                value = std::clamp(
                    value,
                    0.0,
                    255.0
                );

                int index =
                    static_cast<int>(
                        value *
                        (RAMP_SIZE - 1) /
                        255.0
                    );

                result[y].push_back(
                    ASCII_RAMP[index]
                );
            }
        }

        return result;
    }

    /*
     * =========================================================
     * RECTANGLE MODE
     * =========================================================
     *
     * One terminal character represents two vertical
     * image samples:
     *
     *       upper   lower
     *
     * █       ON      ON
     * ▀       ON      OFF
     * ▄       OFF     ON
     * space   OFF     OFF
     *
     * Ordered dithering is used to preserve grayscale
     * information instead of simply using gray >= 128.
     */

    constexpr double RECTANGLE_ASPECT_RATIO = 0.25;

    const double imageAspect =
        static_cast<double>(image.width) /
        static_cast<double>(image.height);

    double fitWidth =
        static_cast<double>(maxWidth);

    double fitHeight =
        fitWidth /
        imageAspect *
        RECTANGLE_ASPECT_RATIO;

    if (fitHeight > maxHeight)
    {
        fitHeight =
            static_cast<double>(maxHeight);

        fitWidth =
            fitHeight *
            imageAspect /
            RECTANGLE_ASPECT_RATIO;
    }

    double outputWidth =
        fitWidth * config.size;

    double outputHeight =
        fitHeight * config.size;

    int width = std::max(
        1,
        static_cast<int>(
            std::round(outputWidth)
        )
    );

    int height = std::max(
        1,
        static_cast<int>(
            std::round(outputHeight)
        )
    );

    width = std::min(
        width,
        maxWidth
    );

    height = std::min(
        height,
        maxHeight
    );

    /*
     * Each terminal row represents two source-image rows.
     */
    const int sourceHeight =
        std::max(
            2,
            height * 2
        );

    std::vector<std::string> result(height);

    for (int y = 0; y < height; ++y)
    {
        result[y].reserve(width);

        /*
         * Source Y coordinates for the two vertical
         * samples represented by this character.
         */
        int upperY =
            (y * image.height) /
            sourceHeight;

        int lowerY =
            ((y * 2 + 1) * image.height) /
            sourceHeight;

        upperY = std::clamp(
            upperY,
            0,
            image.height - 1
        );

        lowerY = std::clamp(
            lowerY,
            0,
            image.height - 1
        );

        for (int x = 0; x < width; ++x)
        {
            int x0 =
                x * image.width / width;

            int x1 =
                (x + 1) * image.width / width;

            x1 = std::max(
                x1,
                x0 + 1
            );

            x1 = std::min(
                x1,
                image.width
            );

            /*
             * Average the horizontal source region.
             */
            uint8_t upperGray =
                averageGrayscale(
                    image,
                    x0,
                    x1,
                    upperY,
                    upperY + 1
                );

            uint8_t lowerGray =
                averageGrayscale(
                    image,
                    x0,
                    x1,
                    lowerY,
                    lowerY + 1
                );

            /*
             * Apply brightness.
             */
            double upperValue =
                std::clamp(
                    upperGray * config.brightness,
                    0.0,
                    255.0
                );

            double lowerValue =
                std::clamp(
                    lowerGray * config.brightness,
                    0.0,
                    255.0
                );

            /*
             * Dither each vertical sample independently.
             *
             * This preserves much more tonal information
             * than a simple 128 threshold.
             */
            bool upperOn =
                pixelOn(
                    static_cast<uint8_t>(upperValue),
                    x,
                    y * 2
                );

            bool lowerOn =
                pixelOn(
                    static_cast<uint8_t>(lowerValue),
                    x,
                    y * 2 + 1
                );

            /*
             * Convert the two samples into one Unicode
             * half-block character.
             */
            if (upperOn && lowerOn)
            {
                result[y] += "█";
            }
            else if (upperOn)
            {
                result[y] += "▀";
            }
            else if (lowerOn)
            {
                result[y] += "▄";
            }
            else
            {
                result[y] += " ";
            }
        }
    }

    return result;
}