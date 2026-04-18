# 测试模块

add_executable(unit_tests
    test_string_demo.cpp
    test_vector_demo.cpp
    test_optional_demo.cpp
    test_map_demo.cpp
    test_set_demo.cpp
    test_smart_ptr_demo.cpp
    test_tuple_demo.cpp
    test_array_demo.cpp
    test_iterator_demo.cpp
    test_chrono_demo.cpp
    test_stringstream_demo.cpp
    test_function_demo.cpp
    test_exception_demo.cpp
    test_fstream_demo.cpp
    test_sort_demo.cpp
    test_search_demo.cpp
    test_transform_demo.cpp
    test_binary_search_demo.cpp
    test_quicksort_demo.cpp
    test_mergesort_demo.cpp
    test_heap_demo.cpp
    test_linked_list_demo.cpp
    test_tree_demo.cpp
    test_graph_demo.cpp
    test_dp_demo.cpp
    test_sliding_window_demo.cpp
    test_two_pointers_demo.cpp
    test_backtracking_demo.cpp
    test_bit_manipulation_demo.cpp
    test_structured_bindings_demo.cpp
    test_if_initializer_demo.cpp
    test_string_view_demo.cpp
    test_if_constexpr_demo.cpp
    test_variant_demo.cpp
    test_any_demo.cpp
    test_apply_demo.cpp
    test_fold_expressions_demo.cpp
    test_inline_variables_demo.cpp
    test_singleton_demo.cpp
    test_factory_method_demo.cpp
    test_abstract_factory_demo.cpp
    test_builder_demo.cpp
    test_prototype_demo.cpp
    test_adapter_demo.cpp
    test_bridge_demo.cpp
    test_composite_demo.cpp
    test_decorator_demo.cpp
    test_facade_demo.cpp
    test_flyweight_demo.cpp
    test_proxy_demo.cpp
    test_chain_of_responsibility_demo.cpp
    test_command_demo.cpp
    test_interpreter_demo.cpp
    test_iterator_pattern_demo.cpp
    test_mediator_demo.cpp
    test_memento_demo.cpp
    test_observer_demo.cpp
    test_state_demo.cpp
    test_strategy_demo.cpp
    test_template_method_demo.cpp
    test_visitor_demo.cpp
)

target_include_directories(unit_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src/std
    ${CMAKE_SOURCE_DIR}/src/algorithm
    ${CMAKE_SOURCE_DIR}/src/cpp17
    ${CMAKE_SOURCE_DIR}/src/designpattern
)

target_link_libraries(unit_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)
