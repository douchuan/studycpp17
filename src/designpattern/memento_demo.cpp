#include "memento_demo.h"

#include <iostream>

int main() {
    TextEditor editor("v1");
    History history;
    history.push(editor.save());
    editor.set_content("v2");
    history.push(editor.save());
    editor.set_content("v3");
    std::cout << "current: " << editor.content() << "\n";
    auto m = history.pop();
    editor.restore(*m);
    std::cout << "after undo: " << editor.content() << "\n";
    return 0;
}
