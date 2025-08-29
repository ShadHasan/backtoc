#include <stdio.h>
#include <string.h>

int json_test() {
	char* jsonstr = "{\"key\": \"value\"}";
	int len = strlen(jsonstr);
	int i;
	for(i=0;i<len;i++) {
		printf("char: %d,", jsonstr[i]);
	}
	return 0;
}
