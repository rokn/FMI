#ifndef IMAGEEDITOR_IMAGE_H
#define IMAGEEDITOR_IMAGE_H

#include <memory>
#include <ostream>
#include "ImageStructures.h"
#include "Vector.h"


class Image {
public:
    Image(Dimensions dimensions, const std::shared_ptr<Vector<Color>> &colorData, const char *filename);

    void rotate(RotationDirection direction);
    Rotation getRotation() const;

    Dimensions getDimensions() const;

    void makeMonochrome();
    void makeGrayScale();
    void makeNegative();

    bool save(const char* suffix);

    const char* getFilename() const;

protected:
    void setType(ImageType type);

    std::shared_ptr<Vector<Color>> colorData;

    const char *getNewFilename(const char *suffix) const;

    virtual bool actualSave(std::ostream& ostream) const = 0;
private:
    Rotation rotation;
    ImageType type;

    Dimensions dimensions;

    char* filename;


    void performRotation();
    unsigned getIndex(unsigned x, unsigned y, unsigned width);

    unsigned getOldIndexRotated(unsigned x, unsigned y);
};


#endif //IMAGEEDITOR_IMAGE_H
