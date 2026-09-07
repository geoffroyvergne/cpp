#include "VideoDecoder.hpp"
#include "AsciiRenderer.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

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

    AsciiRenderer renderer;

    renderer.initialize();

    bool paused = false;

    double speed = 1.0;

    constexpr double shortSeekAmount = 5.0;
    constexpr double longSeekAmount = 30.0;

    using Clock =
        std::chrono::steady_clock;

    auto playbackStart =
        Clock::now();

    double timelineStartPTS =
        0.0;

    bool firstFrame = true;

    while (!renderer.shouldQuit())
    {
        /*
         * Read keyboard input once per loop.
         *
         * Input is no longer handled from inside
         * render(), which makes the control flow
         * much more predictable.
         */
        renderer.pollInput();

        if (renderer.shouldQuit())
            break;

        /*
         * Pause / Play
         */
        if (renderer.consumePauseToggle())
        {
            paused = !paused;

            if (!paused)
            {
                /*
                 * Restart the wall-clock reference
                 * when playback resumes.
                 */
                playbackStart =
                    Clock::now();

                timelineStartPTS =
                    decoder.getCurrentPTS();
            }
        }

        /*
         * Speed increase.
         *
         * 1x -> 2x -> 4x
         */
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

        /*
         * Speed decrease.
         *
         * 1x -> 0.5x -> 0.25x
         */
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

        /*
         * Reset speed.
         */
        if (renderer.consumeSpeedReset())
        {
            speed = 1.0;

            playbackStart =
                Clock::now();

            timelineStartPTS =
                decoder.getCurrentPTS();
        }

        /*
         * Short backward seek: -5 seconds
         */
        if (renderer.consumeSeekBackward())
        {
            double target =
                decoder.getCurrentPTS() -
                shortSeekAmount;

            if (decoder.seekTo(target))
            {
                playbackStart =
                    Clock::now();

                timelineStartPTS =
                    decoder.getCurrentPTS();

                firstFrame = false;
            }
        }

        /*
         * Short forward seek: +5 seconds
         */
        if (renderer.consumeSeekForward())
        {
            double target =
                decoder.getCurrentPTS() +
                shortSeekAmount;

            if (decoder.seekTo(target))
            {
                playbackStart =
                    Clock::now();

                timelineStartPTS =
                    decoder.getCurrentPTS();

                firstFrame = false;
            }
        }

        /*
         * Long backward seek: -30 seconds
         */
        if (renderer.consumeLongSeekBackward())
        {
            double target =
                decoder.getCurrentPTS() -
                longSeekAmount;

            if (decoder.seekTo(target))
            {
                playbackStart =
                    Clock::now();

                timelineStartPTS =
                    decoder.getCurrentPTS();

                firstFrame = false;
            }
        }

        /*
         * Long forward seek: +30 seconds
         */
        if (renderer.consumeLongSeekForward())
        {
            double target =
                decoder.getCurrentPTS() +
                longSeekAmount;

            if (decoder.seekTo(target))
            {
                playbackStart =
                    Clock::now();

                timelineStartPTS =
                    decoder.getCurrentPTS();

                firstFrame = false;
            }
        }

        /*
         * While paused we keep displaying the current
         * frame and the status information.
         */
        if (paused)
        {
            renderer.render(
                decoder.getFrame(),
                decoder.getWidth(),
                decoder.getHeight(),
                decoder.getCurrentPTS(),
                decoder.getDuration(),
                speed,
                true
            );

            std::this_thread::sleep_for(
                std::chrono::milliseconds(20)
            );

            continue;
        }

        /*
         * Decode next frame.
         */
        if (!decoder.readFrame())
        {
            break;
        }

        double pts =
            decoder.getCurrentPTS();

        /*
         * First frame establishes the timing reference.
         */
        if (firstFrame)
        {
            firstFrame = false;

            timelineStartPTS =
                pts;

            playbackStart =
                Clock::now();
        }

        /*
         * Time elapsed inside the video.
         */
        double videoTime =
            pts -
            timelineStartPTS;

        /*
         * Convert video time according to playback speed.
         *
         * At 2x, 10 seconds of video take 5 seconds
         * of real time.
         */
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

        /*
         * Wait until this frame should be displayed.
         */
        auto now =
            Clock::now();

        if (targetTime > now)
        {
            std::this_thread::sleep_until(
                targetTime
            );
        }

        /*
         * Render frame + UI.
         */
        renderer.render(
            decoder.getFrame(),
            decoder.getWidth(),
            decoder.getHeight(),
            pts,
            decoder.getDuration(),
            speed,
            false
        );
    }

    renderer.shutdown();

    return 0;
}
