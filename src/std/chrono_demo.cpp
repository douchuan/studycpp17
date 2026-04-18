#include "chrono_demo.h"

#include <iostream>

int main() {
    // timestamp
    std::cout << "timestamp (ms): " << now_ms() << "\n";

    // measure
    auto [result, elapsed] = measure([]() {
        long long sum = 0;
        for (int i = 0; i < 1'000'000; ++i) sum += i;
        return sum;
    });
    std::cout << "sum = " << result << ", took " << elapsed << " ms\n";

    // time literals
    std::cout << "5s = " << seconds_to_ms(5) << " ms\n";

    return 0;
}
