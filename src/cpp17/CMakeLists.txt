# cpp17 模块：每个特性自成独立可执行文件

add_executable(structured_bindings_demo structured_bindings_demo.cpp)
add_executable(if_initializer_demo if_initializer_demo.cpp)
add_executable(string_view_demo string_view_demo.cpp)
add_executable(if_constexpr_demo if_constexpr_demo.cpp)
add_executable(variant_demo variant_demo.cpp)
add_executable(any_demo any_demo.cpp)
add_executable(apply_demo apply_demo.cpp)
add_executable(fold_expressions_demo fold_expressions_demo.cpp)
add_executable(filesystem_demo filesystem_demo.cpp)
add_executable(inline_variables_demo inline_variables_demo.cpp)

# filesystem 在某些平台上需要链接 stdc++fs
find_library(STD_FS_LIB stdc++fs)
if (STD_FS_LIB)
    target_link_libraries(filesystem_demo PRIVATE ${STD_FS_LIB})
endif ()
