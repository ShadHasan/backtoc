#ifndef ADVANIEN_COMMON_DS
#define ADVANIEN_COMMON_DS

// It is kernel job set that is a name against the "programchar" which is a kernel function,
// and kernel job set is the array/list of such function.
typedef struct {
	char name[400];
	char** program_name_list;
} adv_kernel_program_list_map_ds;

typedef struct {
	char name[400];
	char* program_char;
} adv_kernel_program_map__ds;

//
typedef struct {
	char* key;

} adv_parsed_program_object;


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

struct adv_kv_obj {
	char* key;
	char* type; // array, object, string
	adv_kv_obj children;     // when type is object
	adv_kv_array* value_list; // when type is array, then again each element of array can be array, object, string
	char* value; // when type is string
};

typedef struct {
	char* key = "root";
	adv_kv_obj* child;
} adv_kv;

adv_kv adv_create_kv() {
	adv_key_value obj;
	obj.adv_key_value_obj = NULL;
	return obj;
}

void adv_add_string_obj_kv(adv_kv kv, char* value) {
	adv_key_value obj;
	obj.adv_key_value_obj = NULL;
	return obj;
}

void adv_add_array_obj_kv(adv_kv kv, char** value_list) {
	adv_key_value obj;
	obj.adv_key_value_obj = NULL;
	return obj;
}

#endif
