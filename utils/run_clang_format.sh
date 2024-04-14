#!/bin/bash

# Run clang-format on all source files in the project
# shellcheck disable=SC2046
clang-format -i --verbose -style=file $(find src/ test/ -name '*.cc' -or -name '*.hh')
