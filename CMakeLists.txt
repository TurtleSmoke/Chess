cmake_minimum_required(VERSION 3.12)
project(Chess
        VERSION 0.0.0
        DESCRIPTION "Chess engine"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC
        "src/engine/board.cc"
)

# Headers (for IDEs)
set(HDR
        "src/engine/bitboard.hh"
        "src/engine/board.hh"
        "src/engine/moves/move.hh"
        "src/engine/moves/pawn.hh"
)

set(CMAKE_MODULE_PATH "third_party")

add_executable(chess)
include_directories(
        "src"
        "src/engine"
        "src/engine/moves"
)
target_sources(chess PRIVATE "src/main.cc" ${SRC})
target_compile_options(chess PRIVATE -Wall -Werror -Wextra -pedantic)

# Test sources
file(GLOB_RECURSE SRC_UNIT_TEST ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/*.cc)

# Used for both tests and coverage
enable_testing()
find_package(Threads REQUIRED)
add_subdirectory(third_party/googletest)

# Run tests only.
add_executable(unit_test)
target_sources(unit_test PRIVATE
        ${SRC}
        ${SRC_UNIT_TEST})
target_compile_options(unit_test PRIVATE -O0 -g3 -fsanitize=address)
target_link_options(unit_test PRIVATE -O0 -g3 -fsanitize=address)
target_link_libraries(unit_test PRIVATE Threads::Threads gtest gtest_main gmock_main)

add_test(NAME unit_test COMMAND unit_test)

# Run coverage, It is a copy of unit_test with coverage flags, so that it can run both in CI without any issues.
add_executable(coverage)
target_sources(coverage PRIVATE
        ${SRC}
        ${SRC_UNIT_TEST})
target_compile_options(coverage PRIVATE -O0 -g3 --coverage -fno-inline -fno-inline-small-functions -fno-default-inline -fkeep-inline-functions -DNDEBUG) # -DNDEBUG is to disable assert, gives worse branch coverage
target_link_options(coverage PRIVATE -O0 -g3 --coverage -fno-inline -fno-inline-small-functions -fno-default-inline -fkeep-inline-functions -DNDEBUG)
target_link_libraries(coverage PRIVATE Threads::Threads gtest gtest_main gmock_main)

# Run gcov
add_custom_target(
        gcov
        COMMAND coverage
        COMMAND gcov -abcfu `find CMakeFiles/coverage.dir -name \"*.cc.o\"`
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS coverage
)


# Run gcovr
add_custom_target(
        gcovr
        COMMAND gcovr -r ${CMAKE_CURRENT_SOURCE_DIR} --exclude ${CMAKE_CURRENT_SOURCE_DIR}/tests/ --exclude ${CMAKE_CURRENT_SOURCE_DIR}/third_party/ --use-gcov-files --gcov-ignore-parse-errors --keep --html --html-details -o coverage.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS gcov
)
