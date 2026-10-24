#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

int major = 300;
int minor = 0;

dev_t dev;
char* name = "ADVDev";

static int hello_init(void) {

	int ret;
	dev = MKDEV(major, minor);
	printk(KERN_INFO "HELLO WORLD first statically MAJOR and MINOR device register");
	if((ret = register_chrdev_region(dev, 4, name)) < 0) {
		return ret;
	}
	printk(KERN_INFO "device register succeddfully");
	return 0;
}

static void hello_exit(void) {
	unregister_chrdev_region(dev, 4);
	printk(KERN_INFO "BYE WORLD, unregistered successfully");

}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("TEAM");
MODULE_DESCRIPTION("Statically dev registeration module");
MODULE_LICENSE("GPL");
