// arch/.../sys.c

asmlinkage long SYSCALL_DEFINE0(hello_world) {
  printk("from kernel-tekky: hello, world!\n);
  return 0;
}
