#include "observer_demo.h"

#include <iostream>

int main() {
    Subject subject;
    LogObserver log;
    subject.attach(&log);
    subject.notify("user_login");
    subject.notify("file_upload");
    for (const auto& e : log.events()) std::cout << "event: " << e << "\n";
    return 0;
}
