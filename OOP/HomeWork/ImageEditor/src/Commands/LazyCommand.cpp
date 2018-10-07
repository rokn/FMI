#include "Commands/LazyCommand.h"

void LazyCommand::execute() {
    getCommandContainer()->getQueuedCommands().pushBack(this);
}
