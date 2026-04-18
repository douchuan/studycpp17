#include "command_demo.h"

#include <iostream>

int main() {
    Light light;
    CommandInvoker invoker;
    invoker.execute(std::make_unique<LightOnCommand>(&light));
    std::cout << "light on: " << light.is_on() << "\n";
    invoker.undo_last();
    std::cout << "light after undo: " << light.is_on() << "\n";
    return 0;
}
