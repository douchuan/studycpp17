# sanitizer 模块：工业级内存安全/线程安全/泄漏检测工具演示
#
# 每个 demo 故意触发特定类型的 bug，用对应 sanitizer 运行即可看到检测报告。
# ASan 类 demo：用 ASAN_OPTIONS 配置
# TSan 类 demo：仅支持 Clang 编译
# LSan 类 demo：通常随 ASan 一起启用

cmake_minimum_required(VERSION 3.14)

option(SANITIZE_ADDRESS "Enable AddressSanitizer" OFF)
option(SANITIZE_THREAD "Enable ThreadSanitizer" OFF)
option(SANITIZE_UNDEFINED "Enable UndefinedBehaviorSanitizer" OFF)
option(SANITIZE_MEMORY "Enable MemorySanitizer (Clang only)" OFF)
option(SANITIZE_LEAK "Enable LeakSanitizer" OFF)

# --- 工具链检测 ---
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
    set(IS_CLANG TRUE)
else ()
    set(IS_CLANG FALSE)
endif ()

# --- Sanitizer target（故意包含 bug，仅用于演示） ---
add_executable(asan_overflow_demo asan_overflow_demo.cpp)
add_executable(asan_uaf_demo asan_uaf_demo.cpp)
add_executable(asan_double_free_demo asan_double_free_demo.cpp)
add_executable(tsan_race_demo tsan_race_demo.cpp)
add_executable(tsan_fixed_demo tsan_fixed_demo.cpp)
add_executable(ubsan_demo ubsan_demo.cpp)
add_executable(leak_demo leak_demo.cpp)
add_executable(msan_demo msan_demo.cpp)
add_executable(static_analysis_demo static_analysis_demo.cpp)

# 使用列表语法确保每个 flag 独立传递
list(APPEND ASAN_FLAGS -fsanitize=address -fno-omit-frame-pointer -g -O1)
list(APPEND UBSAN_FLAGS -fsanitize=undefined -fno-omit-frame-pointer -g -O1)
list(APPEND TSAN_FLAGS -fsanitize=thread -fno-omit-frame-pointer -g -O1)
list(APPEND MSAN_FLAGS -fsanitize=memory -fsanitize-memory-track-origins -fno-omit-frame-pointer -g -O1)
list(APPEND LSAN_FLAGS -fsanitize=leak -fno-omit-frame-pointer -g -O1)

# --- ASan 组 ---
if (SANITIZE_ADDRESS)
    foreach (tgt asan_overflow_demo asan_uaf_demo asan_double_free_demo leak_demo)
        target_compile_options(${tgt} PRIVATE ${ASAN_FLAGS})
        target_link_options(${tgt} PRIVATE ${ASAN_FLAGS})
    endforeach ()
endif ()

# --- UBSan ---
if (SANITIZE_UNDEFINED)
    target_compile_options(ubsan_demo PRIVATE ${UBSAN_FLAGS})
    target_link_options(ubsan_demo PRIVATE ${UBSAN_FLAGS})
endif ()

# --- TSan ---
if (SANITIZE_THREAD)
    if (NOT IS_CLANG)
        message(WARNING "ThreadSanitizer requires Clang/GCC. Skipping TSan targets.")
    else ()
        target_compile_options(tsan_race_demo PRIVATE ${TSAN_FLAGS})
        target_link_options(tsan_race_demo PRIVATE ${TSAN_FLAGS})
        target_compile_options(tsan_fixed_demo PRIVATE ${TSAN_FLAGS})
        target_link_options(tsan_fixed_demo PRIVATE ${TSAN_FLAGS})
    endif ()
endif ()

# --- MSan（仅 Clang，不能和 ASan 同时启用） ---
if (SANITIZE_MEMORY)
    if (NOT IS_CLANG)
        message(WARNING "MemorySanitizer requires Clang. Skipping MSan target.")
    else ()
        target_compile_options(msan_demo PRIVATE ${MSAN_FLAGS})
        target_link_options(msan_demo PRIVATE ${MSAN_FLAGS})
    endif ()
endif ()

# --- LSan ---
if (SANITIZE_LEAK)
    if (NOT SANITIZE_ADDRESS)
        # LSan 可作为独立 sanitizer 使用
        target_compile_options(leak_demo PRIVATE ${LSAN_FLAGS})
        target_link_options(leak_demo PRIVATE ${LSAN_FLAGS})
    endif ()
    # ASan 已内置 LSan，若同时开启则不需要额外 flag
endif ()

# --- 静态分析（clang-tidy） ---
find_program(CLANG_TIDY clang-tidy)
if (CLANG_TIDY)
    foreach (tgt static_analysis_demo asan_overflow_demo tsan_race_demo ubsan_demo)
        if (TARGET ${tgt})
            set_property(TARGET ${tgt} PROPERTY CXX_CLANG_TIDY
                ${CLANG_TIDY};-checks=-*,bugprone-*,cppcoreguidelines-*,readability-*,performance-*)
        endif ()
    endforeach ()
endif ()
