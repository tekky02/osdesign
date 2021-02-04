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

static bool is_directory(const char *file) {
  struct stat st;
  if (stat(file, &st) == -1) {
    perror(file);
    exit(EXIT_FAILURE);
  }
  return S_ISDIR(st.st_mode);
}

static void show_tip(const char *executable) {
  fprintf(stderr, "Try '%s --help' for more information.\n", executable);
}

static void print_help(const char *executable) {
  printf("Usage: %s [option]... source dest.\n", executable);
  printf("   or: %s [option]... source... directory.\n", executable);
  printf("Copy source to dest, or multiple sources to directory.\n");
  exit(EXIT_SUCCESS);
}

void arg_check(int argc, const char *argv[]) {
  switch (argc) {
  case 1:
    fprintf(stderr, "%s: missing file operand.\n", argv[0]);
    show_tip(argv[0]);
    exit(EXIT_FAILURE);
  case 2:
    if (argv[1][0] == '-') {
      if (strcmp("--help", argv[1]) == 0) {
        print_help(argv[0]);
      } else {
        fprintf(stderr, "%s: invalid option '%s'.\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
      }
    } else {
      fprintf(stderr, "%s: missing destination after %s.\n", argv[0], argv[1]);
      show_tip(argv[0]);
      exit(EXIT_FAILURE);
    }
  case 3:
    copy(argv[1], argv[2]);
    break;
  default: // copy source... directory
           // make sure argv[argc-1] is a directory
    if (is_directory(argv[argc - 1])) {
      // for source... copy(source, dest)
      for (int i = 1; i < argc - 1; ++i) {
        copy(argv[i], argv[argc - 1]);
      }
    } else {
      fprintf(stderr, "%s: target '%s' is not a directory.\n", argv[argc - 1]);
      exit(EXIT_FAILURE);
    }
  }
}

void run_process(int argc, const char *argv[]) { arg_check(argc, argv); }

void prepare(const char *src, const char *dest) {
  src_name_size = 0;
  struct stat st;
  char prefix[PATH_MAX];
  if (stat(src, &st) == -1) {
    perror(src);
    exit(EXIT_FAILURE);
  } else if (S_ISDIR(st.st_mode)) {
    src_name_size = strlen(src) + 1;
    struct stat dst;
    if (stat(dest, &dst) == -1) {
      snprintf(prefix, PATH_MAX, "%s", dest);
    } else if (S_ISDIR(dst.st_mode)) {
      snprintf(prefix, PATH_MAX, "%s/%s", dest, src);
    } else {
      fprintf(stderr, "can not overwrite %s\n", dest);
      exit(EXIT_FAILURE);
    }
    mkdir(prefix, st.st_mode);
  }
  open_dest(prefix, src);
}

void copy(const char *src, const char *dest) { prepare(src, dest); }

void copy_content(int srcfd, int destfd) {
  char buffer[BUFSIZE];
  size_t n = 0;
  while ((n = read(srcfd, buffer, BUFSIZE)) > 0) {
    write(destfd, buffer, n);
  }
}

void copy_wrapper(const char *src, const char *dest) {
  if (is_directory(src)) {
    copy_directory(src, dest);
  } else {
    copy_regular_file();
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
