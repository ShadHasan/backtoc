#ifndef ADVANIEN_COMMON_DS
#define ADVANIEN_COMMON_DS

typedef struct {
	unsigned short r;
	unsigned short g;
	unsigned short b;
} pixel;


typedef struct {
	char name[400];
	char** program_name_list;
} kernel_program_list_map_ds;

typedef struct {
	char name[400];
	char* program_char;
} kernel_program_map__ds;

#endif
