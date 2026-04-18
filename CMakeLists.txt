cmake_minimum_required(VERSION 3.14)
project(studycpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(src/basic)
add_subdirectory(src/std)
add_subdirectory(src/algorithm)
add_subdirectory(src/cpp17)
add_subdirectory(src/designpattern)
add_subdirectory(src/security)
add_subdirectory(src/sanitizer)
add_subdirectory(tests)

# 源码格式化 target: cmake --build build --target format
find_program(CLANG_FORMAT clang-format)
if (CLANG_FORMAT)
    file(GLOB_RECURSE ALL_SRC
        src/*.h src/*.cpp
        tests/*.h tests/*.cpp
    )
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SRC}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Formatting source files with clang-format"
    )
else ()
    message(STATUS "clang-format not found, skipping format target")
endif ()

# 静态分析 target: cmake --build build --target analyze
find_program(CLANG_TIDY clang-tidy PATHS /opt/homebrew/opt/llvm/bin NO_DEFAULT_PATH)
if (CLANG_TIDY)
    file(GLOB_RECURSE ALL_SOURCES src/*.h src/*.cpp)
    # Exclude sanitizer directory (intentional bug demos)
    list(FILTER ALL_SOURCES EXCLUDE REGEX "src/sanitizer/.*")
    add_custom_target(analyze
        COMMAND ${CLANG_TIDY}
            --header-filter='src/.*'
            --checks='clang-analyzer-*,bugprone-*,modernize-*,performance-*,-modernize-use-trailing-return-type,-modernize-use-nodiscard,-modernize-avoid-c-arrays,-modernize-use-auto,-bugprone-easily-swappable-parameters,-bugprone-exception-escape'
            -p ${CMAKE_BINARY_DIR}
            ${ALL_SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running static analysis with clang-tidy"
    )
else ()
    message(STATUS "clang-tidy not found, skipping analyze target")
endif ()
