#include "../utilities/fileIO.h"
#include "../model/common_data_structure.h"

#ifndef ADVANIEN_KERNEL_PROGRAM_MAPPER
#define ADVANIEN_KERNEL_PROGRAM_MAPPER


void map_map_kernel_program_data(kernel_program_list_map_ds *prgram_dictionary) {
	char* content = NULL;
	unsigned int content_length;
	content_length = file_char_content_return_length("main/kernel_program_map/map.data", content);

	printf("length %d, %s", content_length, content);
}

#endif
