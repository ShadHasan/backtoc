#include "../utilities/fileIO.h"
#include "../model/common_data_structure.h"

#ifndef ADVANIEN_KERNEL_PROGRAM_MAPPER
#define ADVANIEN_KERNEL_PROGRAM_MAPPER


bool _adv_contain(char* string, char c2){
	return false;
}

void _adv_parse_map(char* content, unsigned int length) {
	int i;
	char object_open = '{';
	char object_close = '}';
	char value_array_open = '[';
	char value_array_close = ']';
	char literal_open_close = '"';

	char* reserved_char = "{}[]\",";
	// ignoring leading and preceding space and newline
	for (i = 0; i<length; i++) {

	}
}

void map_map_kernel_program_data(kernel_program_list_map_ds *prgram_dictionary) {
	char* content = NULL;
	unsigned int content_length;
	content_length = file_char_content_return_length("main/kernel_program_map/map.data", content);

	printf("length %d, %s", content_length, content);
}

#endif
