#include "DocumentFactory.h"

Document* DocumentFactory::createDocument(const char *filename) {
    if(!(filename && *filename)) {
        return nullptr;
    }

    Document *document = new Document();
    if(!document->open(filename)) {
        delete document;
        document = nullptr;
    }

    return document;
}
