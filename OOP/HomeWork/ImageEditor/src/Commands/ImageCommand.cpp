#include <cstring>
#include "Commands/ImageCommand.h"

void ImageCommand::setCommandContainer(ImageCommandContainer *commandContainer) {
    this->commandContainer = commandContainer;
}

ImageCommandContainer* ImageCommand::getCommandContainer() {
    return commandContainer;
}

void ImageCommand::applyToAllImages(std::function<void(Image *)> imageModifier) {
    if(!commandContainer) {
        throw NoCommandContainerSet();
    }

    auto& images = commandContainer->getImages();
    for (unsigned i = 0; i < images.getSize(); ++i) {
        imageModifier(images[i]);
    }
}

const char *ImageCommand::getName() {
    return name;
}

void ImageCommand::setName(const char *name) {
    char *newName = new char[strlen(name) + 1];
    strcpy(newName, name);
    
    delete[] this->name;
    this->name = newName;
}
