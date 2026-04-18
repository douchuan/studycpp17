# studycpp — CLAUDE.md

C++17 学习笔记项目，通过可独立编译运行和测试的 demo 学习 C++ 基础语法、标准库、常用算法、C++17 特性、设计模式、密码学和 Sanitizer 工具。

## 技术栈

- **C++17**（AppleClang / libc++）
- **CMake 3.20+**（FetchContent 自动拉取 GoogleTest）
- **OpenSSL 3.x**（密码学工具箱，macOS 通过 Homebrew 安装：`brew install openssl@3`）
- **Google Test**（单元测试）
- **clang-format**（代码格式化，基于 Google 风格：4 空格缩进，行宽 100）
- **Sanitizer**（ASan/TSan/UBSan/LSan，需 Clang 编译时启用）

## 构建命令

```bash
mkdir -p build && cd build
cmake .. -DOPENSSL_ROOT_DIR=/opt/homebrew/opt/openssl@3  # macOS 需指定 OpenSSL 路径
cmake --build . -j$(sysctl -n hw.ncpu)

# 运行全部测试
ctest --output-on-failure

# 运行单个 demo
./src/basic/typedef_demo
./src/std/string_demo
./src/algorithm/sort_demo
./src/cpp17/structured_bindings_demo
./src/designpattern/singleton_demo

# 格式化
cmake --build . --target format
```

## 目录结构

```
studycpp/
├── src/
│   ├── basic/            # C++ 基础语法 demo（typedef 等）
│   ├── std/              # 标准库 demo（14 个）
│   ├── algorithm/        # 经典算法 demo（15 个）
│   ├── cpp17/            # C++17 特性 demo（10 个）
│   ├── designpattern/    # GoF 23 设计模式 demo
│   └── sanitizer/        # Sanitizer 工具演示（9 个，含 README）
│   ├── security/         # 密码学工具箱 (OpenSSL 3.x, 27 个)
└── tests/                # Google Test 单元测试
```

## Demo 组织原则

- **独立编译运行单元**：每个 demo 由 `.h`（函数/类定义）和 `.cpp`（`main()` 函数）组成，可独立编译和运行
- 新增 demo：在同目录下添加 `.h` / `.cpp` 一对文件，并在该目录的 `CMakeLists.txt` 中追加一行 `add_executable`
- 模板类或需在头文件中完整定义的 demo（如 `iterator_pattern_demo.h`）直接在 `.h` 中实现
- 设计模式的 `.h` 文件需包含注释：模式名称（中英文）及使用场景

## 单元测试

- 所有测试位于 `tests/` 目录，命名规范 `test_<demo名>.cpp`
- 测试文件 include 对应头文件即可，无需额外依赖
- 新增测试：添加文件到 `tests/`，并在 `tests/CMakeLists.txt` 中注册
- 目标可执行文件名与 demo 名一致（如 `string_demo` → `test_string_demo.cpp`）
- 设计模式测试文件使用 `test_<pattern>_demo.cpp` 命名（如 `test_singleton_demo.cpp`）

## 注意事项

- 避免同名函数跨头文件重复定义（之前 `safe_divide` 在 optional_demo 和 exception_demo 中冲突，已重命名）
- 设计模式中若有循环引用（如 `state_demo.h` 的 IdleState ↔ HasCoinState），inline 方法需放在两个类定义之后
- `export` 是 C++ 保留关键字，方法名需避开（已改为 `do_export`）
- `make_from_tuple` 要求构造参数类型与 tuple 元素类型严格匹配
- security 模块使用 OpenSSL 3.x EVP API，macOS 需通过 Homebrew 安装 OpenSSL 3（系统自带的是 LibreSSL）
- Ed25519 签名必须使用 `EVP_DigestSign` one-shot API，不能使用 DigestSignUpdate/Final 模式
- Argon2、bcrypt、BLAKE3、后量子密码（Kyber/Dilithium）不在 OpenSSL 中，需独立库
- sanitizer 模块的 demo 故意包含 bug，需通过 CMake 选项启用对应 sanitizer 才能看到检测报告
- ASan 和 TSan 不可同时启用；ASan 和 MSan 不可同时启用
- MSan 仅 Clang 支持，且 macOS ARM64 不支持（`-fsanitize=memory` 编译报错）
- TSan 在 macOS 上可用，但 Linux 上检测更完整
- sanitizer demo 不带 sanitizer 编译也能运行（bug 静默发生，无告警）
