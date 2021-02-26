// test for new system call hello_world.
// created by tekky on 2021.2.18.
// Copyright © 2021 tekky. All rights reserved.

#include <linux/kernel.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

int main() {
  long result = syscall(333);
  printf("result of syscall(333) = %ld.\n", result);
  return 0;
}
