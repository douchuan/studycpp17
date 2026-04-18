#include "smart_ptr_demo.h"

#include <iostream>

int main() {
    // unique_ptr
    auto s = make_unique_str("hello unique_ptr");
    std::cout << "*s = " << *s << "\n";

    // shared_ptr
    auto v = make_shared_vec();
    std::cout << "shared_vec: ";
    for (int x : *v) std::cout << x << " ";
    std::cout << "\n";
    std::cout << "use_count = " << v.use_count() << "\n";
    {
        [[maybe_unused]] auto copy = v;  // NOLINT(performance-unnecessary-copy-initialization)
        std::cout << "use_count (after copy) = " << v.use_count() << "\n";
    }
    std::cout << "use_count (after copy gone) = " << v.use_count() << "\n";

    // custom deleter
    auto p = make_ptr_with_deleter(42);
    std::cout << "*p = " << *p << "\n";

    // weak_ptr
    auto sp = std::make_shared<int>(100);
    auto wp = observe(sp);
    std::cout << "weak_ptr expired (alive): " << std::boolalpha << wp.expired() << "\n";
    sp.reset();
    std::cout << "weak_ptr expired (reset): " << wp.expired() << "\n";

    return 0;
}
