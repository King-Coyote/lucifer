#pragma once

#include <Magick++.h>
#include "RenderPixel.h"

using namespace std;

class ImageConverter {

public:
    void convertImage(string filename, unsigned int w, unsigned int h, Pixel** pixels);

};