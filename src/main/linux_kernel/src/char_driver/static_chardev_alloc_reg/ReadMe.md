## loading module

## unload module

## checking char device 
```
cat /procs/devices
```


## Adding device as a node at /dev


### Why Character Drivers Are Added to /dev

Character drivers are added to /dev to expose hardware devices as regular files, following the Unix philosophy that "everything is a file."

Without the /dev directory, standard applications would not know how to communicate with the kernel or physical hardware. Placing them in /dev provides three key benefits:
• Unified Interface: Applications can use standard C library functions (open, read, write, close) to interact with hardware, just as they do with standard text files.
• Access Control: The operating system can use standard file permissions (chmod, chown) to control which users or groups can access specific hardware.
• Abstraction: The application does not need to know the complex low-level registers or hardware protocols. It simply reads and writes bytes to the file, and the driver handles the hardware translation.


```
$ sudo insmod static_alloc_device_reg.ko 

$ sudo mknod /dev/ADVDev0 c 300 0

$ ls -l /dev/ADVDev0 
crw-r--r-- 1 root root 300, 0 okt 24 17:24 /dev/ADVDev0

$ sudo rmmod static_alloc_device_reg   ## Even rmmod is done, device is present at /dev/ADVDev0. Need to manually delete.

$ ls -l /dev/ADVDev0 
crw-r--r-- 1 root root 300, 0 okt 24 17:24 /dev/ADVDev0

$ sudo rm /dev/ADVDev0 

$ ls -l /dev/ADVDev0 
ls: cannot access '/dev/ADVDev0': No such file or directory

```

