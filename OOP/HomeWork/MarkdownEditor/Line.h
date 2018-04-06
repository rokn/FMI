#ifndef MARKDOWNEDITOR_LINE_H
#define MARKDOWNEDITOR_LINE_H

#include <ostream>

class Line {
public:
    Line();
    explicit Line(const char* content);
    ~Line();

    bool setContent(const char* content);
    void setNextLine(Line* next);
    Line* getNextLine();

    bool setWordsMod(unsigned mod, unsigned from, unsigned to);
    void setHeader(bool header);

    void write(std::ostream& output) const;

private:
    char* content;
    unsigned* wordMods;
    unsigned wordCount;
    bool isHeader;
    Line *nextLine;

    unsigned countWords();
    bool isValidWord(unsigned word);
    bool isSpace(char c) const;

    void writePart(const char *&content, std::ostream &ostream, bool spaces) const;
    void writeMod(std::ostream &output, unsigned word, bool isBack) const;

    void handleHeader(std::ostream &ostream) const;
};


#endif //MARKDOWNEDITOR_LINE_H
