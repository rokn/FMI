#include "CommandInterpreter.h"
#include "Document.h"
#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;

static const unsigned MAX_COMMAND_LENGTH = 64;
static const unsigned COMMAND_COUNT = 7;
static const char *COMMANDS[] = {
        "makeHeading",
        "makeItalic",
        "makeBold",
        "makeCombine",
        "addLine",
        "remove",
        "exit",
};
static const CommandInterpreter::Command COMMANDS_MAP[] = {
        CommandInterpreter::MAKE_HEADING,
        CommandInterpreter::MAKE_ITALIC,
        CommandInterpreter::MAKE_BOLD,
        CommandInterpreter::MAKE_COMBINE,
        CommandInterpreter::ADD_LINE,
        CommandInterpreter::REMOVE_LINE,
        CommandInterpreter::EXIT,
};

CommandInterpreter::CommandInterpreter()
        : document(nullptr) {}

CommandInterpreter::CommandInterpreter(Document *document) {
    setDocument(document);
}

void CommandInterpreter::setDocument(Document *document) {
    this->document = document;
}

void CommandInterpreter::launch() {
    if (!document) {
        return;
    }

    bool isRunning = true;

    while (isRunning) {
        Command command = getNextCommand();
        executeCommand(command);

        if (command == EXIT) {
            document->save();
            document->close();
            isRunning = false;
        }
    }
}

CommandInterpreter::Command CommandInterpreter::getNextCommand() {
    Command result = UNKNOWN;

    char command[MAX_COMMAND_LENGTH];
    cin >> command;

    for (int i = 0; i < COMMAND_COUNT; ++i) {
        if (!strcmp(COMMANDS[i], command)) {
            result = COMMANDS_MAP[i];
            break;
        }
    }

    return result;
}

void CommandInterpreter::executeCommand(Command command) {
    if(command & (EXIT | UNKNOWN)) {
        return;
    }

    Document::ModStatus status = Document::SUCCESS;
    char *newLine;
    unsigned line, from, to;

    bool readSuccess = readArgs(line, from, to, newLine, command);
    if(!readSuccess) {
        return;
    }

    switch (command) {
        case MAKE_HEADING:
            status = document->makeHeader(line);
            break;
        case MAKE_ITALIC:
            status = document->makeWordMod(line, from, to, Document::WordMod::BOLD);
            break;
        case MAKE_BOLD:
            status = document->makeWordMod(line, from, to, Document::WordMod::ITALIC);
            break;
        case MAKE_COMBINE:
            status = document->makeWordMod(line, from, to, Document::WordMod::BOLD | Document::WordMod::ITALIC);
            break;
        case ADD_LINE:
            status = document->addLine(newLine);
            delete[] newLine;
            break;
        case REMOVE_LINE:
            status = document->removeLine(line);
            break;
        case UNKNOWN:
            cout << "Unknown command!" << endl;
            return;
    }

    handleStatus(status);
}

void CommandInterpreter::handleStatus(Document::ModStatus status) {
    switch(status) {
        case Document::SUCCESS: break;
        case Document::FILE_NOT_OPENED:
            cout << "File is not opened!" << endl;
            break;
        case Document::INVALID_LINE:
            cout << "Invalid line!" << endl;
            break;
        case Document::INVALID_WORD:
            cout << "Invalid word range!" << endl;
            break;
        case Document::TOO_LONG_LINE:
            cout << "Line too long!" << endl;
            break;
        case Document::INSUFFICIENT_MEMORY:
            cout << "Insufficient memory!" << endl;
            break;
    }

}

bool CommandInterpreter::readArgs(unsigned &line, unsigned &from, unsigned &to, char *&newLine, Command command) {
    if(command == ADD_LINE) {
        newLine = new(std::nothrow) char[Document::MAX_LINE_LENGTH + 1];
        if (!newLine) {
            cout << "Insufficient memory!" << endl;
            return false;
        }

        cin.ignore(); //Ignore space after command
        cin.getline(newLine, Document::MAX_LINE_LENGTH);
        return true;
    }

    cin >> line;
    line--;

    if(command & (MAKE_ITALIC | MAKE_BOLD | MAKE_COMBINE)) {
        cin >> from >> to;
        from--;
        to--;
    }

    return true;
}


