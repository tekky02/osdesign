#! /bin/bash
# created by tekky on 2021.2.18.

find ./include ./src ./test -regex '.*[.]\(c\|cpp\|cc\|hpp\|h\)$' | xargs clang-format -i

