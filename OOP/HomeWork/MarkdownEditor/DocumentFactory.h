#ifndef MARKDOWNEDITOR_DOCUMENTFACTORY_H
#define MARKDOWNEDITOR_DOCUMENTFACTORY_H


#include "Document.h"

namespace DocumentFactory {
    Document* createDocument(const char* filename);
};


#endif //MARKDOWNEDITOR_DOCUMENTFACTORY_H
