#include <cstring>
#include <iostream>
#include <limits>
#include "ImageLoader.h"
#include "Commands/MonochromeCommand.h"
#include "Commands/GrayScaleCommand.h"
#include "Commands/NegativeCommand.h"
#include "Commands/RotateCommand.h"
#include "Commands/AddImageCommand.h"
#include "Commands/MakeCollageCommand.h"
#include "InputSystem.h"

using std::cin;
using std::cout;
using std::endl;

static const char* COMMANDS[InputSystem::MAX_COMMAND] = {
        "load",
        "monochrome",
        "grayscale",
        "negative",
        "rotate",
        "save",
        "sessionInfo",
        "exit",
        "switch",
        "makeCollage",
};

static const unsigned MAX_COMMAND_NAME = 30;

static const int MAX_LINE = 4096;

InputSystem::InputSystem(System *system)
: system(system)
, running(false) { }

void InputSystem::run() {
    running = true;
    char command[MAX_COMMAND_NAME];

    while(running) {
        cout << ">";
        cin >> command;
        Commands actualCommand = getCommand(command);
        execute(actualCommand);
//        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

InputSystem::Commands InputSystem::getCommand(const char *commandName) {
    for (unsigned i = 0; i < MAX_COMMAND; ++i) {
        if(!strcmp(commandName, COMMANDS[i])) {
            return (Commands)i;
        }
    }

    return MAX_COMMAND;
}

void InputSystem::execute(InputSystem::Commands command) {
    switch(command){
        case LOAD:
            parseImages();
            break;

        case MONOCHROME:
            addCommandToSession(new MonochromeCommand());
            break;

        case GRAY_SCALE:
            addCommandToSession(new GrayScaleCommand());
            break;

        case NEGATIVE:
            addCommandToSession(new NegativeCommand());
            break;

        case ROTATE:
            parseRotateCommand();
            break;

        case SAVE:
            saveSession();
            break;

        case SESSION_INFO:
            printSessionInfo();
            break;

        case EXIT:
            running = false;
            break;

        case SWITCH:
            switchSession();
            break;

        case MAKE_COLLAGE:
            break;

        case MAX_COMMAND:
            cout << "Command unknown!" << endl;
            break;
    }
}

void InputSystem::parseImages() {
    Vector<char*> images;
    char* line = new char[MAX_LINE];
    cin.getline(line, MAX_LINE);
    const char* currPos = line;

    while(*currPos) {
        skipSpaces(currPos);
        unsigned spacePos = findSpace(currPos);
        char* filename = new char[spacePos + 1];
        strncpy(filename, currPos, spacePos);
        filename[spacePos] = '\0';

        images.pushBack(filename);
        currPos += spacePos;
    }

    delete[] line;

    loadImages(images);

    for (unsigned i = 0; i < images.getSize(); ++i) {
        delete[] images[i];
    }
}

void InputSystem::skipSpaces(const char *&pos) {
    while((*pos == ' ' || *pos == '\t') && *pos) {
        ++pos;
    }
}

unsigned InputSystem::findSpace(const char *pos) {
    const char* beg = pos;
    while(!(*pos == ' ' || *pos == '\t' || !*pos)) {
        ++pos;
    }

    return (unsigned int)(pos - beg);
}

void InputSystem::loadImages(const Vector<char *>& fileNames) {
    Vector<Image*> images(fileNames.getSize());

    for (unsigned i = 0; i < fileNames.getSize(); ++i) {
        Image* image = ImageLoader::loadImage(fileNames[i]);
        if(!image) {
            cout << "Failed loading image: " << fileNames[i] << endl;
            continue;
        }

        images.pushBack(image);
    }

    Session* session = new Session(images);
    system->addSession(session);

    cout << "Session with ID: " << session->getId() << " started" << endl;
}

void InputSystem::addCommandToSession(ImageCommand *command) {
    Session* session = system->getSession();
    if(!session) {
        cout << "No session loaded" << endl;
        delete command;
        return;
    }

    session->addCommand(command);
}

void InputSystem::printSessionInfo() {
    Session* session = system->getSession();
    if(!session) {
        cout << "No session loaded" << endl;
        return;
    }

    session->printInfo();
}

void InputSystem::saveSession() {
    Session* session = system->getSession();
    if(!session) {
        cout << "No session loaded" << endl;
        return;
    }

    session->save();
}

void InputSystem::switchSession() {
    unsigned newId;
    cin >> newId;
    Session* session = system->switchSession(newId);
    if(!session) {
        cout << "Session with ID: " << newId << " not found" << endl;
        return;
    }

    cout << "You switched to session with ID: " << session->getId() << "!" << endl;
}

void InputSystem::parseRotateCommand() {
    char direction[10];
    cin >> direction;
    RotationDirection rotation;

    if(!strcmp(direction, "left")) {
        rotation = ROTATE_LEFT;
    } else if (!strcmp(direction, "right")) {
        rotation = ROTATE_RIGHT;
    } else {
        cout << "Direction unknown" << endl;
        return;
    }

    addCommandToSession(new RotateCommand(rotation));
}
