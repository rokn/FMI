#include <iostream>
#include <ctime>
#include "Session.h"
#include "Commands/ImageCommand.h"

static const int SUFFIX_BUFFER_SIZE = 80;
unsigned Session::ID_COUNTER = 0;

Session::Session(const Vector<Image *> &startingImages)
: addedImages(startingImages) {
    id = ID_COUNTER++;
}

Vector<Image *> &Session::getImages() {
    return addedImages;
}

Vector<ImageCommand *> &Session::getQueuedCommands() {
    return queuedLazyCommands;
}

unsigned Session::getId() const {
    return id;
}

void Session::addCommand(ImageCommand *command) {
    command->setCommandContainer(this);
    commands.pushBack(command);
}

bool Session::undoCommand() {
    if(commands.isEmpty()) {
        return false;
    }

    ImageCommand* command = commands.popBack();
    delete command;
    return true;
}

void Session::save() {
    for (unsigned i = 0; i < commands.getSize(); ++i) {
        commands[i]->execute();
    }

    for (unsigned i = 0; i < queuedLazyCommands.getSize(); ++i) {
        queuedLazyCommands[i]->actualExecute();
    }

    clearCommands();

    const char* suffix = getTimeSuffix();

    for (unsigned i = 0; i < addedImages.getSize(); ++i) {
        if (!addedImages[i]->save(suffix)) {
            std::cout << "Failed saving image: " << addedImages[i]->getFilename();
        }
    }

    delete[] suffix;
}

void Session::clearCommands() {
    for (unsigned i = 0; i < commands.getSize(); ++i) {
        delete commands[i];
    }

    commands.clear();
    queuedLazyCommands.clear();
}

const char *Session::getTimeSuffix() const {
    time_t rawTime;
    struct tm * timeInfo;
    char* buffer = new char[SUFFIX_BUFFER_SIZE];

    time (&rawTime);
    timeInfo = localtime(&rawTime);

    strftime(buffer, sizeof(buffer), "_%d-%m-%Y_%I%M%S", timeInfo);

    return buffer;
}

void Session::printInfo() const {
    std::cout << "Name of the images in the session: ";

    for (unsigned i = 0; i < addedImages.getSize(); ++i) {
        std::cout << addedImages[i]->getFilename() << " ";
    }

    std::cout << std::endl;

    std::cout << "Pending transformations: ";

    for (unsigned i = 0; i < commands.getSize(); ++i) {
        std::cout << commands[i]->getName();
        if(i < commands.getSize() - 1) {
            std::cout << ", ";
        }
    }
}

Session::~Session() {
    clearCommands();

    for (unsigned i = 0; i < addedImages.getSize(); ++i) {
        delete addedImages[i];
    }

    addedImages.clear();
}
