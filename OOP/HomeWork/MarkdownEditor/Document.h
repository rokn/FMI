#ifndef MARKDOWNEDITOR_DOCUMENT_H
#define MARKDOWNEDITOR_DOCUMENT_H

class Line;

class Document {
public:
    enum WordMod {
        NONE   = 0,
        BOLD   = 1,
        ITALIC = 1 << 1,
    };

    enum ModStatus {
        SUCCESS,
        FILE_NOT_OPENED,
        INVALID_LINE,
        INVALID_WORD,
        TOO_LONG_LINE,
        INSUFFICIENT_MEMORY
    };

    Document();
    explicit Document(const char* filename);
    ~Document();

    bool open(const char* filename);

    ModStatus makeHeader(unsigned line);
    ModStatus makeWordMod(unsigned line, unsigned from, unsigned to, unsigned wordMod);

    ModStatus addLine(const char* lineContent);
    ModStatus removeLine(unsigned line);

    bool save();
    void close();

private:
    bool fileOpened;
    char *fileName;
    Line *firstLine;
    Line *lastLine;
    unsigned lineCount;

    bool isValidLine(unsigned line);
    Line* getLine(unsigned line);
};


#endif //MARKDOWNEDITOR_DOCUMENT_H
