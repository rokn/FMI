#ifndef IMAGEEDITOR_IMAGECOMMANDCONTAINER_H
#define IMAGEEDITOR_IMAGECOMMANDCONTAINER_H


#include "Image.h"
#include "Vector.h"

class ImageCommand;

class ImageCommandContainer {
public:
    virtual Vector<Image*>& getImages() = 0;
    virtual Vector<ImageCommand*>& getQueuedCommands() = 0;
};

#endif //IMAGEEDITOR_IMAGECOMMANDCONTAINER_H
