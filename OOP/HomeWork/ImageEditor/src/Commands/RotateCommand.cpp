#include <cstring>
#include "Commands/RotateCommand.h"

static const char *const COMMAND_NAME = "rotate ";

RotateCommand::RotateCommand(RotationDirection direction)
: direction(direction) {
    const char* dirName = (direction == ROTATE_LEFT) ? "left" : "right";
    char* name = new char[strlen(COMMAND_NAME) + strlen(dirName) + 1];

    strcpy(name, COMMAND_NAME);
    strcat(name, dirName);
    setName(name);

    delete[] name;
}

void RotateCommand::actualExecute() {
    applyToAllImages([this](Image* image) {
        image->rotate(direction);
    });
}
