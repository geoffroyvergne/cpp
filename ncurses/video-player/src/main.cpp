#include "VideoDecoder.hpp"
#include "AsciiRenderer.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <iomanip>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr
            << "Usage: "
            << argv[0]
            << " <video-file>"
            << std::endl;

        return 1;
    }

    // ------------------------------------------------------------
    // Decoder
    // ------------------------------------------------------------

    VideoDecoder decoder(argv[1]);

    if (!decoder.open())
    {
        return 1;
    }

    std::cout
        << "Video: "
        << decoder.getWidth()
        << "x"
        << decoder.getHeight()
        << std::endl;

    std::cout
        << "FPS: "
        << decoder.getFPS()
        << std::endl;

    std::cout
        << "Duration: "
        << decoder.getDuration()
        << " seconds"
        << std::endl;

    // ------------------------------------------------------------
    // Renderer
    // ------------------------------------------------------------

    AsciiRenderer renderer;

    renderer.initialize();

    // ------------------------------------------------------------
    // Playback state
    // ------------------------------------------------------------

    bool paused = false;

    double speed = 1.0;

    constexpr double seekAmount = 5.0;

    using Clock =
        std::chrono::steady_clock;

    auto playbackStart =
        Clock::now();

    double timelineStartPTS =
        0.0;

    bool firstFrame = true;

    // ------------------------------------------------------------
    // Main loop
    // ------------------------------------------------------------

    while (!renderer.shouldQuit())
    {
        // --------------------------------------------------------
        // Keyboard / controls
        // --------------------------------------------------------

        if (renderer.consumePauseToggle())
        {
            paused = !paused;

            if (!paused)
            {
                // Restart timing reference when resuming.
                playbackStart =
                    Clock::now();

                timelineStartPTS =
                    decoder.getCurrentPTS();
            }
        }

        if (renderer.consumeSpeedIncrease())
        {
            speed =
                std::min(
                    4.0,
                    speed * 2.0
                );

            playbackStart =
                Clock::now();

            timelineStartPTS =
                decoder.getCurrentPTS();
        }

        if (renderer.consumeSpeedDecrease())
        {
            speed =
                std::max(
                    0.25,
                    speed / 2.0
                );

            playbackStart =
                Clock::now();

            timelineStartPTS =
                decoder.getCurrentPTS();
        }

        if (renderer.consumeSpeedReset())
        {
            speed = 1.0;

            playbackStart =
                Clock::now();

            timelineStartPTS =
                decoder.getCurrentPTS();
        }

        // --------------------------------------------------------
        // Seek backward
        // --------------------------------------------------------

        if (renderer.consumeSeekBackward())
        {
            double target =
                decoder.getCurrentPTS() -
                seekAmount;

            if (decoder.seekTo(target))
            {
                playbackStart =
                    Clock::now();

                timelineStartPTS =
                    decoder.getCurrentPTS();
            }
        }

        // --------------------------------------------------------
        // Seek forward
        // --------------------------------------------------------

        if (renderer.consumeSeekForward())
        {
            double target =
                decoder.getCurrentPTS() +
                seekAmount;

            if (decoder.seekTo(target))
            {
                playbackStart =
                    Clock::now();

                timelineStartPTS =
                    decoder.getCurrentPTS();
            }
        }

        // --------------------------------------------------------
        // Pause
        // --------------------------------------------------------

        if (paused)
        {
            // We still need to render the current frame and
            // process keyboard input.
            //
            // readFrame() is intentionally not called here.

            renderer.render(
                decoder.getFrame(),
                decoder.getWidth(),
                decoder.getHeight()
            );

            std::this_thread::sleep_for(
                std::chrono::milliseconds(20)
            );

            continue;
        }

        // --------------------------------------------------------
        // Decode next frame
        // --------------------------------------------------------

        if (!decoder.readFrame())
        {
            break;
        }

        double pts =
            decoder.getCurrentPTS();

        // --------------------------------------------------------
        // First frame
        // --------------------------------------------------------

        if (firstFrame)
        {
            firstFrame = false;

            timelineStartPTS =
                pts;

            playbackStart =
                Clock::now();
        }

        // --------------------------------------------------------
        // Calculate target presentation time.
        //
        // speed = 1.0
        //     normal playback
        //
        // speed = 2.0
        //     twice as fast
        //
        // speed = 0.5
        //     half speed
        // --------------------------------------------------------

        double videoTime =
            pts -
            timelineStartPTS;

        double realTime =
            videoTime /
            speed;

        auto targetTime =
            playbackStart +
            std::chrono::duration_cast<
                Clock::duration
            >(
                std::chrono::duration<double>(
                    realTime
                )
            );

        // --------------------------------------------------------
        // Wait until presentation time
        // --------------------------------------------------------

        auto now =
            Clock::now();

        if (targetTime > now)
        {
            std::this_thread::sleep_until(
                targetTime
            );
        }

        // --------------------------------------------------------
        // Render
        // --------------------------------------------------------

        renderer.render(
            decoder.getFrame(),
            decoder.getWidth(),
            decoder.getHeight()
        );

        // --------------------------------------------------------
        // If the renderer is slower than the video, we don't
        // sleep. The next iteration will immediately decode the
        // next frame.
        //
        // This naturally lets us catch up instead of accumulating
        // an ever-growing delay.
        // --------------------------------------------------------
    }

    renderer.shutdown();

    return 0;
}