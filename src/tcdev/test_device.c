// created by tekky on 2021.2.19.
// Copyright(c) 2021 tekky.

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024

int main() {
  char buf[BUFSIZE];
  int fd = open("/dev/tekky_chrdev", O_RDWR);
  if (fd == -1) {
    printf("open device failed!\n");
    exit(1);
  }
  printf("current message in the device:\n");
  read(fd, buf, BUFSIZE);
  printf("%s\n", buf);

  printf("input something: ");
  scanf("%s", buf);
  write(fd, buf, strlen(buf));

  printf("======after write=====\n");
  read(fd, buf, BUFSIZE);
  printf("%s\n", buf);

  close(fd);
  return 0;
}
