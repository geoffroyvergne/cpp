#include "VideoDecoder.hpp"
#include "AsciiRenderer.hpp"

#include <iostream>
#include <chrono>
#include <thread>

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


    const char* filename = argv[1];


    // ---------------------------------------------
    // Open video
    // ---------------------------------------------

    VideoDecoder decoder(filename);

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


    // ---------------------------------------------
    // Initialize renderer
    // ---------------------------------------------

    AsciiRenderer renderer;

    renderer.initialize();


    // ---------------------------------------------
    // Playback timing
    // ---------------------------------------------

    const double fps =
        decoder.getFPS();

    const double frameTime =
        1.0 / fps;


    auto nextFrameTime =
        std::chrono::steady_clock::now();


    // ---------------------------------------------
    // Main playback loop
    // ---------------------------------------------

    while (!renderer.shouldQuit())
    {
        /*
         * Decode frame.
         */

        if (!decoder.readFrame())
        {
            break;
        }


        /*
         * Render frame.
         */

        renderer.render(
            decoder.getFrame(),
            decoder.getWidth(),
            decoder.getHeight()
        );


        if (renderer.shouldQuit())
            break;


        /*
         * Schedule next frame.
         *
         * Instead of:
         *
         *   sleep(frameTime)
         *
         * we maintain an absolute deadline.
         *
         * This prevents small timing errors from
         * accumulating over the duration of the video.
         */

        nextFrameTime +=
            std::chrono::duration_cast<
                std::chrono::steady_clock::duration
            >(
                std::chrono::duration<double>(
                    frameTime
                )
            );


        auto now =
            std::chrono::steady_clock::now();


        if (nextFrameTime > now)
        {
            std::this_thread::sleep_until(
                nextFrameTime
            );
        }
        else
        {
            /*
             * Rendering took longer than one frame.
             *
             * Don't sleep: immediately continue.
             */

            nextFrameTime = now;
        }
    }


    // ---------------------------------------------
    // Cleanup
    // ---------------------------------------------

    renderer.shutdown();


    return 0;
}