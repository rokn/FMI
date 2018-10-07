#ifndef IMAGEEDITOR_IMAGEPPM_H
#define IMAGEEDITOR_IMAGEPPM_H


#include "Image.h"

class ImagePPM : public Image {
public:
    ImagePPM(const Dimensions &dimensions, const std::shared_ptr<Vector<Color>> &colorData, const char *filename,
             unsigned maxValue);

protected:
    bool actualSave(std::ostream &ostream) const override;

private:
    unsigned maxValue;

    void analyzeColors(const std::shared_ptr<Vector<Color>> &colorData);
};


#endif //IMAGEEDITOR_IMAGEPPM_H
