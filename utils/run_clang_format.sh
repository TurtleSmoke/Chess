#!/bin/bash

# Run clang-format on all files in the project
# shellcheck disable=SC2046
clang-format -i -style=file --verbose $(find src/ test/ -name '*.cc' -o -name '*.hh') --