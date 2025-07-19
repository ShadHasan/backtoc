#include <stdio.h>
#include <string.h>

#ifndef ADVANIEN_FILEIO
#define ADVANIEN_FILEIO

char* incrementing_char(char* ptr, char c, uint length) {
	if (ptr != NULL) {
		ptr = (char *)realloc(ptr, length * sizeof(char));
	} else {
		ptr = (char *)malloc(sizeof(char) * 1);
	}
	ptr[length-1] = c;
	return ptr;
}

char* file_char_content(char* file_path) {
	FILE *fp;
	int file_char_counter = 0;
	int c;
	char* final = NULL;
	fp = fopen(file_path, "r");
	while ((c = getc(fp))!= EOF) {
		file_char_counter++;
		final = incrementing_char(final, (char)c, file_char_counter);
	}
	return final;
}


uint file_char_content_return_length(char* file_path, char* final) {
	FILE *fp;
	uint file_char_counter = 0;
	int c;
	fp = fopen(file_path, "r");
	while ((c = getc(fp))!= EOF) {
		file_char_counter++;
		final = incrementing_char(final, (char)c, file_char_counter);
	}
	return file_char_counter;
}

#endif
