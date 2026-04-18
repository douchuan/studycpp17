#include "structured_bindings_demo.h"

#include <iostream>

int main() {
    // struct
    Point p{10, 20, 30};
    auto [x, y, z] = unpack_point(p);
    std::cout << "point: (" << x << ", " << y << ", " << z << ")\n";

    // map kv
    std::map<std::string, int> ages = {{"Alice", 30}, {"Bob", 25}};
    auto [k, v] = first_kv(ages);
    std::cout << "first kv: " << k << " -> " << v << "\n";

    // tuple
    auto [name, age, active] = make_person();
    std::cout << "person: " << name << ", " << age << ", active=" << std::boolalpha << active
              << "\n";

    return 0;
}
