#ifndef ADVANIEN_COMMON_KEYVAL
#define ADVANIEN_COMMON_KEYVAL

// Dictionary entire data structure with hierarchal. kv stands for key-value. Hence it is
// like json datastructure
typedef struct adv_kv_obj adv_kv_obj;
typedef struct adv_kv_array adv_kv_array;

// array each instance blueprint
// please note array can have nested array
struct adv_kv_array_ins_bp{
	char* type; // array, object, string
	adv_kv_obj obj;
	adv_kv_array* value_list;
	char* value;
};

// key list blueprint. It helps to keep track of used key. Hence used to prevent duplicate
// key for data structure;
typedef struct {
	char* key;
} key_list_bp;

struct adv_kv_obj {
	char* key;
	key_list_bp* used_keys;
	char* type; // array, object, string
	adv_kv_obj children;     // when type is object
	adv_kv_array* value_list; // when type is array, then again each element of array can be array, object, string
	char* value; // when type is string
};

typedef struct {
	char* key = "root";
	adv_kv_obj* child;
	unsigned int child_count;
} adv_kv;

// Initialize key value derived data structure
adv_kv adv_init_kv() {
	adv_key_value obj;
	obj.adv_key_value_obj = NULL;
	return obj;
}

void adv_add_string_obj_kv(adv_kv* kv, char* key, char* value) {
	adv_kv_obj obj;
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

void adv_add_array_obj_kv(adv_kv kv, char** value_list) {
	adv_key_value obj;
	obj.adv_key_value_obj = NULL;
	return obj;
}

#endif
