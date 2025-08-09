#ifndef ADVANIEN_COMMON_KEYVAL
#define ADVANIEN_COMMON_KEYVAL

#include <stdlib.h>
#include "model/common/keyval.h"
#include <string.h>

// Dictionary entire data structure with hierarchical. "kv" stands for key-value. Hence it is

// like json datastructure
typedef struct adv_kv_obj adv_kv_obj;
typedef struct adv_kv_array adv_kv_array;

// array each instance blueprint
// please note array can have nested array
struct adv_kv_array{
	char* type; // array, object, string
	adv_kv_obj obj;
	adv_kv_array* value_list;
	char* value;
};


struct adv_kv_obj {
	char* key;

	// key list blueprint. It helps to keep track of used key. Hence used to prevent duplicate
	// key for data structure
	adv_l_key_set* used_keys;

	char* type; // array, object, string

	adv_kv_obj* children;     // when type is object
	adv_kv_array* value_list; // when type is array, then again each element of array can be array, object, string
	char* value; // when type is string
};


// Initialize key value derived data structure
adv_kv_array adv_init_kv(char* type) {
	// Root object
	adv_kv_obj obj;

	// initializing root key
	obj.key = "(0)";
	obj.used_keys = (adv_l_key_set*)malloc(sizeof(adv_l_key_set));
	adv_init_lks(obj.used_keys);
	adv_add_key_lks(obj.used_keys, obj.key);

	// root keyval is alway of type object. It value may be array, object, string etc
	// but root itself is a object
	strcpy(obj.type, type);

	obj.children = NULL;
	obj.value_list = NULL;
	obj.value = NULL;

	return obj;
}

/// This is all when root kv is of object type
void add_obj_to_adv_kv_obj(adv_kv* kv, char* key, char* value) {
	adv_kv_obj* obj;
	obj = (adv_kv_obj*)malloc(sizeof(adv_kv_obj));
	obj.key = key;
	obj.type = "string";
	obj.value = value;
	if (kv->adv_key_value_obj == NULL) {
		kv->adv_key_value_obj = (adv_kv_obj*)malloc(sizeof(adv_kv_obj));
		kv->child_count = 1;
		kv->adv_key_value_obj[0] = obj;

		kv->used_keys = (key_list_bp*)malloc(sizeof(key_list_bp));
		kv->used_keys[0]
	} else {
		kv->adv_key_value_obj = (adv_kv_obj*)realloc(kv->adv_key_value_obj, sizeof(adv_kv_obj)*(kv->child_count + 1));
		kv->adv_key_value_obj[kv->child_count] = obj;
		kv->child_count++;
	}
}

void add_str_to_adv_kv_obj(adv_kv* kv, char* key, char* value) {

}

void add_arr_to_adv_kv_obj(adv_kv* kv, char* key, adv_kv_array* arr) {

}


// This is the end  when root kv is of object type

/// This is all when root kv is of array type

// This is the end  when root kv is of array type


/// This is all when adding element to array type "kv"
void add_str_array_to_adv_kv_obj(adv_kv* kv, char* type, char* value) {

}

// this is nested array
void add_array_array_to_adv_kv_obj(adv_kv* kv, char* type, adv_kv_array* arr) {

}

void add_object_array_to_adv_kv_obj(adv_kv kv, char* type, adv_kv_obj* obj) {

}

// This is the end of adding element when "kv" is of array type

#endif
