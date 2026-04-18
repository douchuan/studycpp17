# Sanitizer 工具箱

C++ 工程内存安全/线程安全/泄漏检测的工业级解决方案演示。每个 demo **故意包含 bug**，用于展示 sanitizer 如何捕获问题。

## 工具矩阵

| 工具 | 检测目标 | 编译器 | 平台支持 |
|------|---------|--------|---------|
| **ASan** (AddressSanitizer) | 越界、UAF、Double Free、Stack/Heap 溢出 | Clang/GCC | 全平台 |
| **TSan** (ThreadSanitizer) | 数据竞态条件 | Clang/GCC | Linux/macOS |
| **UBSan** (UndefinedBehaviorSanitizer) | 未定义行为：空指针、有符号溢出、对齐错误 | Clang/GCC | 全平台 |
| **LSan** (LeakSanitizer) | 内存泄漏 | Clang | Linux 全支持 / macOS 有限 |
| **MSan** (MemorySanitizer) | 未初始化内存读取 | **仅 Clang** | Linux 全支持 / **macOS ARM 不支持** |
| **clang-tidy** | 静态分析：API 误用、性能、规范 | Clang | 全平台 |

## 快速开始

### ASan — 内存安全

```bash
# 编译（启用 ASan）
cmake -S .. -B build_asan -DSANITIZE_ADDRESS=ON
cmake --build build_asan --target asan_overflow_demo

# 运行（bug 会被精确定位到文件+行号）
./build_asan/src/sanitizer/asan_overflow_demo
```

**检测报告示例**：
```
ERROR: AddressSanitizer: heap-buffer-overflow on address 0x603000001c14
    #0 main asan_overflow_demo.cpp:11
SUMMARY: heap-buffer-overflow asan_overflow_demo.cpp:11 in main
```

### TSan — 线程安全

```bash
cmake -S .. -B build_tsan -DSANITIZE_THREAD=ON
cmake --build build_tsan --target tsan_race_demo
cmake --build build_tsan --target tsan_fixed_demo
./build_tsan/src/sanitizer/tsan_race_demo    # 有 race
./build_tsan/src/sanitizer/tsan_fixed_demo    # 无告警
```

### UBSan — 未定义行为

```bash
cmake -S .. -B build_ubsan -DSANITIZE_UNDEFINED=ON
cmake --build build_ubsan --target ubsan_demo
./build_ubsan/src/sanitizer/ubsan_demo
```

### LSan — 内存泄漏

```bash
# 独立模式（Linux 推荐）
cmake -S .. -B build_lsan -DSANITIZE_LEAK=ON

# 随 ASan 一起启用（macOS 推荐，ASan 内置 LSan）
cmake -S .. -B build_asan -DSANITIZE_ADDRESS=ON
```

### clang-tidy — 静态分析

```bash
# 安装
brew install llvm  # macOS
# 编译时自动启用（find_program 会检测 clang-tidy）
cmake -S .. -B build_tidy
cmake --build build_tidy --target static_analysis_demo
```

## CMake 集成（你的项目）

最简集成方式，在顶层 CMakeLists.txt 中添加：

```cmake
# 编译时传 sanitizer 选项即可
# cmake -DSANITIZE_ADDRESS=ON ..
option(SANITIZE_ADDRESS "Enable ASan" OFF)
if (SANITIZE_ADDRESS)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g)
    add_link_options(-fsanitize=address)
endif ()
```

推荐 CI/CD 流程：
1. **Debug 构建** + `SANITIZE_ADDRESS=ON` 运行全量测试
2. **Debug 构建** + `SANITIZE_THREAD=ON` 运行并发测试
3. **Debug 构建** + `SANITIZE_UNDEFINED=ON` 运行全量测试
4. **clang-tidy** 在 MR/PR 时自动检查

## 平台限制

| 平台 | ASan | TSan | UBSan | LSan | MSan |
|------|------|------|-------|------|------|
| Linux x86_64 | ✅ | ✅ | ✅ | ✅ | ✅ |
| macOS x86_64 | ✅ | ⚠️ | ✅ | ⚠️ | ❌ |
| macOS ARM64 | ✅ | ✅ | ✅ | ⚠️ | ❌ |

## Sanitizer 兼容性

- **不可组合**：ASan 和 TSan 不能同时启用；ASan 和 MSan 不能同时启用
- **UBSan** 可与 ASan 组合：`-fsanitize=address,undefined`
- **LSan** 已内置于 ASan（Linux 默认开启，macOS 需 `ASAN_OPTIONS=detect_leaks=1`）
- **编译器优化级别**：建议 `-O1`（`-O0` 会漏检，`-O2` 可能改变 bug 行为）
