// file copier.h.
// created by tekky on 2021.1.27.
// Copyright © 2021 tekky. All rights reserved.

#ifndef __COPIER_H__
#define __COPIER_H__

#include <stdbool.h>
#include <stddef.h>
#include <sys/stat.h>

#define BUFSIZE 1024U

typedef enum {
  TOO_FEW_ARGS, // no enough args provided.
  WRONG_DEST    // destination is not reachable.
} error_type;

#ifdef __cplusplus
extern "C" {
#endif

// wrapper provided for client
void copy(int argc, const char *argv[]);

// check if provided arguments is valid
void arg_check(int argc, const char *argv[]);

// copy the content of scrfd to destfd.
void copy_content(const char *src, const char *dest);

// function for src is a regular file.
void copy_regular_file(const char *src, const char *dest);

// function for src is a directory.
// @brief if dest is a directory, then copy `src/file1` to `dest/src/file1`,
// jump 0. if there is no dest, copy folder `src` to `dest`, for example,
// `src/file1` -> `dest/file1`, jump `src`.
void copy_directory(const char *src, const char *dest, size_t jump);

#ifdef __cplusplus
}
#endif
#endif // __COPIER_H__
