cmake_minimum_required(VERSION 3.12)
project(Chess
        VERSION 0.0.0
        DESCRIPTION "Chess engine"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC
        "src/test_cov/test_tmp.cc"
)

include_directories(
        "src"
        "src/test_cov"
)

set(CMAKE_MODULE_PATH "third_party")

add_executable(CHESS)
target_sources(CHESS PRIVATE "src/main.cc" ${SRC})
target_compile_options(CHESS PRIVATE -Wall -Werror -Wextra -pedantic)

# Test sources
file(GLOB_RECURSE SRC_UNIT_TEST ${CMAKE_CURRENT_SOURCE_DIR}/test/unit/*.cc)

# Global flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")

# Used for both test and coverage
enable_testing()
find_package(Threads REQUIRED)
add_subdirectory(third_party/googletest)

# Run test only.
add_executable(unit_test)
target_sources(unit_test PRIVATE
        ${SRC}
        ${SRC_UNIT_TEST})
target_compile_options(unit_test PRIVATE -O0 -g3 -fsanitize=address)
target_link_options(unit_test PRIVATE -O0 -g3 -fsanitize=address)
target_link_libraries(unit_test PRIVATE Threads::Threads gtest gtest_main)

add_test(
        NAME Unit
        COMMAND ./unit_test
)
