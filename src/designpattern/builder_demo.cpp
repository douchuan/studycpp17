#include "builder_demo.h"

#include <iostream>

int main() {
    HttpRequestBuilder builder;
    auto req = builder.method("POST").url("/api/data").body(R"({"key":"value"})").build();
    std::cout << req.build() << "\n";
    return 0;
}
