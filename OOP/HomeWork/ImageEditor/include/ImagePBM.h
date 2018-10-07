#ifndef IMAGEEDITOR_IMAGEPBM_H
#define IMAGEEDITOR_IMAGEPBM_H


#include "Image.h"

class ImagePBM : public Image {
public:
    ImagePBM(const Dimensions &dimensions, const std::shared_ptr<Vector<Color>> &colorData, const char *filename);

protected:
    bool actualSave(std::ostream &ostream) const override;
};


#endif //IMAGEEDITOR_IMAGEPBM_H
