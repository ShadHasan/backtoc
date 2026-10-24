/* Not working
 * For some reason it is killing entire kernel when I try to run
 * sudo rmmod first_interrupt
 *
 * May something I am missing while I was writing.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>

#define IRQ_NUMBER 1

void * my_id;

static irqreturn_t adv_handler(int irq, void* dev_id) {
	int a = 10;
	int b = 20;
	printk(KERN_INFO "Interrupt %d triggered \n", irq);

	// Below is not c90
	// int a = 10;
	// int b = 20; 
	printk("value of sum = %d\n", a+b);
	// Return IRQ_HANDLED to ackowledge the interrupt
	return IRQ_HANDLED;

}

static int my_init(void) {
	int result;
	// Register the interrupt handler
	result = request_irq(IRQ_NUMBER, adv_handler, IRQF_SHARED, "my_interrupt", &(my_id));
	if (result) {
		printk(KERN_ERR "Failed to register interrupt handler\n");
		return result;
	}
	printk(KERN_INFO "Interrupt handler registered\n");
	return 0;
}

static void my_exit(void) {
	free_irq(IRQ_NUMBER, (void*) (my_id));
	printk(KERN_INFO "Interrupt handler unregistered \n");
}

module_init (my_init);
module_exit (my_exit);

MODULE_AUTHOR("TEAM");
MODULE_DESCRIPTION("Test interrupt module");
MODULE_LICENSE("GPL"); 

