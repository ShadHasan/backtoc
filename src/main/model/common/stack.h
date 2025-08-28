#ifndef ADVANIEN_COMMON_STACK
#define ADVANIEN_COMMON_STACK
#include<stdlib.h>


typedef struct adv_char_stack adv_char_stack;

struct adv_char_stack {
	char c;
	adv_char_stack* next;
	adv_char_stack* prev;
};

adv_char_stack* init_adv_char_stack(char c) {
	adv_char_stack* stack = (adv_char_stack*)malloc(sizeof(adv_char_stack));
	stack->c = c;
	stack->next = NULL;
	stack->prev = NULL;
	return stack;
}

void push_adv_char_stack(adv_char_stack* stack, char c) {
	adv_char_stack* nstack = (adv_char_stack*)malloc(sizeof(adv_char_stack));
	nstack->c = stack->c;
	stack->c = c;
	nstack->next = NULL;
	stack->next = nstack;
}

char seek_adv_char_stack(adv_char_stack* stack) {
	return stack->c;
}

char pop_adv_char_stack(adv_char_stack* stack) {
	adv_char_stack* rstack = stack->next;
	char c = stack->c;
	free(stack);
	stack = rstack;
	return c;
}

#endif
