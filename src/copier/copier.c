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
      fprintf(stderr, "%s: missing destination after '%s'.\n", argv[0],
              argv[1]);
      show_tip(argv[0]);
      exit(EXIT_FAILURE);
    }
  case 3: {
    struct stat sst;
    if (stat(argv[1], &sst) == -1) {
      perror(argv[1]);
      exit(EXIT_FAILURE);
    } else if (S_ISDIR(sst.st_mode)) {
      struct stat st;
      if (stat(argv[2], &st) == -1) {
        // dest not exists, copy src/* to dest/*.
        mkdir(argv[2], sst.st_mode);
        copy_directory(argv[1], argv[2],
                       strlen(argv[1]) +
                           1); // jump `src`, `src/file` -> `dest/file`.
      } else if (S_ISDIR(st.st_mode)) {
        // dest already exists, copy `src` to `dest/src`.
        char path[PATH_MAX];
        snprintf(path, PATH_MAX, "%s/%s", argv[2], argv[1]);
        mkdir(path, sst.st_mode); // create `dest/src` directory.
        copy_directory(argv[1], argv[2],
                       0); // no jump, `src/file` -> `dest/src/file`.
      } else {
        // dest is not a directory, but, for example, a regular file.
        fprintf(stderr, "%s: can not overwrite '%s'.\n", argv[0], argv[2]);
        exit(EXIT_FAILURE);
      }
    } else {
      copy_regular_file(argv[1], argv[2]);
    }
  } break;
  default: // copy source... directory
    if (is_directory(
            argv[argc - 1])) { // a directory named `dest` should already there.
      // for all sources copy source[i] to dest/source[i].
      for (int i = 1; i < argc - 1; ++i) {
        struct stat dst;
        if (stat(argv[i], &dst) == -1) {
          perror(argv[i]);
          exit(EXIT_FAILURE);
        } else if (S_ISDIR(dst.st_mode)) {
          char path[PATH_MAX];
          snprintf(path, PATH_MAX, "%s/%s", argv[argc - 1], argv[i]);
          mkdir(path, dst.st_mode);
          copy_directory(argv[i], argv[argc - 1], 0);
        } else {
          copy_regular_file(argv[i], argv[argc - 1]);
        }
      }
    } else {
      fprintf(stderr, "%s: target '%s' is not a directory.\n", argv[argc - 1]);
      exit(EXIT_FAILURE);
    }
  }
}

void copy(int argc, const char *argv[]) { arg_check(argc, argv); }

void copy_content(const char *src, const char *dest) {
  int srcfd = open(src, O_RDONLY | O_CLOEXEC);
  struct stat st;
  stat(src, &st);
  int destfd = open(dest, O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC, st.st_mode);

  char buffer[BUFSIZE];
  size_t n = 0;
  while ((n = read(srcfd, buffer, BUFSIZE)) > 0) {
    write(destfd, buffer, n);
  }
  close(srcfd);
  close(destfd);
}

void copy_regular_file(const char *src, const char *dest) {
  struct stat st;
  if (stat(dest, &st) == -1) { // no file named dest exists, free to create one
    copy_content(src, dest);
  } else if (S_ISDIR(st.st_mode)) {
    char dest_file[PATH_MAX];
    snprintf(dest_file, PATH_MAX, "%s/%s", dest, src);
    copy_content(src, dest_file);
  } else { // file named ${dest} already exists and is not directory.
    fprintf(stderr, "can not overwrite '%s'.\n", dest);
    exit(EXIT_FAILURE);
  }
}

void copy_directory(const char *src, const char *dest, size_t jump) {
  DIR *directory = opendir(src);
  struct dirent *file_entry = readdir(directory);
  while ((file_entry = readdir(directory)) != NULL) {
    if (file_entry->d_name[0] == '.') {
      continue;
    }
    char src_file[PATH_MAX];
    char dest_file[PATH_MAX];
    snprintf(src_file, PATH_MAX, "%s/%s", src, file_entry->d_name);
    snprintf(dest_file, PATH_MAX, "%s/%s", dest, src_file + jump);
    struct stat st;
    stat(src_file, &st);
    if (file_entry->d_type == DT_DIR) {
      mkdir(dest_file, st.st_mode);
      copy_directory(src_file, dest, jump);
    } else if (file_entry->d_type == DT_REG) {
      copy_content(src_file, dest_file);
    }
  }
  closedir(directory);
}
