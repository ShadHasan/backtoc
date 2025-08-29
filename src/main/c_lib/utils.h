#ifndef ADVANIEN_UTILS
#define ADVANIEN_UTILS

#include <stdbool.h>
#include <string.h>
#include "model/common/stack.h"

void tstring(char* ts, char c) {
	int len = strlen(ts);
	if (ts == NULL) {
		ts = (char*)malloc(sizeof(char));
		ts[0] = c;
	} else {
		ts = (char*)realloc(ts, (len+1)*sizeof(char));
		ts[len] = c;
	}

}

bool validate_json(char* json_str){
	int len = strlen(json_str);
	char c, poped_c;
	bool isKey = true;
	char* ts = NULL;
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
				} else {
					poped_c = pop_adv_char_stack(c_stack);
				}
				break;
			case ']':
				if (c != ']') {
					invalid = true;
				} else {
					poped_c = pop_adv_char_stack(c_stack);
				}
				break;
			case ':':    // Time to separate key and its value
				if (c != '"') {
					isKey = false;
				}
				break;
			case ',':
				if (c != '"') {
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
			break;
		}
	}
}

#endif
