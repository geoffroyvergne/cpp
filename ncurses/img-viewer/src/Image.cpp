#include "Image.h"

const uint8_t* Image::pixel(int x, int y) const
{
    return &pixels[(y * width + x) * 3];
}
