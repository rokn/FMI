#ifndef MARKDOWNEDITOR_COMMANDINTERPRETER_H
#define MARKDOWNEDITOR_COMMANDINTERPRETER_H

#include "Document.h"

class Document;

class CommandInterpreter {
public:
    CommandInterpreter();
    explicit CommandInterpreter(Document* document);

    void setDocument(Document* document);

    void launch();

    enum Command {
        UNKNOWN      = 0,
        MAKE_HEADING = 1 << 0,
        MAKE_ITALIC  = 1 << 1,
        MAKE_BOLD    = 1 << 2,
        MAKE_COMBINE = 1 << 3,
        ADD_LINE     = 1 << 4,
        REMOVE_LINE  = 1 << 5,
        EXIT         = 1 << 6,
    };
private:
    Document* document;

    Command getNextCommand();
    void executeCommand(Command command);

    void handleStatus(Document::ModStatus status);
    bool readArgs(unsigned &line, unsigned &from, unsigned &to, char *&newLine, Command command);
};


#endif //MARKDOWNEDITOR_COMMANDINTERPRETER_H
