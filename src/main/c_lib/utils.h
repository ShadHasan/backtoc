#ifndef ADVANIEN_UTILS
#define ADVANIEN_UTILS

#include <stdbool.h>
#include <string.h>
#include "model/common/stack.h"

typedef struct adv_depth adv_depth;
typedef struct kv_multi_type_stack kv_multi_type_stack;

struct adv_depth {
	int current_depth;
	int current_depth_type; // array 0 object 1 and string 2
	int* depth_element;    // These help to track the element for each level that it is first element or not.
	int allocated;

	kv_multi_type_stack* kmts;
	// for each depth either there is object, array and value and temporarily stored
	adv_kv_obj* temp_obj;
	adv_kv_array* temp_arr;
	char* depth_temp_key;
	// int* depth_type;  // not needed because otos character can tell type
	char* depth_temp_value;
};

struct kv_multi_type_stack {
	adv_kv_obj** obj;
	adv_kv_array** arr;
	char** temp_key;
	char** temp_value;
	char* single_char;

	int* type_track;  // array 0, object 1, key 2, value 3, single char 4
	int type_0_size;
	int type_1_size;
	int type_2_size;
	int type_3_size;
	int type_4_size;
	int stack_size;
};

void push_to_kv_multi_stack(adv_depth* depth_tracer, adv_kv_obj* obj, adv_kv_array* arr, char* key, char* value) {
	kv_multi_type_stack* kmts = depth_tracer->kmts;
	if (kmts->stack_size == 0) {
		kmts->type_track = (int*)malloc(sizeof(int));
	} else {
		kmts->type_track = (int*)realloc(kmts->type_track, (kmts->stack_size+1)*sizeof(int));
	}
	if (obj != NULL) {
		kmts->type_track[kmts->stack_size] = 1;
		if (kmts->type_1_size == 0) {
			kmts->obj = (adv_kv_obj**)malloc(sizeof(adv_kv_obj*));
		} else {
			kmts->obj = (adv_kv_obj**)realloc(kmts->obj, (kmts->type_1_size + 1)*sizeof(adv_kv_obj*));
		}
		kmts->obj[kmts->type_1_size] = obj;
		kmts->type_1_size++;
	} else {
		if ( arr != NULL) {
			kmts->type_track[kmts->stack_size] = 0;
			if (kmts->type_0_size == 0) {
				kmts->arr = (adv_kv_array**)malloc(sizeof(adv_kv_array*));
			} else {
				kmts->arr = (adv_kv_array**)realloc(kmts->arr, (kmts->type_0_size + 1)*sizeof(adv_kv_array*));
			}
			kmts->arr[kmts->type_0_size] = arr;
			kmts->type_0_size++;
		} else {
			if (key != NULL) {
				kmts->type_track[kmts->stack_size] = 2;
				if (kmts->type_2_size == 0) {
					kmts->temp_key = (char**)malloc(sizeof(char*));
				} else {
					kmts->temp_key = (char**)realloc(kmts->temp_key, (kmts->type_2_size + 1)*sizeof(char*));
				}
				kmts->temp_key[kmts->type_2_size] = key;
				kmts->type_2_size++;
			} else {
				if (value != NULL) {
					kmts->type_track[kmts->stack_size] = 3;
					if (kmts->type_3_size == 0) {
						kmts->temp_value = (char**)malloc(sizeof(char*));
					} else {
						kmts->temp_value = (char**)realloc(kmts->temp_value, (kmts->type_3_size + 1)*sizeof(char*));
					}
					kmts->temp_value[kmts->type_3_size] = value;
					kmts->type_3_size++;
				} else {
					// No action here
				}
			}
		}
	}
	kmts->stack_size++;
}

void pop_to_kv_multi_stack(adv_depth* depth_tracer, adv_kv_obj* obj, adv_kv_array* arr, char* key, char* value) {
	if (obj != NULL) {

	} else {
		if ( arr != NULL) {

		} else {
			if (key != NULL) {

			} else {
				if (value != NULL) {

				} else {

				}
			}
		}
	}
}


adv_depth* init_adv_depth() {
	adv_depth *depth = malloc(sizeof(depth));
	depth->current_depth = 0;
	depth->allocated = 1;
	depth->depth_element = (int*)malloc(sizeof(int));
	depth->depth_element[0] = 1;
	depth->kmts = (kv_multi_type_stack*)malloc(sizeof(kv_multi_type_stack));
	depth->kmts->stack_size = 0;
	depth->kmts->type_0_size = 0;
	depth->kmts->type_1_size = 0;
	depth->kmts->type_2_size = 0;
	depth->kmts->type_3_size = 0;
	depth->kmts->type_4_size = 0;
	return depth;
}

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
	// printf("%d, %s\n", len, ts);

}

void free_tstring(char* ts) {
	// printf("faulting");
	int len = strlen(ts);
	int i;
	ts = (char*)realloc(ts, (1)*sizeof(char));
	ts[0] = '\0';
}

void set_depth_element(adv_depth* depth_trace) {
	if(depth_trace->current_depth > depth_trace->allocated) {
		depth_trace->depth_element = (int*)realloc(depth_trace->depth_element, (++depth_trace->allocated)*sizeof(int));

	}
	depth_trace->depth_element[depth_trace->current_depth] = 1;
}

void reset_depth_element(adv_depth* depth_trace){
	depth_trace->depth_element[depth_trace->current_depth] = 0;
}



bool validate_json(char* json_str){
	bool invalid = false;
	int i;

	int len = strlen(json_str);

	char c, poped_c;
	bool isKey = true;
	short type;  // array 0, object 1, string 2

	// current level of depth which is root represent
	// as 0 in json tree which have only one element
	adv_depth *depth = init_adv_depth();

	char* ts = (char*)malloc(sizeof(char));
	ts[0] = '\0';

	adv_char_stack* c_stack = init_adv_char_stack();
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
					depth->current_depth++;
				}
				break;
			case '[':
				if (c != '"') {   // if " is not otos. Not string literal but json syntax
					push_adv_char_stack(c_stack, '[');
					// TODO: here initialize new kv array
					isKey = false;
					depth->current_depth++;
				}
				break;
			case '"':
				if (c != '"') {   // if " is not otos. Not string literal but json syntax
					push_adv_char_stack(c_stack, '"');
				} else {
					poped_c = pop_adv_char_stack(c_stack);
					// here get the key in ts if isKey "true" else value
					switch(c) {
						case '{':
							// key or value
							break;
						case '[':
							// value
							break;
					}
					set_depth_element(depth);
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
						reset_depth_element(depth);
						depth->current_depth--;
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
						reset_depth_element(depth);
						depth->current_depth--;
					}
				}
				break;
			case ':':    // Time to separate key from its value
				if(!isKey) {
					invalid = true; // value do not have followed value, only key have value.
				} else {
					if (c != '"') {  // if " is not on top of stack. It is not string literal but json syntax and it is key but value.
						isKey = false;
						// TODO: here push string kv object keys
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
					// TODO: invalid if current kv object or array does not have any value or key-value
					if (depth->depth_element[depth->current_depth] == 0) {
						invalid = true;
					} else {
						reset_depth_element(depth);
						switch(c) {
						case '{':
							if (isKey){
								// TODO: store ts as temp_key for current kv object and pushed to kv object when value is determined.
							} else {
								// TODO: push ts as values with keys in temp_key as a key to current kv object
							}
							isKey = true;
							break;
						case '[':
							// TODO: push value to current kv array
							isKey = false;
							break;
						}
						free_tstring(ts);
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


// otop: on top of stack
adv_kv_or_a* parse_json(char* json_str){
	adv_kv_or_a* collective = (adv_kv_or_a*)malloc(sizeof(adv_kv_or_a));
	bool invalid = false;
	int i;

	int len = strlen(json_str);

	char c, poped_c;
	bool isKey = true;
	short type;  // array 0, object 1, string 2

	// current level of depth which is root represent
	// as 0 in json tree which have only one element
	adv_depth *depth = malloc(sizeof(depth));
	depth->current_depth = 0;
	depth->allocated = 1;
	depth->depth_element = (int*)malloc(sizeof(int));
	depth->depth_element[0] = 1;

	char* ts = (char*)malloc(sizeof(char));
	ts[0] = '\0';

	adv_char_stack* c_stack = init_adv_char_stack();
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
					depth->current_depth++;
				}
				break;
			case '[':
				if (c != '"') {   // if " is not otos. Not string literal but json syntax
					push_adv_char_stack(c_stack, '[');
					// TODO: here initialize new kv array
					isKey = false;
					depth->current_depth++;
				}
				break;
			case '"':
				if (c != '"') {   // if " is not otos. Not string literal but json syntax
					push_adv_char_stack(c_stack, '"');
				} else {
					poped_c = pop_adv_char_stack(c_stack);
					// here get the key in ts if isKey "true" else value
					switch(c) {
						case '{':
							// key or value
							break;
						case '[':
							// value
							break;
					}
					set_depth_element(depth);
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
						reset_depth_element(depth);
						depth->current_depth--;
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
						reset_depth_element(depth);
						depth->current_depth--;
					}
				}
				break;
			case ':':    // Time to separate key from its value
				if(!isKey) {
					invalid = true; // value do not have followed value, only key have value.
				} else {
					if (c != '"') {  // if " is not on top of stack. It is not string literal but json syntax and it is key but value.
						isKey = false;
						// TODO: here push string kv object keys
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
					// TODO: invalid if current kv object or array does not have any value or key-value
					if (depth->depth_element[depth->current_depth] == 0) {
						invalid = true;
					} else {
						reset_depth_element(depth);
						switch(c) {
						case '{':
							if (isKey){
								// TODO: store ts as temp_key for current kv object and pushed to kv object when value is determined.
							} else {
								// TODO: push ts as values with keys in temp_key as a key to current kv object
							}
							isKey = true;
							break;
						case '[':
							// TODO: push value to current kv array
							isKey = false;
							break;
						}
						free_tstring(ts);
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

	return collective;
}

#endif
