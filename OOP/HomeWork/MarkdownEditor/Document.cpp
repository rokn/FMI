#include "Document.h"
#include "Line.h"
#include <fstream>
#include <iostream>
#include <cstring>

using std::ifstream;
using std::ofstream;
using std::ios;
using std::cout;
using std::endl;

const unsigned Document::MAX_LINE_LENGTH = 1024;

Document::Document()
: fileName(nullptr)
, newFileName(nullptr)
, fileOpened(false)
, firstLine(nullptr)
, lastLine(nullptr)
, lineCount(0) { }

Document::Document(const char *filename)
: Document() {
    open(filename);
}

bool Document::open(const char *filename) {
    if(fileOpened) {
        return false;
    }

    ifstream file(filename);
    if(!file) {
        return false;
    }

    fileName = new (std::nothrow) char[strlen(filename) + 1];
    if(!filename) {
        return false;
    }
    strcpy(fileName, filename);

    char* buffer = new (std::nothrow) char[MAX_LINE_LENGTH+1];
    if(!buffer) {
        return false;
    }

    if(file.getline(buffer, MAX_LINE_LENGTH)) {
        firstLine = new (std::nothrow) Line(buffer);
        if(!firstLine) {
            return false;
        }

        lastLine = firstLine;
    } else {
        return true;
    }

    lineCount = 1;

    while(file.getline(buffer, MAX_LINE_LENGTH)) {
        Line* curr = new (std::nothrow) Line();
        if(!(curr && curr->setContent(buffer))) {
            return false;
        }

        lastLine->setNextLine(curr);
        lastLine = curr;
        lineCount++;
    }

    fileOpened = true;
    return true;
}

bool Document::save() {
    ofstream out(getMarkdownName());

    if(!out) {
        return false;
    }

    Line* curr = firstLine;

    while(curr) {
        curr->write(out);
        curr = curr->getNextLine();
    }

    return true;
}

Document::~Document() {
    close();
}

void Document::close() {
    if(!fileOpened) {
        return;
    }

    delete[] fileName;
    delete[] newFileName;

    Line* curr = firstLine;
    while(curr) {
        Line* temp = curr->getNextLine();
        delete curr;
        curr = temp;
    }

    fileOpened = false;
    lineCount = 0;
}

bool Document::isValidLine(unsigned line) {
    return line < lineCount;
}

Line *Document::getLine(unsigned line) {
    if(!isValidLine(line)) {
        return nullptr;
    }

    Line* curr = firstLine;
    for (int i = 0; i < line; ++i) {
        curr = curr->getNextLine();
    }

    return curr;
}

Document::ModStatus Document::makeHeader(unsigned line) {
    if(!fileOpened) {
        return FILE_NOT_OPENED;
    }

    Line* lineP = getLine(line);
    if(!lineP) {
        return INVALID_LINE;
    }

    lineP->setHeader(true);
    return SUCCESS;
}

Document::ModStatus Document::makeWordMod(unsigned line, unsigned from, unsigned to, unsigned wordMod) {
    if(!fileOpened) {
        return FILE_NOT_OPENED;
    }

    Line* lineP = getLine(line);
    if(!lineP) {
        return INVALID_LINE;
    }

    if(!lineP->setWordsMod(wordMod, from, to)) {
        return INVALID_WORD;
    }

    return SUCCESS;
}

Document::ModStatus Document::addLine(const char *lineContent) {
    if(!fileOpened) {
        return FILE_NOT_OPENED;
    }

    if(strlen(lineContent) > MAX_LINE_LENGTH) {
        return TOO_LONG_LINE;
    }

    Line* line = new (std::nothrow) Line(lineContent);
    if(!line) {
        return INSUFFICIENT_MEMORY;
    }

    if(!lastLine) {
        firstLine = line;
        lastLine = line;
    } else {
        lastLine->setNextLine(line);
        lastLine = line;
    }

    ++lineCount;
    return SUCCESS;
}

Document::ModStatus Document::removeLine(unsigned line) {
    if(!isValidLine(line)) {
        return INVALID_LINE;
    }

    if(line == 0) {
        Line* lineP = firstLine;
        firstLine = lineP->getNextLine();
        delete lineP;

        --lineCount;
        if(lineCount == 0) {
            lastLine = nullptr;
        }
        return SUCCESS;
    }

    Line* curr = firstLine;

    for (int i = 0; i < line - 1; ++i) {
        curr = curr->getNextLine();
    }

    Line* temp = curr->getNextLine();
    curr->setNextLine(temp->getNextLine());
    delete temp;

    --lineCount;
    return SUCCESS;
}

const char * Document::getMarkdownName() {
    if(newFileName) {
        return newFileName;
    }

    newFileName = new char[strlen(fileName)];
    strcpy(newFileName, fileName);
    char* tmp = newFileName;

    while(*tmp != '.') {
        tmp++;
    }

    tmp++;
    strcpy(tmp, "md");

    return newFileName;
}
