#include "../utilities/fileIO.h"
#include "../model/common_data_structure.h"

#ifndef ADVANIEN_KERNEL_PROGRAM_MAPPER
#define ADVANIEN_KERNEL_PROGRAM_MAPPER


bool _adv_string_contain_char(char* string, char c2){
	int i = 0;
	while(string[i] == '\0'){
		if(string[i] == c2) {
			return true;
		}
		i++;
	}
	return false;
}

void _adv_parse_map(char* content, unsigned int length) {
	int i;
	char object_open = '{';
	char object_close = '}';
	char value_array_open = '[';
	char value_array_close = ']';
	char literal_open_close = '"';
	char key_value_separator = ':';

	// if value
	char next_literal = ',';

	char* open_type_char = "{[\"";
	char* close_type_char = "}]\"";

	// Three types of literal object key, object string, object array
	char* literal_stack;

	char* open_type_stack;


	// ignoring leading and preceding space and newline
	for (i = 0; i<length; i++) {
		if (_adv_contain(reserved_char, content[i])) {
			// Trigger literal type
		} else {
			if (content[i] == ' ' || content[i] == '\n') {

			} else {

			}
		}
	}
}

void map_map_kernel_program_data(kernel_program_list_map_ds *prgram_dictionary) {
	char* content = NULL;
	unsigned int content_length;
	content_length = file_char_content_return_length("main/kernel_program_map/map.data", content);

	printf("length %d, %s", content_length, content);
}

#endif
