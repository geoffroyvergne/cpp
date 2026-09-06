#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "ImageLoader.h"

#include <stdexcept>

Image ImageLoader::load(const std::string& filename)
{
    int width;
    int height;
    int channels;

    unsigned char* data = stbi_load(
        filename.c_str(),
        &width,
        &height,
        &channels,
        3
    );

    if (!data)
    {
        throw std::runtime_error(
            "Cannot load image: " + filename
        );
    }

    Image image;
    image.width = width;
    image.height = height;

    image.pixels.assign(
        data,
        data + (width * height * 3)
    );

    stbi_image_free(data);

    return image;
}
