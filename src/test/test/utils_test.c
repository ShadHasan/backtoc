#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "c_lib/utils.h"

int json_test() {
	char* jsonstr = "{\"key\": \"value\", \"key2\": [], \"key3\": {}}";
	char* jsonstr1 = "{\"key\": \"value\", \"key2\": [], \"key3\": {{}}";
	char* jsonstr2 = "{\"key\": \"value\", \"key2\": [], \"key3\": {}}}";
	char* jsonstr3 = "{";
	char* jsonstr4 = "";
	char* jsonst5 = "{}";
	char* jsonstr6 = "}";
	char* jsonstr7 = "[";
	char* jsonstr8 = "[]";
	char* jsonstr9 = "]";
	/*
	int len = strlen(jsonstr);
	int i;

	printf("\n");
	for(i=0;i<len;i++) {
		printf("char: (%d - %c),", jsonstr[i],jsonstr[i]);
	}
	printf("\n");
	*/
	bool valid = validate_json(jsonstr1);
	if (valid) {
		printf("\nValid json");
	} else {
		printf("\nNot valid json");
	}
	return 0;
}
