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
	short type; // array 0, object 1, string 2
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
	adv_lks_keys* keyset;

	short type; // array 0, object 1, string 2

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
adv_kv_obj* adv_init_kv(int type) {
	// type can be array 0, object 1 even though string is 2,
	// we cannot initialized with string hence other than 0, 1 will return NULL
	if (type <0 && type > 1) {
		return NULL;
	}

	// Root object
	adv_kv_obj* obj = (adv_kv_obj*)malloc(sizeof(adv_kv_obj));
	obj->type = type;

	// initializing root key with given type
	obj->keyset = adv_init_lks();
	adv_add_key_lks(obj->keyset, "(0)", type);

	obj->children = NULL;
	obj->value_list = NULL;
	obj->value = NULL;

	return obj;
}

int adv_kv_fetch_obj_index_type_for_null(adv_kv_obj* kv, int type) {
	int index = -1;
	int i;
	switch (type) {
		case 0:
			for(i = 0; i < kv->keyset->count_array; i++) {
				if(kv->value_list[i] == NULL) {
					index = i;
					break;
				}
			}
			break;
		case 1:
			for(i = 0; i < kv->keyset->count_object; i++) {
				if(kv->children[i] == NULL) {
					index = i;
					break;
				}
			}
			break;
		case 2:
			for(i = 0; i < kv->keyset->count_string; i++) {
				if(kv->value[i] == NULL) {
					index = i;
					break;
				}
			}
			break;
	}
	return index;
}

int adv_kv_fetch_arr_index_type_for_null(adv_kv_array* karr) {
	int index = -1;
	int i;
	switch (karr->type) {
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

/// This is all when kv object adding other kv object
void adv_kv_add_obj_to_obj(adv_kv_obj* kv, char* key, adv_kv_obj* obj) {
	adv_lks_index_data index = adv_index_key_lks(kv->keyset, key);
	bool allocate = false;
	int type = 1;

	// First check children of type object have null value. Take that is as type index else use count_object as type_index.
	int type_index = adv_kv_fetch_obj_index_type_for_null(kv, type);
	if (type_index == -1) {
		type_index = kv->keyset->count_object;
	}
	adv_add_key_lks(keyset, key, type, type_index);
	// adding new object against the key;
	if (type_index > 0) {
		kv->children = (kv->children**)realloc(*kv->children , (type_index+1)*(sizeof(kv->children*)));
	} else {
		kv->children = (kv->children**)malloc(sizeof(kv->children*));
	}
	kv->children[type_index] = obj;
	// deleting(Assign NULL) to children,value_list, value to it index if already existing anything against the key
}

void add_str_to_adv_kv_obj(adv_kv_obj* kv, char* key, char* value) {

}

void add_arr_to_adv_kv_obj(adv_kv_obj* kv, char* key, adv_kv_array* arr) {

}

// This is the end  when root kv is of object type


/// This is all when root kv is of array type

// This is the end  when root kv is of array type


/// This is all when adding element to array type "kv"
void add_str_array_to_adv_kv_arr(adv_kv_obj* kv, char* value) {

}

// this is nested array
void add_array_array_to_adv_kv_arr(adv_kv_obj* kv, adv_kv_array* arr) {

}

void add_object_array_to_adv_kv_arr(adv_kv_obj* kv, adv_kv_obj* obj) {

}

// This is the end of adding element when "kv" is of array type

#endif
