

```
# compile module and loading
$>  sudo make
$>  sudo insmod auto_dev_noding_chardev.ko 
$>  sudo dmesg

# device registered
$>  cat /proc/devices 

# sysfs/class has also created
$>  cd /sys/class/
$>  ls
$>  cd AdvClass/
$>  ls
$>  cd AutoADVDev
$>  ls

# Automatic node created
$>  ls -l /dev
$>  ls -l /dev/AutoADVDev

# removing and verify device unregistered and node removed
$>  sudo rmmod auto_dev_noding_chardev
$>  ls -l /dev/AutoADVDev
$>  cd /sys/class/
$>  ls
$>  dmesg

```
# Extra note 1
The class_create() function in the Linux kernel is declared in <linux/device.h> (specifically inside <linux/device/class.h> in modern kernel trees) and is used by device drivers to create a struct class pointer for registering device classes with sysfs. [1] (/goto?url=CAESfAHrOzAVGfeQPVsdpFgzy8xnTibOLdK2wY3w1waqqSwIy_S-8nonf0-4P51Oxb7d2NJk1SjFM8zBOp_owc6NhzmgtFmYAfNIqxXAN3woO99qGE8mQ_-t6EB4n1UFXDMvbxNIk3uu_zHRbsK8gEqy77C-N1WGaUVmle8_m5Q), [2] (/goto?url=CAESggEB6zswFaAYf1tPgsnqIqeZAIR6EDoiWB6afB5nQ_j5fnbVEnolmJNSuHtZh2c-MkzYysRVxsTZ75xd9nOLCiumnTSLLmIT5rQfjrAfQo8zBOoO701Us_TB01I-g_l1keeeB6_-I8ujsGalwqLsMi9ypdQDwr-miTOnMSztCI2-TZ_G), [3] (/goto?url=CAEScgHrOzAVWDDKG1r3FOa0XVqdyRm5V5mYYlzIFrxmn7tJDCN9aAJFB-aNICPgBR6OXhPnGbcwQumOxM24T5hIl8IWdoO7UwEEPphmHs2LQsgxZApZXEW_j5gHtU1obrvNUrWeeFN5VI608qerVIkSKkr7CQ), [4] (/goto?url=CAEShQEB6zswFbXzteShS7iem4CKI_-BxOZm6o87T_U1f-Pbts5iOjQrW1H_fW3R5BjJPuKn5qXSot5dlS_efohfK45LhO4MwmLdAeN2IEVQwgbnUSw3O4ad8S-B_muOQMCGowVWbTzGneVvFMcMW4wsMHIYT-ysczWbFYnH5PBwBoVLN0PRzVXT), [5] (/goto?url=CAESkgEB6zswFTWsb62h8g1aKDOEb0rlvXIsZ3YhwU8xbfJLSmv1SJHxli0kAYZxhgwkYwdGO8jOxh_rviMFk8xgIcMDzcl9tOPYl71ZnSFmdZHnXE_05R6ypcWqtEszUFudkkEOO2vGKtTdj6RUPq40dR8juAdBrQvI9kT6WWU-3TUTTT8uU4MSngDGXRPyJ3BEHrVq_A)

Function Syntax and API Changes

• Kernel 6.3 and older:c
struct class *class_create(struct module *owner, const char *name);
Use code with caution.

	• Requires two arguments: THIS_MODULE and the class name string. [1] (/goto?url=CAESfQHrOzAVVhz3wpe8FmgGuPiZhYBzjdNZrkDTEgk0NUcPplE0krz9ugi4jombb7VzHbRLBoAF7xtxzvLq_dPClWKJWK6UEHWJJ2-mkN8l1k1FdnJN6kFObOCvt57zIs5ZOWE3VWo2AWiAtcaou9B-2MywZ3L9uQbs2HqIUa3k), [2] (/goto?url=CAES1wEB6zswFdo6CfRCbNPO0I45de0p1kR-rCPJgOzb8zLo0P0IDF9aHxhGfwQGUsMgmhahuKYammJYM4wgcIcunYyynb2BepHYvwkr_ZtPGJMG_s61BR3de6gr84FtD3v2ueRVKJTBa-h9FZ8-MnAvaWVsJ7mJZAXCZkptuW8FcK-lNfRgABKjaYEU-5B70LjUkUsOG52Iw3hmiN878a--Klv63X5XSRQlDqXfZ9szWsamoRpQ058hSi_KVFIY3xFwy7ORA6hpp3-Ro-3uF7opIy6JIExAavscMA)
• Kernel 6.4 and newer:c
struct class *class_create(const char *name);
Use code with caution.

	• Simplified to take only a single argument (the class name string), removing THIS_MODULE. [1] (/goto?url=CAESbAHrOzAV9yJsNoNRWNf1f28r-nVIGJd_FT-IUsMs0dneUwDjV3b4mYRsnE1B8vGOXDr3uV_UmOVn9AxhuOxFrcDcoUDbTS_TL2IRdB-EYiFFrueUTMrNF9H4dRYO7An9_TUyA5f0cnaCqFlGTg), [2] (/goto?url=CAES1wEB6zswFdo6CfRCbNPO0I45de0p1kR-rCPJgOzb8zLo0P0IDF9aHxhGfwQGUsMgmhahuKYammJYM4wgcIcunYyynb2BepHYvwkr_ZtPGJMG_s61BR3de6gr84FtD3v2ueRVKJTBa-h9FZ8-MnAvaWVsJ7mJZAXCZkptuW8FcK-lNfRgABKjaYEU-5B70LjUkUsOG52Iw3hmiN878a--Klv63X5XSRQlDqXfZ9szWsamoRpQ058hSi_KVFIY3xFwy7ORA6hpp3-Ro-3uF7opIy6JIExAavscMA)

Example Usage in a Driver

To maintain compatibility across different kernel versions, drivers often wrap class_create() with a version check:
c
```
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
    my_class = class_create("my_device_class");
#else
    my_class = class_create(THIS_MODULE, "my_device_class");
#endif
```
Use code with caution.
Are you writing or porting a Linux device driver for a specific kernel version, or running into a compile error with class_create?


# Extra note 2

THIS_MODULE is a macro defined in the Linux kernel header file <linux/module.h>.
It resolves to a pointer to the current module's struct module instance. When you compile code as a loadable kernel module (LKM), the build system automatically assigns this pointer to track the module's lifetime, usage count, and dependencies.

How it Works Under the Hood

When you include <linux/module.h>, the macro is typically defined like this:
c
extern struct module __this_module;
#define THIS_MODULE (&__this_module)
Use code with caution.
1. __this_module: This is a global variable generated automatically for every module by the kernel building tool (modpost) during the compilation stage.
2. Built-in Drivers: If your driver is compiled directly into the kernel image (y instead of m in Kconfig), THIS_MODULE resolves to NULL because the code is statically built and cannot be unloaded.

Why it Was Removed from class_create

Historically, functions like class_create(THIS_MODULE, "name") required THIS_MODULE so that the kernel could increment the module's reference count. This prevented a user from unloading the module (via rmmod) while its sysfs device class was still in active use.
In Kernel 6.4, the kernel developers refactored the subsystem. The class infrastructure now implicitly handles the module ownership internally when the device is registered, making the manual passing of THIS_MODULE redundant.


