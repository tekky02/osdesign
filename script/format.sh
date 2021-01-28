#! /bin/bash

find ./include ./copier ./test -regex '.*\(c\|cpp\|cc\|hpp\|h\)$' | xargs clang-format -i

