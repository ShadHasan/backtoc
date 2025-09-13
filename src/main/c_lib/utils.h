#ifndef ADVANIEN_UTILS
#define ADVANIEN_UTILS

#include <stdbool.h>
#include <string.h>
#include "model/common/keyval.h"
#include "model/common/stack.h"

typedef struct adv_json_depth adv_json_depth;
typedef struct kv_multi_type_stack kv_multi_type_stack;

struct adv_json_depth {
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

	int* type_track;     // array 0, object 1, key 2, value 3, single char 4
	int type_allocated;  // keep track of type_track allocated memory.
	int stack_size;      // keep track of current stack size

	int allocated_0;
	int type_0_size;
	int allocated_1;
	int type_1_size;
	int allocated_2;
	int type_2_size;
	int allocated_3;
	int type_3_size;
	int allocated_4;
	int type_4_size;

};

void push_to_kv_multi_stack(adv_json_depth* depth_tracer, adv_kv_obj* obj, adv_kv_array* arr, char* key, char* value) {
	kv_multi_type_stack* kmts = depth_tracer->kmts;
	if (kmts->type_allocated <= (kmts->stack_size+1)) {
		if (kmts->stack_size == 0) {
			kmts->type_track = (int*)malloc(sizeof(int));
			kmts->type_allocated = 1;
		} else {
			kmts->type_track = (int*)realloc(kmts->type_track, (kmts->stack_size+1)*sizeof(int));
			kmts->type_allocated = kmts->stack_size+1;
		}
	}
	if (obj != NULL) {
		kmts->type_track[kmts->stack_size] = 1;
		if (kmts->allocated_1 < (kmts->type_1_size + 1)) {
			if (kmts->type_1_size == 0) {
				kmts->obj = (adv_kv_obj**)malloc(sizeof(adv_kv_obj*));
			} else {
				kmts->obj = (adv_kv_obj**)realloc(kmts->obj, (kmts->type_1_size + 1)*sizeof(adv_kv_obj*));
			}
			kmts->allocated_1 = kmts->type_1_size + 1;
		}
		kmts->obj[kmts->type_1_size] = obj;
		kmts->type_1_size++;
	} else {
		if ( arr != NULL) {
			kmts->type_track[kmts->stack_size] = 0;
			if (kmts->allocated_0 < (kmts->type_0_size + 1)) {
				if (kmts->type_0_size == 0) {
					kmts->arr = (adv_kv_array**)malloc(sizeof(adv_kv_array*));
				} else {
					kmts->arr = (adv_kv_array**)realloc(kmts->arr, (kmts->type_0_size + 1)*sizeof(adv_kv_array*));
				}
				kmts->allocated_0 = kmts->type_0_size + 1;
			}
			kmts->arr[kmts->type_0_size] = arr;
			kmts->type_0_size++;
		} else {
			if (key != NULL) {
				kmts->type_track[kmts->stack_size] = 2;
				if (kmts->allocated_2 < (kmts->type_2_size + 1)) {
					if (kmts->type_2_size == 0) {
						kmts->temp_key = (char**)malloc(sizeof(char*));
					} else {
						kmts->temp_key = (char**)realloc(kmts->temp_key, (kmts->type_2_size + 1)*sizeof(char*));
					}
					kmts->allocated_2 = kmts->type_2_size + 1;
				}
				kmts->temp_key[kmts->type_2_size] = key;
				kmts->type_2_size++;
			} else {
				if (value != NULL) {
					kmts->type_track[kmts->stack_size] = 3;
					if (kmts->allocated_3 < (kmts->type_3_size + 1)) {
						if (kmts->type_3_size == 0) {
							kmts->temp_value = (char**)malloc(sizeof(char*));
						} else {
							kmts->temp_value = (char**)realloc(kmts->temp_value, (kmts->type_3_size + 1)*sizeof(char*));
						}
						kmts->allocated_3 = kmts->type_3_size + 1;
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

int pop_to_kv_multi_stack(adv_json_depth* depth_tracer) {
	kv_multi_type_stack* kmts = depth_tracer->kmts;
	int type = kmts->type_track[kmts->stack_size-1];
	switch(type) {
		case 0:
			depth_tracer->temp_arr = kmts->arr[kmts->type_0_size];
			kmts->type_0_size--;
			break;
		case 1:
			depth_tracer->temp_obj = kmts->obj[kmts->type_1_size];
			kmts->type_1_size--;
			break;
		case 2:
			depth_tracer->depth_temp_key = kmts->temp_key[kmts->type_2_size];
			kmts->type_2_size--;
			break;
		case 3:
			depth_tracer->depth_temp_value = kmts->temp_value[kmts->type_3_size];
			kmts->type_3_size--;
			break;
	}
	kmts->stack_size--;
	return type;
}

int seek_type_kv_multi_stack(adv_json_depth* depth_tracer) {
	kv_multi_type_stack* kmts = depth_tracer->kmts;
	int type = kmts->type_track[kmts->stack_size-1];
	switch(type) {
		case 0:
			depth_tracer->temp_arr = kmts->arr[kmts->type_0_size];
			break;
		case 1:
			depth_tracer->temp_obj = kmts->obj[kmts->type_1_size];
			break;
		case 2:
			depth_tracer->depth_temp_key = kmts->temp_key[kmts->type_2_size];
			break;
		case 3:
			depth_tracer->depth_temp_value = kmts->temp_value[kmts->type_3_size];
			break;
	}
	return type;
}


adv_json_depth* init_adv_json_depth() {
	adv_json_depth *depth = malloc(sizeof(adv_json_depth));
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
	depth->kmts->type_allocated = 0;
	depth->kmts->allocated_0 = 0;
	depth->kmts->allocated_1 = 0;
	depth->kmts->allocated_2 = 0;
	depth->kmts->allocated_3 = 0;
	depth->kmts->allocated_4 = 0;
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
	// int len2 = strlen(ts);
	// printf("pre: %d, post: %d", len, len2);
	// printf(", %s\n", ts);
}

void free_tstring(char* ts) {
	// printf("faulting");
	ts = (char*)realloc(ts, (1)*sizeof(char));
	ts[0] = '\0';
}

void allocate_depth_element(adv_json_depth* depth_trace) {
	if(depth_trace->current_depth >= depth_trace->allocated) {
		depth_trace->allocated = depth_trace->current_depth + 1;
		depth_trace->depth_element = (int*)realloc(depth_trace->depth_element, (depth_trace->allocated)*sizeof(int));
	}
}

void set_depth_element(adv_json_depth* depth_trace) {
	// printf("alloc: %d, d: %d", depth_trace->allocated, depth_trace->current_depth);
	allocate_depth_element(depth_trace);
	// printf("alloc: %d, d: %d", depth_trace->allocated, depth_trace->current_depth);
	depth_trace->depth_element[depth_trace->current_depth] = 1;
}

void reset_depth_element(adv_json_depth* depth_trace){
	allocate_depth_element(depth_trace);
	depth_trace->depth_element[depth_trace->current_depth] = 0;
}



bool validate_json(char* json_str){
	bool invalid = false;
	int i;

	int len = strlen(json_str);

	char c;
	bool isKey = true;

	// current level of depth which is root represent
	// as 0 in json tree which have only one element
	adv_json_depth *depth = init_adv_json_depth();

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
					pop_adv_char_stack(c_stack);
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
						pop_adv_char_stack(c_stack);
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
						pop_adv_char_stack(c_stack);
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
void parse_json(adv_kv_or_a* collective, char* json_str){
	int oa[2] = {0, 1};
	int oa_res;
	bool invalid = false;
	int i, type, type_key;

	int len = strlen(json_str);

	int c, popped_c; // array[] 0, object{} 1, key 2, quote" 3, value_array 5, value_object 6, value_string 7
	bool isKey = true;
	// current level of depth which is root represent
	// as 0 in json tree which have only one element
	adv_json_depth *depth = init_adv_json_depth();

	char* ts = (char*)malloc(sizeof(char));
	ts[0] = '\0';
	adv_kv_obj* to;
	adv_kv_array* ta;
	char* tk;
	char* tv;
	adv_kv_obj* sto;
	adv_kv_array* sta;


	adv_int_stack* i_stack = init_adv_int_stack();
	for(i=0;i<len;i++) {

		if (i_stack->size > 0)
			c = seek_adv_int_stack(i_stack);
		else
			c = -1;
		printf("(%d, %c) ", c, json_str[i]);
		switch(json_str[i]) {
			case '{':
				if (c != 3) {   // if " is not otos. Not string literal but json syntax
					push_adv_int_stack(i_stack, 1);
					isKey = true;
				}
				break;
			case '[':
				if (c != 3) {   // if " is not otos. Not string literal but json syntax
					push_adv_int_stack(i_stack, 0);
					// Initialize new kv array
					depth->temp_arr = adv_kv_init_arr();
					isKey = false;
				}
				break;
			case '"':
				if (c != 3) {   // if " is not otos. Not string literal but json syntax
					push_adv_int_stack(i_stack, 3);
				} else {
					popped_c = pop_adv_int_stack(i_stack);
					if (popped_c != 3) {
						invalid = true;
					} else {
						if (isKey) {
							push_to_kv_multi_stack(depth, NULL, NULL, ts, NULL);
							push_adv_int_stack(i_stack, 2);
						} else {
							push_to_kv_multi_stack(depth, NULL, NULL, NULL, ts);
							push_adv_int_stack(i_stack, 7);
						}
						oa_res = seek_adv_int_stack_first_arrival(i_stack, oa, 2);
						switch(oa_res) {
							case 0:
								isKey = false;
								break;
							case 1:
								isKey = true;
								break;
							default:
								invalid = true;
								break;
						}
					}
					free_tstring(ts);
				}
				break;
			case '}':
				if (c != 3) {
					sto = adv_kv_init_obj();
					popped_c = pop_adv_int_stack(i_stack);
					while (popped_c != 1) {
						printf("po %d", popped_c);
						switch(popped_c) {
							case 5:
								type = pop_to_kv_multi_stack(depth);
								ta = depth->temp_arr;
								popped_c = pop_adv_int_stack(i_stack);
								type_key = pop_to_kv_multi_stack(depth);
								if (popped_c == 2 && type == 0 && type_key == 2) {
									tk = depth->depth_temp_key;
									adv_kv_add_obj_arr(sto, tk, ta);
								} else {
									invalid = true;
								}
								break;
							case 6:
								type = pop_to_kv_multi_stack(depth);
								to = depth->temp_obj;
								popped_c = pop_adv_int_stack(i_stack);
								type_key = pop_to_kv_multi_stack(depth);
								if (popped_c == 2 && type == 1 && type_key == 2) {
									tk = depth->depth_temp_key;
									adv_kv_add_obj_obj(sto, tk, to);
								} else {
									invalid = true;
								}
								break;
							case 7:
								type = pop_to_kv_multi_stack(depth);
								tv = depth->depth_temp_value;
								popped_c = pop_adv_int_stack(i_stack);
								type_key = pop_to_kv_multi_stack(depth);
								if (popped_c == 2 && type == 3 && type_key == 2) {
									tk = depth->depth_temp_key;
									adv_kv_add_obj_str(sto, tk, tv);
								} else {
									invalid = true;
								}
								break;
							default:
								invalid = true;
								break;
						}
						if (invalid)
							break;
						popped_c = pop_adv_int_stack(i_stack);
					}
					if (!invalid) {
						push_adv_int_stack(i_stack, 6);
						push_to_kv_multi_stack(depth, sto, NULL, NULL, NULL);
						oa_res = seek_adv_int_stack_first_arrival(i_stack, oa, 2);
						switch(oa_res) {
							case 0:
								isKey = false;
								break;
							case 1:
								isKey = true;
								break;
							default:
								invalid = true;
								break;
						}
					}
				}
				break;
			case ']':
				if (c != 3) {
					sta = adv_kv_init_arr();
					popped_c = pop_adv_int_stack(i_stack);
					while(popped_c != 0) {
						switch(popped_c) {
							case 5:
								type = pop_to_kv_multi_stack(depth);
								ta = depth->temp_arr;
								if (type == 0)
									adv_kv_add_arr_arr(sta, ta);
								else
									invalid = true;
								break;
							case 6:
								type = pop_to_kv_multi_stack(depth);
								to = depth->temp_obj;
								if (type == 1)
									adv_kv_add_arr_obj(sta, to);
								else
									invalid = true;
								break;
							case 7:
								type = pop_to_kv_multi_stack(depth);
								tv = depth->depth_temp_value;
								if (type == 3)
									adv_kv_add_arr_str(sta, tv);
								else
									invalid = true;
								break;
						}
						if (invalid)
							break;
						popped_c = pop_adv_int_stack(i_stack);
					}
					if (!invalid) {
						push_adv_int_stack(i_stack, 5);
						push_to_kv_multi_stack(depth, NULL, sta, NULL, NULL);
						oa_res = seek_adv_int_stack_first_arrival(i_stack, oa, 2);
						switch(oa_res) {
							case 0:
								isKey = false;
								break;
							case 1:
								isKey = true;
								break;
							default:
								invalid = true;
								break;
						}
					}
				}
				break;
			case ':':    // Time to separate key from its value
				if (c != 3) {
					oa_res = seek_adv_int_stack_first_arrival(i_stack, oa, 2);
					if (oa_res == 1) { // semicolon is expected in object and in a string
						if(!isKey) {
							invalid = true; // value do not have followed value, only key have value.
						} else {
							isKey = false;
						}
					} else {
						invalid = true;  // semicolon is expected in object and in a string
					}
				}
				break;
			case ',':
				if (c != 3) {
					oa_res = seek_adv_int_stack_first_arrival(i_stack, oa, 2);
					switch(oa_res) {
						case 0:
							isKey = false;
							break;
						case 1:
							isKey = true;
							break;
						default:
							invalid = true;
							break;
					}
				}
				break;
			default:
				if (c == 3) {
					tstring(ts, json_str[i]);
				}
				break;
		}

		if (invalid) {
			printf("\n Error at char: '%c', index: %d, stack: %d, ts: %s\n", json_str[i], i, c, ts);
			break;
		}
	}
	if(i_stack->size != 1) {
		invalid = true;
		printf("\n Error at dangling syntax stack %d, char: %c", i_stack->size, seek_adv_int_stack(i_stack));
	} else {
		type = pop_to_kv_multi_stack(depth);
		printf("%d", type);
		switch(type) {
			case 0:
				collective->type = 0;
				collective->arr = depth->temp_arr;
				break;
			case 1:
				collective->type = 1;
				collective->obj = depth->temp_obj;
				break;
			default:
				collective->type = -1;
				invalid = true;
				break;
		}
	}

}

#endif
