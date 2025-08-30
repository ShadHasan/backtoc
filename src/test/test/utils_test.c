#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "c_lib/utils.h"

int json_test() {
	char* jsonstr = "{\"key\": \"value\", \"key2\": [], \"key3\": {}}";

	// List of invalid json
	char* jsonstr1 = "{\"key\": \"value\", \"key2\": [], \"key3\": {{}}";
	char* jsonstr2 = "{\"key\": \"value\", \"key2\": [], \"key3\": {}}}";
	char* jsonstr3 = "{";
	char* jsonstr4 = "";

	char* jsonstr6 = "}";
	char* jsonstr7 = "[";
	char* jsonstr8 = "[,]";
	char* jsonstr9 = "]";
	char* jsonstr10 = "{\"key\": \"value\", \"key2\": [], \"key3\": {\"key3\":{}}";
	char* jsonstr11 = "{,}";

	// List of valid json
	char* vjsonstr1 = "{\"key\": \"value\", \"key2\": [], \"key3\": {\"key3\":{}}}";
	char* vjsonstr2 = "{}";
	char* vjsonstr3 = "[]";
	char* vjsonstr4 = "{\"key\": \"{\"}";
	char* vjsonstr5 = "[\"\"]";
	char* vjsonstr6 = "[\",\"]";

	/*
	int len = strlen(jsonstr);
	int i;

	printf("\n");
	for(i=0;i<len;i++) {
		printf("char: (%d - %c),", jsonstr[i],jsonstr[i]);
	}
	printf("\n");
	*/
	bool valid = validate_json(vjsonstr1);
	if (valid) {
		printf("\nValid json");
	} else {
		printf("\nNot valid json");
	}
	return 0;
}
