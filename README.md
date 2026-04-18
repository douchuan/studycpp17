# studycpp

C++17 study notes, featuring self-contained, runnable and testable demos for the standard library, common algorithms, and C++17 features.

## Directory Structure

```
studycpp/
├── CMakeLists.txt
├── src/
│   ├── algorithm/              # Algorithms
│   ├── cpp17/                  # C++17 features
│   ├── designpattern/          # Design patterns
│   └── sanitizer/              # Sanitizer tool demonstrations
│   ├── security/               # Cryptography toolkit (OpenSSL 3.x)
│   └── std/                    # Standard library
└── tests/                      # Google Test unit tests
```

**Source files in each directory are self-contained**: `.h` defines functions, and `.cpp` contains a `main()` function for standalone compilation and execution. To add a new module, simply create a pair of `.h` / `.cpp` files in the target directory and append an `add_executable` line in the directory's `CMakeLists.txt`.

## Build and Run

```bash
# First-time setup + build
mkdir -p build && cd build
cmake .. \
    -DCMAKE_C_COMPILER=/opt/homebrew/opt/llvm/bin/clang \
    -DCMAKE_CXX_COMPILER=/opt/homebrew/opt/llvm/bin/clang++ \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DOPENSSL_ROOT_DIR=/opt/homebrew/opt/openssl@3
cmake --build . -j$(sysctl -n hw.ncpu)

# Run all tests
ctest --output-on-failure

# Run a specific demo
./src/std/string_demo
./src/algorithm/sort_demo
./src/cpp17/structured_bindings_demo
./src/security/aes_gcm_demo
```

For subsequent incremental builds:

```bash
cd build && cmake --build .
```

## Code Formatting

```bash
cmake --build . --target format
```

Formatting rules are defined in `.clang-format` (based on Google style, 4-space indentation, line width 100).

## Static Analysis (clang-tidy)

```bash
cmake --build . --target analyze
```