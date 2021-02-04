#! /bin/bash

find ./include ./src ./test -regex '.*[.]\(c\|cpp\|cc\|hpp\|h\)$' | xargs clang-format -i

