#include "Commands/GrayScaleCommand.h"

static const char *const COMMAND_NAME = "grayscale";

GrayScaleCommand::GrayScaleCommand() {
    setName(COMMAND_NAME);
}

void GrayScaleCommand::actualExecute() {
    applyToAllImages([](Image* image) {
        image->makeGrayScale();
    });
}

