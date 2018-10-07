#include "Commands/ActiveCommand.h"

void ActiveCommand::execute() {
    auto& queuedCommands = getCommandContainer()->getQueuedCommands();

    for (unsigned i = 0; i < queuedCommands.getSize(); ++i) {
        queuedCommands[i]->actualExecute();
    }

    queuedCommands.clear();
    actualExecute();
}
