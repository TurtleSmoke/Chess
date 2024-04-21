#!/bin/bash

# Run clang-tidy on all files in the project
# shellcheck disable=SC2046
clang-tidy -extra-arg=-std=c++17 $(find src -name "*.cc" -o -name "*.hh") -- -Isrc/engine