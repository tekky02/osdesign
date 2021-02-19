// created by tekky on 2021.2.19.
// Copyright(c) 2021 tekky.

#include <linux/cdev.h>
#include <linux/device.h>
// #include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>

#define BUFSIZE 2048

MODULE_LICENSE("GPL");
MODULE_AUTHOR("tekky");
MODULE_DESCRIPTION("tekky's character device for linux kernel 4.19");
MODULE_VERSION("0.1");

static int busy = 0; // if the device is busy.
static int tcdev_major = 0;

// open the device.
static int my_open(struct inode *inode, struct file *file);

// release the device.
static int my_release(struct inode *inode, struct file *file);

// read from the device to user buffer.
static ssize_t my_read(struct file *file, char __user *user_buffer, size_t size,
                       loff_t *offset);

// write items in user buffer to the device.
static ssize_t my_write(struct file *file, const char __user *user_buffer,
                        size_t size, loff_t *offset);

struct tcdev_data {
  struct cdev tcdev;
  // my data starts here...
  char buffer[BUFSIZE];
  size_t size;
};

static struct tcdev_data my_device;

static int my_open(struct inode *inode, struct file *file) {
  if (busy == 0) {
    struct tcdev_data *my_data =
        container_of(inode->i_cdev, struct tcdev_data, tcdev);
    file->private_data = my_data;
    try_module_get(THIS_MODULE);
    // initialize device..
    busy = 1;
    return 0;
  } else {
    printk(KERN_INFO "From tekky_chrdev: device is busy now!\n");
    return -EBUSY;
  }
}

static int my_release(struct inode *inode, struct file *file) {
  busy = 0;
  module_put(THIS_MODULE);
  return 0;
}

static ssize_t my_read(struct file *file, char __user *user_buffer, size_t size,
                       loff_t *offset) {
  struct tcdev_data *my_data = (struct tcdev_data *)file->private_data;
  ssize_t remain = my_data->size - *offset;
  ssize_t len = remain < size ? remain : size;
  if (len <= 0) {
    return 0;
  }
  // read data from my_data->buffer to user buffer
  if (copy_to_user(user_buffer, my_data->buffer + *offset, len)) {
    return -EFAULT;
  }
  *offset += len;
  return len;
}

static ssize_t my_write(struct file *file, const char __user *user_buffer,
                        size_t size, loff_t *offset) {
  struct tcdev_data *my_data = (struct tcdev_data *)file->private_data;
  int remain = my_data->size - *offset;
  ssize_t len = remain < size ? remain : size;

  if (len <= 0) {
    return 0;
  }
  // read data from user buffer to my_data->buffer.
  if (copy_from_user(my_data->buffer + *offset, user_buffer, len)) {
    return -EFAULT;
  }
  *offset += len;
  return len;
}

const struct file_operations tcdev_fops = {.owner = THIS_MODULE,
                                           .open = my_open,
                                           .read = my_read,
                                           .write = my_write,
                                           .release = my_release};

static int tcdev_init(void) {
  dev_t dev;
  int err = alloc_chrdev_region(&dev, 0, 1, "tekky_chrdev");
  if (err != 0) {
    printk(KERN_INFO "From tekky_chrdev: module init_failed.\n");
    return err;
  }
  tcdev_major = MAJOR(dev);
  char initial_msg[] = "hello, this is tekky_chrdev!\n";
  my_device.size = sizeof(initial_msg);
  strncpy(my_device.buffer, initial_msg,
          sizeof(initial_msg)); // put initial message.

  cdev_init(&my_device.tcdev, &tcdev_fops);
  cdev_add(&my_device.tcdev, MKDEV(tcdev_major, 0), 1);
  printk(KERN_INFO
         "From tekky_chrdev: module init success with major number: %d\n",
         tcdev_major);
  return 0;
}

static void tcdev_exit(void) {
  cdev_del(&my_device.tcdev);
  unregister_chrdev_region(MKDEV(tcdev_major, 0), 1);
  printk(KERN_INFO "From tekky_chrdev: Goodbye!\n");
}

module_init(tcdev_init);
module_exit(tcdev_exit);
