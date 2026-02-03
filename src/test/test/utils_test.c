#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "c_lib/utils.h"

void valid_json(char* str) {
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
	printf("\n*************** JSON Validation Test Start **********************\n");
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

	valid_json(jsonstr);
	valid_json(vjsonstr1);
	valid_json(vjsonstr2);
	valid_json(vjsonstr3);
	valid_json(vjsonstr4);
	valid_json(vjsonstr5);
	valid_json(vjsonstr6);
	printf("\n*************** JSON Validation Test End **********************\n");
	return 0;
}

int multi_stack_test() {
	printf("\n*************** MultiStack Test Start **********************\n");
	adv_json_depth *depth = init_adv_json_depth();
	int type;

	push_to_kv_multi_stack(depth, NULL, NULL, "hello", NULL);
	push_to_kv_multi_stack(depth, NULL, NULL, NULL, "world");

	type = pop_to_kv_multi_stack(depth);
	printf("%d, %s", type, depth->depth_temp_value);
	type = pop_to_kv_multi_stack(depth);
	printf("%d, %s", type, depth->depth_temp_key);
	printf("\n");
	printf("\n*************** MultiStack Test End **********************\n");
	return 0;
}

int validate_json_parse(char* jsonstr) {
	printf("\nTesting string ... %s\n", jsonstr);
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
	return 0;
}

int json_parsing_test() {
	printf("\n*************** JSON Parsing Test Start **********************\n");
	char* vjsonstr1 = "{\"key\": \"value\"}";
	char* vjsonstr2 = "{\"key\": \"value\", \"key2\": [], \"key3\": {\"key3\":{}}}";
	char* vjsonstr3 = "{\"k1\": {\"k1\": \"s1\", \"k2\": \"s2\"}, \"k2\": [\"s1\", \"s2\"], \"k3\": \"s3\", \"k4\": {\"k1\": {\"k1\": \"s1\"}, \"k2\": [\"s1\", \"s2\"], \"k3\": \"s1\"}}";
	char* vjsonstr4 = "{\"k1\": {\"k1\": \"s1\", \"k2\": \"s2\"}, \"k2\": [\"s1\", \"s2\"]"
			", \"k3\": \"s3\", \"k4\": {\"k1\": {\"k1\": \"s1\"}, \"k2\": [\"s1\", \"s2\"], \"k3\": \"s1\"},"
			"\"k5\": [{\"k1\": \"s1\", \"k2\": \"s2\"}, [\"s1\", \"s2\"], \"s1\"],"
			"\"k6\": {}, \"k7\": [], \"k8\": {\"k3\": {}}, \"k9\": [[]],"
			"\"k10\": [{}, []], \"k11\": [{\"k1\": \"s1\"}, [], {\"k1\": []}]"
			"}";

	// validate_json_parse(vjsonstr1);
	// validate_json_parse(vjsonstr2);
	validate_json_parse(vjsonstr4);
	printf("\n*************** JSON Parsing Test End **********************\n");
	return 0;
}

int json_test() {
	json_validation_test();

	multi_stack_test();
	json_parsing_test();

	return 0;
}
