#include "Commands/MonochromeCommand.h"

static const char *const COMMAND_NAME = "monochrome";

MonochromeCommand::MonochromeCommand() {
    setName(COMMAND_NAME);
}

void MonochromeCommand::actualExecute() {
    applyToAllImages([](Image* image) {
        image->makeMonochrome();
    });
}
