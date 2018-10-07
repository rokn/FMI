#ifndef IMAGEEDITOR_INPUTSYSTEM_H
#define IMAGEEDITOR_INPUTSYSTEM_H

#include "System.h"

class InputSystem {
public:
    enum Commands {
        LOAD = 0,
        MONOCHROME,
        GRAY_SCALE,
        NEGATIVE,
        ROTATE,
        SAVE,
        SESSION_INFO,
        EXIT,
        SWITCH,
        MAKE_COLLAGE,
        MAX_COMMAND // Should be at the end of the enum
    };

    explicit InputSystem(System* system);
    void run();

private:
    System* system;
    bool running;

    Commands getCommand(const char* commandName);

    void execute(Commands command);

    void parseImages();

    void skipSpaces(const char *&pos);

    unsigned int findSpace(const char *pos);

    void loadImages(const Vector<char *>& fileNames);

    void addCommandToSession(ImageCommand *command);

    void printSessionInfo();

    void saveSession();

    void switchSession();

    void parseRotateCommand();
};


#endif //IMAGEEDITOR_INPUTSYSTEM_H
