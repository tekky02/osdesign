// sys.c.
// created by tekky on 2021.3.2.
// Copyright © 2021 tekky. All rights reserved.

// <<<=========================
// add my new syscall here
// 333 hello_world
// 334 copy_file
SYSCALL_DEFINE0(hello_world) {
  printk("[from kernel]: hello, world\n");
  return 0;
}

SYSCALL_DEFINE2(copy_file, const char *, from, const char *, to) {
  int n = 0;
  struct file *src_file;
  struct file *dest_file;
  loff_t off_src = 0;
  loff_t off_dest = 0;
  char buffer[1024];
  int bytes = 0;
  printk("[from kernel]: copy_file called.\n");
  src_file = filp_open(from, O_RDONLY, 0);
  if (src_file == NULL) {
    printk("[from kernel]: can't open %s.\n", from);
    return -EFAULT;
  }
  dest_file = filp_open(to, O_RDWR | O_CREAT, 0666);
  if (dest_file == NULL) {
    printk("[from kernel]: can't creat file %s.\n", to);
    return -EFAULT;
  }
  while ((n = kernel_read(src_file, buffer, 1024, &off_src)) > 0) {
    kernel_write(dest_file, buffer, n, &off_dest);
    bytes += n;
  }
  filp_close(src_file, NULL);
  filp_close(dest_file, NULL);
  return n;
}
