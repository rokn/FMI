#include <cstring>
#include "Commands/MakeCollageCommand.h"

static const char* COMMAND_NAME = "makeCollage ";

MakeCollageCommand::MakeCollageCommand(Image *firstImage, Image *secondImage, CollageType type)
: firstImage(firstImage)
, secondImage(secondImage)
, type(type) {
    const char* firstName = firstImage->getFilename();
    const char* secondName = secondImage->getFilename();
    char* name = new char[strlen(COMMAND_NAME) + strlen(firstName) + strlen(secondName) + 2];

    strcpy(name, COMMAND_NAME);
    strcat(name, firstName);
    strcat(name, " ");
    strcat(name, secondName);
    setName(name);

    delete[] name;
}

void MakeCollageCommand::actualExecute() {
}

