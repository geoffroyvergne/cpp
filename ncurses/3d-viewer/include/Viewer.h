#pragma once

#include <string>

#include "Mesh.h"
#include "Renderer.h"

class Viewer
{
public:
    explicit Viewer(const Mesh& mesh);

    void run();

private:
    const Mesh& mesh_;

    Renderer renderer_;

    float rotationX_;
    float rotationY_;
    float rotationZ_;

    float zoom_;

    void reset();

    void handleInput(int key);

    void drawInterface();

    void resize();
};
