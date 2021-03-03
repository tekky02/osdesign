#! /bin/bash

find . -regex '.*[.]\(c\|cpp\|cc\|hpp\|h\)$' | xargs clang-format -i

