// file copier.h.
// created by tekky on 2021.1.27.
// © tekky all rights reserved.

#ifndef __COPIER_H__
#define __COPIER_H__

#include <stdbool.h>
#include <sys/stat.h>

#define BUFSIZE 1024U

typedef enum {
  TOO_FEW_ARGS, // no enough args provided.
  WRONG_DEST    // destination is not reachable.
} error_type;

#ifdef __cplusplus
extern "C" {
#endif

// print help information.
void print_help();

// report error message in detail.
void report_error(const char *argv[], int argc, error_type type);

// copier's interface.
void copy(const char *src, const char *dest);

// copy the content of scrfd to destfd.
void copy_content(int srcfd, int destfd);

// create destination file descriptor.
// will create destination file and return its fd.
void open_dest();

#ifdef __cplusplus
}
#endif
#endif // __COPIER_H__
