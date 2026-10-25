#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>

// #include <linux/cdev.h>

int major = 300;
int minor = 0;

dev_t dev;
char* name = "AutoADVDev";
struct class* dev_class;  // sysfs class structure

static int hello_init(void) {

	int ret;
	dev = MKDEV(major, minor);
	printk(KERN_INFO "HELLO WORLD first statically MAJOR and MINOR device register");
	if((ret = register_chrdev_region(dev, 4, name)) < 0) {
		return ret;
	}
	// creating structure class followed by device creation 
	if ( (dev_class = class_create(THIS_MODULE, "AdvClass")) == NULL) {	// since kernel is lower < 6.4 take two argument owner and device name while 6.4 >= takes only device name
		printk(KERN_INFO "Cannot create the struct class \n");
	}
	if ((device_create(dev_class, NULL, dev, NULL, name)) == NULL ) {
		printk(KERN_INFO "Cannot create device 1\n");
	}
	printk(KERN_INFO "device register and mapped to /dev through sysfs succeddfully");
	return 0;
}

static void hello_exit(void) {
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	unregister_chrdev_region(dev, 4);
	printk(KERN_INFO "BYE WORLD, destroy device from sysfsclass follow by unregistered dev successfully");

}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("TEAM");
MODULE_DESCRIPTION("Statically dev registeration with sysfs device creation module");
MODULE_LICENSE("GPL");
