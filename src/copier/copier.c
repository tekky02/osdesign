// file copier.c.
// created by tekky on 2021.1.27.
// © tekky all rights reserved.

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "copier/copier.h"

static int src_name_size = 0;

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

void prepare(const char *src, const char *dest) {
  struct stat st;
  char prefix[PATH_MAX];
  if (stat(src, &st) == -1) {
    perror(src);
  } else if (S_ISDIR(st.st_mode)) {
    src_name_size = strlen(src) + 1;
    struct stat dst;
    if (stat(dest, &dst) == -1) {
      snprintf(prefix, PATH_MAX, "%s", dest);
    } else if (S_ISDIR(dst.st_mode)) {
      snprintf(prefix, PATH_MAX, "%s/%s", dest, src);
    } else {
      fprintf(stderr, "can not overwrite %s\n", dest);
      exit(1);
    }
    mkdir(prefix, st.st_mode);
  }
  open_dest(prefix, src);
}

void copy(const char *src, const char *dest) { prepare(src, dest); }

void copy_content(int srcfd, int destfd) {
  char buffer[BUFSIZE];
  size_t n;
  while ((n = read(srcfd, buffer, BUFSIZE)) > 0) {
    write(destfd, buffer, n);
  }
}

void open_dest(const char *prefix, const char *src) {
  DIR *directory = opendir(src);
  struct dirent *file_entry = readdir(directory);
  while ((file_entry = readdir(directory)) != NULL) {
    if (file_entry->d_name[0] == '.') {
      continue;
    }
    char src_file[PATH_MAX];
    char dest_file[PATH_MAX];
    snprintf(src_file, PATH_MAX, "%s/%s", src, file_entry->d_name);
    snprintf(dest_file, PATH_MAX, "%s/%s", prefix, src_file + src_name_size);
    struct stat st;
    stat(src_file, &st);
    if (file_entry->d_type == DT_DIR) {
      mkdir(dest_file, st.st_mode);
      open_dest(prefix, src_file);
    } else if (file_entry->d_type == DT_REG) {
      int srcfd = open(src_file, O_RDONLY | O_CLOEXEC);
      int destfd =
          open(dest_file, O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC, st.st_mode);
      copy_content(srcfd, destfd);
      close(srcfd);
      close(destfd);
    }
  }
  closedir(directory);
}

void print_help() {}
