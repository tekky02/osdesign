// file copier.c.
// created by tekky on 2021.1.27.
// © tekky all rights reserved.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "copier/copier.h"

bool args_validation(const char *argv[], int argc) {
  if (argc <= 2) {
    return false;
  }
  return true;
}

void report_error(const char *argv[], int argc, error_type type) {
  switch (type) {
  case TOO_FEW_ARGS:
    fprintf(stderr, "too few arguments provided, please run 'bin/copier "
                    "--help' for help\n");
    break;
  case WRONG_DEST:
    break;
  }
}

void copy(int srcfd, int destfd) {
  char buffer[BUFSIZE];
  size_t n;
  while ((n = read(srcfd, buffer, BUFSIZE)) > 0) {
    write(destfd, buffer, BUFSIZE);
  }
}

int open_dest(const char *src, const char *dest) {
  struct stat st;
  if (stat(src, &st) == -1) {
    perror(src);
  } else {
    if (is_regular_file(st.st_mode)) {
      int srcfd = open(src, O_RDONLY);
      int destfd = open(dest, O_CREAT | O_WRONLY);
      copy(srcfd, destfd);
      close(srcfd);
      close(destfd);
    }
  }
}

void print_help() {}

bool is_regular_file(mode_t mode) {}

bool is_symbol_link(mode_t mode) {}
