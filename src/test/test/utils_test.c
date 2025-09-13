#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "c_lib/utils.h"

void valid_jaon(char* str) {
	bool valid = validate_json(str);
	if (valid) {
		printf("\nPass: Valid json");
	} else {
		printf("\nFail: Not valid json");
	}
}

void invalid_json(char* str) {
	bool valid = validate_json(str);
	if (valid) {
		printf("\nFailed: Valid json");
	} else {
		printf("\nPass: Not valid json");
	}
}

int json_validation_test() {
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
	char* jsonstr10 = "{\"key\": \"value\", \"key2\": [], \"key3\": {\"key31\":{}}";
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

	invalid_json(jsonstr1);
	invalid_json(jsonstr2);
	invalid_json(jsonstr3);
	invalid_json(jsonstr4);
	invalid_json(jsonstr6);
	invalid_json(jsonstr7);
	invalid_json(jsonstr8);
	invalid_json(jsonstr9);
	invalid_json(jsonstr10);
	invalid_json(jsonstr11);


	valid_jaon(vjsonstr1);
	valid_jaon(vjsonstr2);
	valid_jaon(vjsonstr3);
	valid_jaon(vjsonstr4);
	valid_jaon(vjsonstr5);
	valid_jaon(vjsonstr6);

}

int json_parsing_test(char* jsonstr) {
	adv_kv_or_a* collective = (adv_kv_or_a*)malloc(sizeof(adv_kv_or_a));
	collective->type = -1;
	parse_json(collective, jsonstr);
	switch(collective->type) {
		case 0:
			adv_kv_traverse_arr(collective->arr);
			break;
		case 1:
			adv_kv_traverse_obj(collective->obj);
			break;
		default:
			printf("Invalid JSON string");
			break;
	}
}

int json_test() {
	// json_validation_test();
	char* jsonstr = "{\"key\": \"value\"}";
	json_parsing_test(jsonstr);

	return 0;
}
