install module

```shell
insmod sample_mod.ko
```

create device  
```shell
# need to know the major number.
mknod /dev/sample_dev c $major 0
```

delete device  
```shell
rm /dev/sample_dev
rmmod sample_mod
```
