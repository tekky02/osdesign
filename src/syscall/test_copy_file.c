// test_copy_file.c.
// created by tekky on 2021.2.18.
// Copyright © 2021 tekky. All rights reserved.
// test for new system call copy_file.

#include <linux/kernel.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

int main() {
  const char *file = "./test_copy_file.c";
  const char *dest = "dest_file.c";
  long result = syscall(334, file, dest);
  printf("result of copy_file: %ld.\n", result);
}
