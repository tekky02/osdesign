// file main.c.
// created by tekky on 2021.1.28.

#include <stdio.h>
#include <stdlib.h>

#include "copier/copier.h"

int main(const int argc, const char *argv[]) {
  printf("argc = %d\n", argc);
  for (int i = 0; i < argc; i++)
    printf("argv[%d]: %s\n", i, argv[i]);
  if (argc < 3) {
    fprintf(stderr, "error argument\n");
    exit(1);
  }
  copy(argv[1], argv[2]);
}
