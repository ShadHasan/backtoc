#ifndef ADVANIEN_COMMON_KEYVAL
#define ADVANIEN_COMMON_KEYVAL

#include <stdlib.h>
#include <stdbool.h>
#include "model/common/keyset.h"
#include <string.h>

// Dictionary entire data structure with hierarchical. "kv" stands for key-value. Hence it is

// like json datastructure
typedef struct adv_kv_obj adv_kv_obj;
typedef struct adv_kv_array adv_kv_array;


// array each instance blueprint
// please note array can have nested array
struct adv_kv_array{
	adv_kv_obj** obj;
	adv_kv_array** value_list;
	char** value;
	int count_object;
	int count_array;
	int count_string;
};


struct adv_kv_obj {
	// key list blueprint. It helps to keep track of used key.
	// Hence used to prevent duplicate key for data structure
	adv_lks_keys* keyset;  // keyset manages type  array 0, object 1, string 2

	adv_kv_obj** children;     // when type is object
	adv_kv_array** value_list; // when type is array, then again each element of array can be array, object, string
	char** value; // when type is string
	int count_object;
	int count_array;
	int count_string;
};


// Initialize key value as a root element
// root keyval is alway of type object. It value may be array, object, string etc
// but root itself is a object
adv_kv_obj* adv_kv_init_obj() {
	// Root object
	adv_kv_obj* obj = (adv_kv_obj*)malloc(sizeof(adv_kv_obj));

	// initializing root key with given type
	obj->keyset = adv_init_lks();

	obj->children = NULL;
	obj->value_list = NULL;
	obj->value = NULL;
	obj->count_object = 0;
	obj->count_array = 0;
	obj->count_string = 0;

	return obj;
}

adv_kv_array* adv_kv_init_arr() {
	adv_kv_array* karr = (adv_kv_array*)malloc(sizeof(adv_kv_array));

	karr->obj = NULL;
	karr->value_list = NULL;
	karr->value = NULL;
	karr->count_object = 0;
	karr->count_array = 0;
	karr->count_string = 0;
}

int adv_kv_fetch_obj_index_type_for_null(adv_kv_obj* kv, int type) {
	int index = -1;
	int i;
	switch (type) {
		case 0:
			for(i = 0; i < kv->count_array; i++) {
				if(kv->value_list[i] == NULL) {
					index = i;
					break;
				}
			}
			break;
		case 1:
			for(i = 0; i < kv->count_object; i++) {
				if(kv->children[i] == NULL) {
					index = i;
					break;
				}
			}
			break;
		case 2:
			for(i = 0; i < kv->count_string; i++) {
				if(kv->value[i] == NULL) {
					index = i;
					break;
				}
			}
			break;
	}
	return index;
}

int adv_kv_fetch_arr_index_type_for_null(adv_kv_array* karr, int type) {
	int index = -1;
	int i;
	switch (type) {
		case 0:
			for(i = 0; i < karr->count_array; i++) {
				if(karr->value_list[i] == NULL) {
					index = i;
					break;
				}
			}
			break;
		case 1:
			for(i = 0; i < karr->count_object; i++) {
				if(karr->obj[i] == NULL) {
					index = i;
					break;
				}
			}
			break;
		case 2:
			for(i = 0; i < karr->count_string; i++) {
				if(karr->value[i] == NULL) {
					index = i;
					break;
				}
			}
			break;
	}
	return index;
}

void adv_kv_set_arr_index_type_null(adv_kv_array* karr, int type, int type_index) {
	switch (type) {
		case 0:
			karr->obj[type_index] = NULL;
			break;
		case 1:
			karr->value_list[type_index] = NULL;
			break;
		case 2:
			karr->value[type_index] = NULL;
			break;
	}
}

void adv_kv_set_obj_index_type_null(adv_kv_obj* kv, int type, int type_index) {
	switch (type) {
		case 0:
			kv->children[type_index] = NULL;
			break;
		case 1:
			kv->value_list[type_index] = NULL;
			break;
		case 2:
			kv->value[type_index] = NULL;
			break;
	}
}

/// This is all when kv object adding other kv object
void adv_kv_add_obj_obj(adv_kv_obj* kv, char* key, adv_kv_obj* obj) {
	adv_lks_index_data key_index_data = adv_index_key_lks(kv->keyset, key);
	bool new_allocate = false;
	int type = 1;

	// deleting(Assign NULL) to children,value_list, value to it index if already existing anything against the key
	if(key_index_data.index != -1) {
		int del_type = key_index_data.type;
		int del_type_index = key_index_data.type_index;
		adv_kv_set_obj_index_type_null(kv, del_type, del_type_index);
	}

	// First check children of type object have null value. Take that is as type index else use count_object as type_index.
	int type_index = adv_kv_fetch_obj_index_type_for_null(kv, type);

	if (type_index == -1) {
		new_allocate = true;
		type_index = kv->count_object++;
	}
	adv_add_key_lks(kv->keyset, key, type, type_index);
	if (new_allocate) {
	// adding new object against the key;
		if (type_index > 1) {
			kv->children = (adv_kv_obj**)realloc(kv->children , (type_index)*(sizeof(adv_kv_obj*)));
		} else {
			kv->children = (adv_kv_obj**)malloc(sizeof(adv_kv_obj*));
		}
	}
	kv->children[type_index] = obj;

}

void adv_kv_add_obj_str(adv_kv_obj* kv, char* key, char* value) {
	adv_lks_index_data key_index_data = adv_index_key_lks(kv->keyset, key);
	bool new_allocate = false;
	int type = 2;

	// deleting(Assign NULL) to children,value_list, value to it index if already existing anything against the key
	if(key_index_data.index != -1) {
		int del_type = key_index_data.type;
		int del_type_index = key_index_data.type_index;
		adv_kv_set_obj_index_type_null(kv, del_type, del_type_index);
	}

	// First check children of type object have null value. Take that is as type index else use count_object as type_index.
	int type_index = adv_kv_fetch_obj_index_type_for_null(kv, type);

	if (type_index == -1) {
		new_allocate = true;
		type_index = kv->count_string++;
	}
	adv_add_key_lks(kv->keyset, key, type, type_index);
	if (new_allocate) {
	// adding new object against the key;
		if (type_index > 1) {
			kv->value = (char**)realloc(kv->value , (type_index)*(sizeof(char*)));
		} else {
			kv->value = (char**)malloc(sizeof(char*));
		}
	}
	kv->value[type_index] = value;
}

void adv_kv_add_obj_arr(adv_kv_obj* kv, char* key, adv_kv_array* arr) {
	adv_lks_index_data key_index_data = adv_index_key_lks(kv->keyset, key);
	bool new_allocate = false;
	int type = 0;

	// deleting(Assign NULL) to children,value_list, value to it index if already existing anything against the key
	if(key_index_data.index != -1) {
		int del_type = key_index_data.type;
		int del_type_index = key_index_data.type_index;
		adv_kv_set_obj_index_type_null(kv, del_type, del_type_index);
	}

	// First check children of type array have null value. Take that is as type index else use count_array as type_index.
	int type_index = adv_kv_fetch_obj_index_type_for_null(kv, type);

	if (type_index == -1) {
		new_allocate = true;
		type_index = kv->count_array++;
	}
	adv_add_key_lks(kv->keyset, key, type, type_index);
	if (new_allocate) {
	// adding new object against the key;
		if (type_index > 1) {
			kv->value_list = (adv_kv_array**)realloc(kv->value , (type_index)*(sizeof(adv_kv_array*)));
		} else {
			kv->value_list = (adv_kv_array**)malloc(sizeof(adv_kv_array*));
		}
	}
	kv->value_list[type_index] = arr;
}


/// This is all when adding element to "kv" array type
void adv_kv_add_arr_arr(adv_kv_array* arr, adv_kv_array* narr) {

}

// this is nested array
void adv_kv_add_arr_str(adv_kv_array* arr, char* str) {

}

void adv_kv_add_arr_obj(adv_kv_array* arr, adv_kv_obj* obj) {

}

void adv_kv_traverse_obj(adv_kv_obj* kv) {

}

void adv_kv_traverse_arr(adv_kv_obj* kv) {

}

#endif
