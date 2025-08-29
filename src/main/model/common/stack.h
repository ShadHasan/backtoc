#ifndef ADVANIEN_COMMON_STACK
#define ADVANIEN_COMMON_STACK
#include<stdlib.h>


typedef struct adv_char_stack adv_char_stack;

struct adv_char_stack {
	char* c;
	int size;
};

adv_char_stack* init_adv_char_stack(char c) {
	adv_char_stack* stack;
	stack->size = 0;
	stack->c = (char*)malloc(sizeof(char));
	stack->c[0] = c;
	stack->size++;
	return stack;
}

void push_adv_char_stack(adv_char_stack* stack, char c) {
	if (stack->c == NULL) {
		stack->c = (char*)malloc(sizeof(char));
		stack->size = 0;
	} else {
		stack->c = (char*)realloc(stack->c, (stack->size+1)*sizeof(char));
	}
	stack->c[stack->size++] = c;
}

char seek_adv_char_stack(adv_char_stack* stack) {
	return stack->c[stack->size-1];
}

char pop_adv_char_stack(adv_char_stack* stack) {
	char c = stack->c[(stack->size-1)];
	stack->c = (char*)realloc(stack->c, (stack->size-1)*sizeof(char));
	stack->size--;
	return c;
}

#endif
