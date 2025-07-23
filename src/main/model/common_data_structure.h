#ifndef ADVANIEN_COMMON_DS
#define ADVANIEN_COMMON_DS

typedef struct {
	unsigned short r;
	unsigned short g;
	unsigned short b;
} pixel;


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


#endif
