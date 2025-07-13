#include <stdio.h>
#include <string.h>


char* incrementing_char(char* temp, char c, uint length) {
	char temp1[length];
	if (temp != NULL)
		strcpy(temp1, temp);
	return temp1[length-1] = c;
}

char* file_char_content(char* file_path) {
	File *fp;
	int file_char_counter = 0;
	char c;
	char* final = NULL;
	fp = fopen(file_path, "r");
	while ((c = getc(fp))!= EOF) {
		file_char_counter++;
		final = incrementing_char(final, c, file_char_counter);
	}
	return final;
}
