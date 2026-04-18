#include "bridge_demo.h"

#include <iostream>

int main() {
    CircleShape v(std::make_unique<VectorRenderer>(), 5.0);
    CircleShape r(std::make_unique<RasterRenderer>(), 5.0);
    std::cout << v.draw() << "\n";
    std::cout << r.draw() << "\n";
    return 0;
}
