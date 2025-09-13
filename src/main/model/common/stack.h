#ifndef ADVANIEN_COMMON_STACK
#define ADVANIEN_COMMON_STACK
#include<stdlib.h>


typedef struct adv_char_stack adv_char_stack;
typedef struct adv_int_stack adv_int_stack;

struct adv_char_stack {
	char* c;
	int size;
};

struct adv_int_stack {
	int* i;
	int size;
};

adv_char_stack* init_adv_char_stack() {
	adv_char_stack* stack = malloc(sizeof(adv_char_stack));
	stack->c = NULL;
	stack->size = 0;
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

adv_int_stack* init_adv_int_stack() {
	adv_int_stack* stack = malloc(sizeof(adv_int_stack));
	stack->i = NULL;
	stack->size = 0;
	return stack;
}

void push_adv_int_stack(adv_int_stack* stack, int i) {
	if (stack->i == NULL) {
		stack->i = (int*)malloc(sizeof(int));
		stack->size = 0;
	} else {
		stack->i = (int*)realloc(stack->i, (stack->size+1)*sizeof(int));
	}
	stack->i[stack->size++] = i;
}

int seek_adv_int_stack(adv_int_stack* stack) {
	return stack->i[stack->size-1];
}

int pop_adv_int_stack(adv_int_stack* stack) {
	int i = stack->i[(stack->size-1)];
	stack->i = (int*)realloc(stack->i, (stack->size-1)*sizeof(int));
	stack->size--;
	return i;
}

char seek_adv_int_stack_first_arrival(adv_int_stack* stack, int* arr, int size_arr) {
	int i, j;
	for(i = stack->size-1; i >= 0; i--) {
		for(j=0; j<size_arr; j++) {
			if(arr[j] == stack->i[i]) {
				return arr[j];
			}
		}
	}
	return -1;
}

#endif
