#!/bin/bash

# Run clang-format on all source files in the project
# shellcheck disable=SC2046
clang-tidy $(find src/ -name '*.cc' -or -name '*.hh')
