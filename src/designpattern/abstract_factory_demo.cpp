#include "abstract_factory_demo.h"

#include <iostream>

int main() {
    LightFactory light;
    auto lb = light.create_button();
    auto lc = light.create_checkbox();
    std::cout << lb->render() << " " << lc->render() << "\n";

    DarkFactory dark;
    auto db = dark.create_button();
    auto dc = dark.create_checkbox();
    std::cout << db->render() << " " << dc->render() << "\n";
    return 0;
}
