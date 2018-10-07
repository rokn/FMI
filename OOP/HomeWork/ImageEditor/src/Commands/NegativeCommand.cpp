#include "Commands/NegativeCommand.h"

static const char *const COMMAND_NAME = "negative";

NegativeCommand::NegativeCommand() {
    setName(COMMAND_NAME);
}

void NegativeCommand::actualExecute() {
    applyToAllImages([](Image* image) {
        image->makeNegative();
    });
}
