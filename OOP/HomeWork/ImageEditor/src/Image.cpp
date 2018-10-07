#include "Image.h"
#include <cstring>
#include <fstream>
#include "Helpers.h"

static const unsigned DIRECTION_COUNT = 4;

static const int MAX_EXT = 255;

Image::Image(Dimensions dimensions, const std::shared_ptr<Vector<Color>> &colorData, const char *filename)
: rotation(NONE)
, colorData(colorData)
, filename(nullptr)
, dimensions(dimensions)
, type(COLOR) {
    this->filename = new char[strlen(filename)];
    strcpy(this->filename, filename);
}

void Image::rotate(RotationDirection direction) {
    rotation = (Rotation)Helpers::mod(rotation + direction, DIRECTION_COUNT);
}

void Image::setType(ImageType type) {
    this->type = type;
}

Rotation Image::getRotation() const {
    return rotation;
}

Dimensions Image::getDimensions() const {
    return dimensions;
}

void Image::makeMonochrome() {
    if(type == MONOCHROME) {
        return;
    }

    for (unsigned i = 0; i < dimensions.pixelCount(); ++i) {
        (*colorData)[i].toMonochrome();
    }

    setType(MONOCHROME);

}

void Image::makeGrayScale() {
    if(type == GRAY_SCALE || type == MONOCHROME) {
        return;
    }

    for (unsigned i = 0; i < dimensions.pixelCount(); ++i) {
        (*colorData)[i].toGrayScale();
    }

    setType(GRAY_SCALE);
}

void Image::makeNegative() {
    for (unsigned i = 0; i < dimensions.pixelCount(); ++i) {
        (*colorData)[i].invert();
    }
}

void Image::performRotation() {
    Dimensions newDimensions;

    switch(rotation) {
        case NONE:
            return;
        case DOWN:
            newDimensions.width = dimensions.width;
            newDimensions.height = dimensions.height;
            break;
        case RIGHT:
        case LEFT:
            newDimensions.width = dimensions.height;
            newDimensions.height = dimensions.width;
            break;
    }

    Vector<Color>* newData = new Vector<Color>(newDimensions.pixelCount());

    for (unsigned x = 0; x < newDimensions.width; ++x) {
        for (unsigned y = 0; y < newDimensions.height; ++y) {
            unsigned oldIndex = getOldIndexRotated(x, y);
            (*newData)[getIndex(x,y,newDimensions.width)] = (*colorData)[oldIndex];
        }
    }

    colorData.reset(newData);
    dimensions = newDimensions;
}

unsigned Image::getIndex(unsigned x, unsigned y, unsigned width) {
    return y*width + x;
}

unsigned Image::getOldIndexRotated(unsigned x, unsigned y) {
    switch(rotation) {
        case NONE:
            return getIndex(x, y, dimensions.width);
        case RIGHT:
            return getIndex(y, (dimensions.height - 1) - x, dimensions.width);
        case DOWN:
            return getIndex((dimensions.width - 1) - x, (dimensions.height - 1) - y, dimensions.width);
        case LEFT:
            return getIndex((dimensions.width - 1) - y, x, dimensions.width);
    }
}

const char *Image::getFilename() const {
    return filename;
}

const char *Image::getNewFilename(const char *suffix) const {
    char* newFilename = new char[strlen(filename) + strlen(suffix) + 1];
    char* ext = new char[MAX_EXT];
    const char* withoutExt = Helpers::getWithoutExtension(filename, ext);

    strcpy(newFilename, withoutExt);
    strcat(newFilename, suffix);
    strcat(newFilename, ext);

    delete[] ext;
    delete[] withoutExt;

    return filename;
}

bool Image::save(const char* suffix) {
    performRotation();

    std::ofstream file(getNewFilename(suffix));

    if(!file) {
        return false;
    }

    return actualSave(file);

}


