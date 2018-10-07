#ifndef IMAGEEDITOR_IMAGEPGM_H
#define IMAGEEDITOR_IMAGEPGM_H


#include "Image.h"

class ImagePGM : public Image {
public:
    ImagePGM(const Dimensions &dimensions, const std::shared_ptr<Vector<Color>> &colorData, const char *filename,
                 unsigned maxValue);

protected:
    bool actualSave(std::ostream &ostream) const override;

private:
    unsigned maxValue;

    void analyzeColors(const std::shared_ptr<Vector<Color>> &colorData);
};


#endif //IMAGEEDITOR_IMAGEPGM_H
