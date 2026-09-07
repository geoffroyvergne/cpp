#include "VideoDecoder.hpp"
#include "AsciiRenderer.hpp"

#include <ncurses.h>

#include <iostream>

#include <chrono>
#include <thread>


int main(int argc, char* argv[])
{
    // ---------------------------------------------
    // Check arguments
    // ---------------------------------------------

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
    // Initialize ncurses
    // ---------------------------------------------

    AsciiRenderer renderer;

    renderer.initialize();


    // ---------------------------------------------
    // Frame timing
    // ---------------------------------------------

    double fps = decoder.getFPS();

    auto frameDuration =
        std::chrono::duration<double>(
            1.0 / fps
        );


    // ---------------------------------------------
    // Playback loop
    // ---------------------------------------------

    while (true)
    {
        auto frameStart =
            std::chrono::steady_clock::now();


        // Check keyboard

        int key = getch();

        if (key == 'q' ||
            key == 'Q' ||
            key == 27)
        {
            break;
        }


        // Decode next frame

        if (!decoder.readFrame())
        {
            break;
        }


        // Render

        renderer.render(
            decoder.getFrame(),
            decoder.getWidth(),
            decoder.getHeight()
        );


        // -----------------------------------------
        // Maintain FPS
        // -----------------------------------------

        auto elapsed =
            std::chrono::steady_clock::now()
            - frameStart;


        auto remaining =
            frameDuration -
            elapsed;


        if (remaining.count() > 0)
        {
            std::this_thread::sleep_for(
                remaining
            );
        }
    }


    // ---------------------------------------------
    // Cleanup
    // ---------------------------------------------

    renderer.shutdown();


    return 0;
}