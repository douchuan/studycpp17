#include "proxy_demo.h"

#include <iostream>

int main() {
    Proxy proxy;
    std::cout << "loaded before request: " << proxy.is_loaded() << "\n";
    std::cout << proxy.request() << "\n";
    std::cout << "loaded after request: " << proxy.is_loaded() << "\n";
    return 0;
}
