#!/bin/bash

# Run shellcheck on all files in the project
# shellcheck disable=SC2046
shellcheck $(find . -name "*.sh" -not -path "./third_party/*")
