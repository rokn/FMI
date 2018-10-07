#ifndef IMAGEEDITOR_IMAGELOADER_H
#define IMAGEEDITOR_IMAGELOADER_H


#include "Image.h"

namespace ImageLoader {
    enum Format{
        PBM,
        PGM,
        PPM,
    };

    Image* loadImage(const char* filename);

};


#endif //IMAGEEDITOR_IMAGELOADER_H
