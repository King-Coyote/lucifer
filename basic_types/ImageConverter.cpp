#include "ImageConverter.h"

using namespace Magick;

void ImageConverter::convertImage(const string filename, const unsigned int w, const unsigned int h, Pixel** pixels) {

    Image image = Image(Geometry(w, h), Color("magenta"));
    image.magick("png");

    // do thangs
    for (unsigned int j = 0; j<h; j++) {
        for (unsigned int i = 0; i<w; i++) {
            image.pixelColor(i, j, Color(
                (pixels[i][j].r) * QuantumRange,
                (pixels[i][j].g) * QuantumRange,
                (pixels[i][j].b) * QuantumRange,
                0
            ));
        }
    }

    image.write(filename);

}