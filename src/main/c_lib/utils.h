#ifndef ADVANIEN_UTILS
#define ADVANIEN_UTILS

#include <stdbool.h>
#include <string.h>
#include "model/common/stack.h"

void tstring(char* ts, char c) {

	if (ts == NULL) {
		ts = (char*)malloc(sizeof(char));
		ts[0] = c;
	} else {
		int len = strlen(ts);
		ts = (char*)realloc(ts, (len+1)*sizeof(char));
		ts[len] = c;
	}

}

bool validate_json(char* json_str){
	bool invalid = false;
	int i;

	int len = strlen(json_str);

	char c, poped_c;
	bool isKey = true;
	short type;  // array 0, object 1, string 2

	char* ts = NULL;

	adv_char_stack* c_stack = malloc(sizeof(adv_char_stack));
	c_stack->c = NULL;
	c_stack->size = 0;
	printf("%d", c_stack->size);
	for(i=0;i<len;i++) {

		if (c_stack->size > 0)
			c = seek_adv_char_stack(c_stack);
		else
			c = '*';

		switch(json_str[i]) {
			case '{':
				if (c != '"') {
					push_adv_char_stack(c_stack, '{');
				}
				break;
			case '[':
				if (c != '"') {
					push_adv_char_stack(c_stack, '[');
				}
				break;
			case '"':
				if (c != '"') {
					push_adv_char_stack(c_stack, '"');
				} else {
					poped_c = pop_adv_char_stack(c_stack);
					// here get the key in ts if isKey "true" else value
				}
				break;
			case '}':
				if (c != '{') {
					invalid = true;
				} else {
					poped_c = pop_adv_char_stack(c_stack);
				}
				break;
			case ']':
				if (c != '[') {
					invalid = true;
				} else {
					poped_c = pop_adv_char_stack(c_stack);
				}
				break;
			case ':':    // Time to separate key from its value
				if(!isKey) {
					invalid = true; // value do not have followed value, only key have value.
				} else {
					if (c != '"') {  // if " is not on top of stack. It is not string literal but json syntax and it is key but value.
						isKey = false;
					} else {
						if (c == '[') {   // if c is [(array) it does not expect semicolon
							invalid = true;
						}
					}
				}
				break;
			case ',':
				if (c != '"') {  // if " is not otos. It is not string literal but json syntax and it is either next key-value or value of an array
					if (c == '{')
						isKey = true;
				}
				break;
			default:
				if (c == '"') {
					tstring(ts, json_str[i]);
				}
				break;
		}

		if (invalid) {
			printf("\n Error at char: %c, index: %d\n", json_str[i], i);
			break;
		}
	}
	if(c_stack->size > 0) {
		invalid = true;
	}

	return (!invalid);
}

// on top of stack

#endif
