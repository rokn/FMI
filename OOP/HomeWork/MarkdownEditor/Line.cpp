#include <cstring>
#include <iostream>
#include "Line.h"
#include "Document.h"

Line::Line()
: isHeader(false)
, content(nullptr)
, wordMods(nullptr)
, wordCount(0)
, nextLine(nullptr) { }

Line::Line(const char *content)
: Line() {
    setContent(content);
}

bool Line::setContent(const char *content) {
    this->content = new (std::nothrow) char[strlen(content)];
    if(!content) {
        return false;
    }

    strcpy(this->content, content);

    wordCount = countWords();
    wordMods = new (std::nothrow) unsigned[wordCount];
    if(!wordMods) {
        return false;
    }

    for (int i = 0; i < wordCount; ++i) {
        wordMods[i] = Document::WordMod::NONE;
    }

    return true;
}

unsigned Line::countWords() {
    unsigned count = 0;
    const char* content = this->content;
    if(!content || !(*content)) {
        return count;
    }

    char prev = *content;

    while(*(++content)) {
        if(isSpace(*content) && !isSpace(prev)) {
            ++count;
        }

        prev = *content;
    }

    if(!isSpace(prev)) {
        count ++;
    }

    return count;
}

void Line::setNextLine(Line *next) {
    nextLine = next;
}

Line* Line::getNextLine() {
    return nextLine;
}

bool Line::setWordsMod(unsigned mod, unsigned from, unsigned to) {
    if(!(isValidWord(from) && isValidWord(to) && wordMods)) {
        return false;
    }

    for (int i = from; i <= to; ++i) {
        wordMods[i] |= mod;
    }

    return true;
}

bool Line::isValidWord(unsigned word) {
    return word < wordCount;
}

void Line::setHeader(bool header) {
    isHeader = header;
}

Line::~Line() {
    delete[] content;
    delete[] wordMods;
}

void Line::write(std::ostream &output) const {
    const char* content = this->content;
    static const bool WORD = false;
    static const bool SPACES = true;
    static const bool FRONT = false;
    static const bool BACK = true;

    handleHeader(output);

    writePart(content, output, SPACES);

    for (unsigned i = 0; i < wordCount; ++i) {
        writeMod(output, i, FRONT);
        writePart(content, output, WORD);
        writeMod(output, i, BACK);
        writePart(content, output, SPACES);
    }

    output << std::endl;
}

bool Line::isSpace(char c) const {
    return c == ' ';
}

void Line::writePart(const char *&content, std::ostream &ostream, bool spaces) const {
    while(*content && (isSpace(*content) == spaces)) {
        ostream << *content;
        ++content;
    }
}

void Line::writeMod(std::ostream &output, unsigned word, bool isBack) const {
    unsigned otherMod = 0;
    if(isBack) {
        if(word < wordCount-1) {
            otherMod = wordMods[word+1];
        }
    } else {
        if(word > 0) {
            otherMod = wordMods[word-1];
        }
    }

    unsigned modDiff = wordMods[word] & (~otherMod); // Inverse implication

    if(modDiff & Document::ITALIC) {
        output << '*';
    }

    if(modDiff & Document::BOLD) {
        output << "**";
    }
}

void Line::handleHeader(std::ostream &ostream) const {
    if(isHeader) {
        ostream << "# ";
    }
}
