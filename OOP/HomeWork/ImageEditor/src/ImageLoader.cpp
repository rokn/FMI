#include <fstream>
#include <cstring>
#include <ImagePBM.h>
#include <ImagePGM.h>
#include <ImagePPM.h>
#include <Helpers.h>
#include "ImageLoader.h"

static ImageLoader::Format getFormat(const char *type);
static unsigned readValWithMax(std::ifstream& file, unsigned maxValue);

Image* ImageLoader::loadImage(const char *filename) {
    std::ifstream file(filename);

    if(!file) {
        return nullptr;
    }

    char type[3];
    file >> type;

    Format format = getFormat(type);

    Dimensions dimensions;
    file >> dimensions.width;
    file >> dimensions.height;

    unsigned maxValue = 0;

    if(format != PBM) {
        file >> maxValue;
    }

    Vector<Color>* data = new Vector<Color>(dimensions.pixelCount());

    for (unsigned i = 0; i < dimensions.pixelCount() && file; ++i) {
        unsigned val = 0;
        switch(format) {
            case PBM:
                file >> val;
                data->pushBack(val ? Color(Color::WHITE) : Color(Color::BLACK));
                break;
            case PGM:
                val = readValWithMax(file, maxValue);
                data->pushBack(Color(val, val, val));
                break;
            case PPM:
                Color c;

                val = readValWithMax(file, maxValue);
                c.setR(val);
                val = readValWithMax(file, maxValue);
                c.setG(val);
                val = readValWithMax(file, maxValue);
                c.setB(val);

                data->pushBack(c);
                break;
        }
    }

    file.close();

    Image* result = nullptr;

    switch(format) {
        case PBM:
            result = new ImagePBM(dimensions, std::shared_ptr<Vector<Color>>(data), filename);
            break;
        case PGM:;
            result = new ImagePGM(dimensions, std::shared_ptr<Vector<Color>>(data), filename, maxValue);
            break;
        case PPM:;
            result = new ImagePPM(dimensions, std::shared_ptr<Vector<Color>>(data), filename, maxValue);
            break;
    }

    return result;
}

ImageLoader::Format getFormat(const char *type) {
    if(!strcmp(type, "P1")) {
        return ImageLoader::PBM;
    } else if (!strcmp(type, "P2")) {
        return ImageLoader::PGM;
    } else if (!strcmp(type, "P3")) {
        return ImageLoader::PPM;
    }
}

static unsigned readValWithMax(std::ifstream& file, unsigned maxValue) {
    unsigned val;
    file >> val;
    val = Helpers::mapRanges(0, maxValue, 0, Color::MAX_VALUE, val);
    return val;
}
