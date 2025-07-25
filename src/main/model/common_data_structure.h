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


// Dictionary entire data structure with hierarchal
typedef struct adv_key_value_obj adv_key_value_obj;

typedef struct {
	char** value;

} adv_key_value_array;

struct adv_key_value_obj {
	char* key;
	char* type; // array, object, string
	adv_key_value_obj* children;     // when type is object
	adv_key_value_array* value_list; // when type is array
	char* value; // when type is string
};

typedef struct {
	char* key = "root";
	adv_key_value_obj* child;
} adv_key_value_ds;


#endif
