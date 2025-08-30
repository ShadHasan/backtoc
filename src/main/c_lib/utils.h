#ifndef ADVANIEN_UTILS
#define ADVANIEN_UTILS

#include <stdbool.h>
#include <string.h>
#include "model/common/stack.h"

void tstring(char* ts, char c) {
	int len = strlen(ts);
	if (len <= 0) {
		ts = (char*)realloc(ts, (len+1)*sizeof(char));
		ts[0] = c;
		ts[1] = '\0';
	} else {
		ts = (char*)realloc(ts, (len+2)*sizeof(char));
		ts[len] = c;
		ts[len+1] = '\0';
	}
	printf("%d, %s\n", len, ts);

}

void free_tstring(char* ts) {
	printf("faulting");
	int len = strlen(ts);
	int i;
	ts = (char*)realloc(ts, (1)*sizeof(char));
	ts[0] = '\0';
}

bool validate_json(char* json_str){
	bool invalid = false;
	int i;

	int len = strlen(json_str);

	char c, poped_c;
	bool isKey = true;
	short type;  // array 0, object 1, string 2
	int depth = 0;   // count level of depth

	char* ts = (char*)malloc(sizeof(char));
	ts[0] = '\0';

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
				if (c != '"') {   // if " is not otos. Not string literal but json syntax
					push_adv_char_stack(c_stack, '{');
					isKey = true;
					// TODO: Here initialize kv object
					depth++;
				}
				break;
			case '[':
				if (c != '"') {   // if " is not otos. Not string literal but json syntax
					push_adv_char_stack(c_stack, '[');
					// TODO: here initialize new kv array
					isKey = false;
					depth++;
				}
				break;
			case '"':
				if (c != '"') {   // if " is not otos. Not string literal but json syntax
					push_adv_char_stack(c_stack, '"');
				} else {
					poped_c = pop_adv_char_stack(c_stack);
					// here get the key in ts if isKey "true" else value
				}
				break;
			case '}':
				if (c != '"') {   // if " is not otos. Not string literal but json syntax
					if (c != '{') {
						invalid = true;
					} else {
						poped_c = pop_adv_char_stack(c_stack);
						// Todo: here link kv object to predecessor
						free_tstring(ts);
						depth--;
					}
				}
				break;
			case ']':
				if (c != '"') {   // if " is not otos. Not string literal but json syntax
					if (c != '[') {
						invalid = true;
					} else {
						poped_c = pop_adv_char_stack(c_stack);
						// Todo: here link kv array to predecessor
						free_tstring(ts);
						depth--;
					}
				}
				break;
			case ':':    // Time to separate key from its value
				if(!isKey) {
					invalid = true; // value do not have followed value, only key have value.
				} else {
					if (c != '"') {  // if " is not on top of stack. It is not string literal but json syntax and it is key but value.
						isKey = false;
						// Todo: here push string kv object keys
						free_tstring(ts);
					} else {
						if (c == '[') {   // if c is [(array) it does not expect semicolon
							invalid = true;
						}
					}
				}
				break;
			case ',':
				if (c != '"') {  // if " is not otos. Not string literal but json syntax and it is either next key-value or value of an array
					if (strlen(ts) > 0) {
						if (c == '{') {
							if (isKey){
								// Todo: store ts as temp_key for current kv object and pushed to kv object when value is determined.
							} else {
								// TODO: push ts as values with keys in temp_key as a key to current kv object
							}
							isKey = true;
						} else {
							if ( c == '[') {
								// Todo: push value to current kv array
							}
						}
						free_tstring(ts);
					} else {
						// TODO: invalid if current kv object or array does not have any value or key-value
						invalid = true;  // TODO: it is incomplete
					}
				}
				break;
			default:
				if (c == '"') {
					tstring(ts, json_str[i]);
				}
				break;
		}

		if (invalid) {
			printf("\n Error at char: '%c', index: %d, stack: %c, ts: %s\n", json_str[i], i, c, ts);
			break;
		}
	}
	if(c_stack->size > 0) {
		invalid = true;
		printf("\n Error at dangling syntax stack %d, char: %c", c_stack->size, seek_adv_char_stack(c_stack));
	}

	return (!invalid);
}

// on top of stack

#endif
