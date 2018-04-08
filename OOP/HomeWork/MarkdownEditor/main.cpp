#include <iostream>
#include "Document.h"
#include "CommandInterpreter.h"

using namespace std;

int main() {
    Document doc("test.txt");
    CommandInterpreter interpreter(&doc);
    interpreter.launch();
    return 0;
}