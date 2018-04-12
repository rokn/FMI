#include <iostream>
#include "Document.h"
#include "CommandInterpreter.h"
#include "DocumentFactory.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Expected filename as argument" << std::endl;
        return -1;
    }

    Document *doc = DocumentFactory::createDocument(argv[1]);
    if(!doc) {
        std::cout << "Couldn't open file: " << argv[1] << std::endl;
        return -2;
    }

    CommandInterpreter interpreter(doc);
    interpreter.launch();

    delete doc;
    return 0;
}