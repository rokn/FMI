#include <cstring>
#include "Commands/AddImageCommand.h"

static const char* COMMAND_NAME = "add ";

AddImageCommand::AddImageCommand(Image *newImage)
: newImage(newImage) {
    char* name = new char[strlen(COMMAND_NAME) + strlen(newImage->getFilename()) + 1];

    strcpy(name, COMMAND_NAME);
    strcat(name, newImage->getFilename());
    setName(name);

    delete[] name;
}

void AddImageCommand::actualExecute() {
    if(newImage != nullptr) {
        getCommandContainer()->getImages().pushBack(newImage);
        newImage = nullptr;
    }
}

AddImageCommand::~AddImageCommand() {
    delete newImage;
}
