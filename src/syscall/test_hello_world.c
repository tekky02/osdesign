// created by tekky on 2021.2.18.
// test for new system call (333)hello_world.

#include <stdio.h>
#include <sys/syscall.h>

int main() {
  long result = syscall(333);
  printf("result of syscall(333) = %ld.\n", res);
  return 0;
}
