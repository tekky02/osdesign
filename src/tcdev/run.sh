#! /bin/bash

sudo dmesg -C

# delete previous device.
if [ -e /dev/tekky_chrdev ]; then
	sudo rm /dev/tekky_chrdev
fi

# if module tekky_chrdev is installed then delete it
lsmod | grep tekky_chrdev

if [ $? -eq 0 ]; then
	sudo rmmod tekky_chrdev
fi

make && make install

major=$(dmesg | grep -Eo '[0-9]+$')

# create device.
sudo mknod /dev/tekky_chrdev c $major 0

if [ $? -eq 0 ]; then
	sudo chown $USER /dev/tekky_chrdev
fi
