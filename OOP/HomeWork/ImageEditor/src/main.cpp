#include <InputSystem.h>
#include "System.h"

int main() {
    System system;
    InputSystem inputSystem(&system);
    inputSystem.run();
    return 0;
}