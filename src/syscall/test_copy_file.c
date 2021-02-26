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
