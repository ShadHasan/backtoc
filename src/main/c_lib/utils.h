#ifndef ADVANIEN_UTILS
#define ADVANIEN_UTILS

#include <stdbool.h>
#include <string.h>
#include "model/common/stack.h"

bool validate_json(char* json_str){
	int len = strlen(json_str);
	char c, poped_c;
	adv_char_stack* c_stack = init_adv_char_stack('');
	int i;
	bool invalid = false;
	for(i=0;i<len;i++) {
		c = seek_adv_char_stack(c_stack);
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
				}
				break;
			case '}':
				if (c != '{') {
					invalid = true;
				}
				break;
			case ']':
				if (c != ']') {
					invalid = true;
				}
				break;
			case ':':
				break;
			case ',':
				break;
			default:
				break;
		}
		if (invalid) {
			break;
		}
	}
}

#endif
