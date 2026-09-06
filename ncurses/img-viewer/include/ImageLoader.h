#pragma once

#include <string>
#include "Image.h"

class ImageLoader
{
    public:
        static Image load(const std::string& filename);
};
