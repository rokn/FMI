#ifndef IMAGEEDITOR_COMMAND_H
#define IMAGEEDITOR_COMMAND_H

#include <functional>
#include "ImageCommandContainer.h"

class NoCommandContainerSet : public std::exception {};

class ImageCommand {
public:
    ImageCommand() : commandContainer(nullptr), name(nullptr) {}

    virtual void execute() = 0;
    void setCommandContainer(ImageCommandContainer* commandContainer);

    virtual void actualExecute() = 0;

    const char* getName();
protected:

    ImageCommandContainer* getCommandContainer();
    void applyToAllImages(std::function<void(Image*)> imageModifier);

    void setName(const char* name);

private:
    ImageCommandContainer* commandContainer;
    char* name;
};


#endif //IMAGEEDITOR_COMMAND_H
