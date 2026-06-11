add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../googletest
    googletest-build
)

enable_testing()

add_executable(
    tests
    sequence_generator_tests.cpp
    rule_generator_tests.cpp
)

target_include_directories(
    tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(
    tests
    GTest::gtest_main
    lab5
)

include(GoogleTest)

gtest_discover_tests(tests)