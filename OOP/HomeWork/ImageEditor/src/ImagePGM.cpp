#include "ImagePGM.h"
#include "Helpers.h"

static const char *const MODE = "P2";

static const int MAX_PER_LINE = 15;

ImagePGM::ImagePGM(const Dimensions &dimensions,
                   const std::shared_ptr<Vector<Color>> &colorData,
                   const char *filename,
                   unsigned maxValue)
: Image(dimensions, colorData, filename)
, maxValue(maxValue) {
    analyzeColors(colorData);
}

void ImagePGM::analyzeColors(const std::shared_ptr<Vector<Color>> &colorData) {
    setType(MONOCHROME);
    for (unsigned i = 0; i < colorData->getSize(); ++i) {
        if(!(*colorData)[i].isMonochrome()) {
            setType(GRAY_SCALE);
            break;
        }
    }
}

bool ImagePGM::actualSave(std::ostream &ostream) const {
    Dimensions dim = getDimensions();
    ostream << MODE << std::endl;
    ostream << dim.width << " " << dim.height << std::endl;
    ostream << maxValue << std::endl;

    for (unsigned i = 0; i < dim.pixelCount(); ++i) {
        unsigned mapped = Helpers::mapRanges(0, Color::MAX_VALUE, 0, maxValue, (*colorData)[i].r());
        ostream << mapped << " ";
        if(i % MAX_PER_LINE == 0 && i != 0) {
            ostream << std::endl;
        }
    }

    ostream << std::endl;
    return true;
}
