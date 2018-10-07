#include "Helpers.h"
#include "ImagePPM.h"
#include "ImageStructures.h"

static const char *const MODE = "P3";

static const int MAX_PER_LINE = 5;

ImagePPM::ImagePPM(const Dimensions &dimensions,
                   const std::shared_ptr<Vector<Color>> &colorData,
                   const char *filename,
                   unsigned maxValue)
: Image(dimensions, colorData, filename)
, maxValue(maxValue) {
    analyzeColors(colorData);
}

void ImagePPM::analyzeColors(const std::shared_ptr<Vector<Color>> &colorData) {
    setType(MONOCHROME);
    for (unsigned i = 0; i < colorData->getSize(); ++i) {
        if(!(*colorData)[i].isMonochrome()) {
            if(!(*colorData)[i].isGrayScale()) {
                setType(COLOR);
                break;
            }
            setType(GRAY_SCALE);
        }
    }
}

bool ImagePPM::actualSave(std::ostream &ostream) const {
    Dimensions dim = getDimensions();
    ostream << MODE << std::endl;
    ostream << dim.width << " " << dim.height << std::endl;
    ostream << maxValue << std::endl;

    for (unsigned i = 0; i < dim.pixelCount(); ++i) {
        Color c = (*colorData)[i];
        unsigned rMapped = Helpers::mapRanges(0, Color::MAX_VALUE, 0, maxValue, c.r());
        unsigned gMapped = Helpers::mapRanges(0, Color::MAX_VALUE, 0, maxValue, c.g());
        unsigned bMapped = Helpers::mapRanges(0, Color::MAX_VALUE, 0, maxValue, c.b());

        ostream << rMapped << " " << gMapped << " " << bMapped << " ";

        if((i+1) % MAX_PER_LINE == 0) {
            ostream << std::endl;
        }
    }

    ostream << std::endl;
    return true;
}

