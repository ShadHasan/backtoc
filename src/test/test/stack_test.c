#include "model/common/stack.h"

void stack_char_test() {
	char c;
	adv_char_stack* c_stack = init_adv_char_stack();
	push_adv_char_stack(c_stack, 'f');
	push_adv_char_stack(c_stack, 'i');
	push_adv_char_stack(c_stack, 'r');
	c = seek_adv_char_stack(c_stack);
	printf("\n seek stack: %c \n",c);
	c = pop_adv_char_stack(c_stack);
	printf("\n pop stack: %c \n",c);
	c = seek_adv_char_stack(c_stack);
	printf("\n %c \n",c);
	push_adv_char_stack(c_stack, 'r');
	push_adv_char_stack(c_stack, 's');
	push_adv_char_stack(c_stack, 't');

	while(c_stack->size > 0) {
		c = pop_adv_char_stack(c_stack);
		printf("\n pop stack: %c \n",c);
	}
}
