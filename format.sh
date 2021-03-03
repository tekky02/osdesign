#! /bin/bash

find . -regex '.*[.]\(c\|cpp\|cc\|hpp\|hh\|h\)$' | xargs clang-format -i

