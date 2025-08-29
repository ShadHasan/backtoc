#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "c_lib/utils.h"

int json_test() {
	char* jsonstr = "{\"key\": \"value\", \"key2\": [], \"key3\": {}}";
	/*
	int len = strlen(jsonstr);
	int i;

	printf("\n");
	for(i=0;i<len;i++) {
		printf("char: (%d - %c),", jsonstr[i],jsonstr[i]);
	}
	printf("\n");
	*/
	bool valid = validate_json(jsonstr);
	if (valid) {
		printf("Valid json");
	} else {
		printf("Not valid json");
	}
	return 0;
}
