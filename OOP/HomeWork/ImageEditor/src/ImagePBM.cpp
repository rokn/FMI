#include "ImagePBM.h"

static const char *const MODE = "P1";

static const int MAX_PER_LINE = 35;

ImagePBM::ImagePBM(const Dimensions &dimensions, const std::shared_ptr<Vector<Color>> &colorData, const char *filename)
: Image(dimensions, colorData, filename) {
    setType(MONOCHROME);
}

bool ImagePBM::actualSave(std::ostream &ostream) const {
    Dimensions dim = getDimensions();
    ostream << MODE << std::endl;
    ostream << dim.width << " " << dim.height << std::endl;

    for (unsigned i = 0; i < dim.pixelCount(); ++i) {
        if((*colorData)[i].r() == 255) {
            ostream << "1";
        } else {
            ostream << "0";
        }

        ostream << " ";

        if(i % MAX_PER_LINE == 0 && i != 0) {
            ostream << std::endl;
        }
    }

    ostream << std::endl;
    return true;
}
