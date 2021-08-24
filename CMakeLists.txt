cmake_minimum_required(VERSION 3.12)
project(Chess
        VERSION 0.0.0
        DESCRIPTION "Chess engine"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Source files
add_executable(CHESS src/main.cc)
target_compile_options(CHESS PRIVATE -Wall -Werror -Wextra -pedantic)


# Testing
enable_testing()
find_package(Threads REQUIRED)
add_subdirectory(third_party/googletest)
add_executable(unit_test test/test.cc)
target_compile_options(unit_test PRIVATE -Wall -Werror -Wextra -pedantic)
target_link_libraries(unit_test PRIVATE Threads::Threads gtest gtest_main)

add_test(
        NAME Unit
        COMMAND make unit_test
)
