// created by tekky on 2021.2.18.
// arch/.../sys.c

asmlinkage long SYSCALL_DEFINE0(hello_world) {
  printk("from kernel-tekky: hello, world!\n);
  return 0;
}
