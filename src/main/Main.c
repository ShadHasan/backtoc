// C standard includes
#include <stdio.h>
#include "utilities/opencl/platform.h"
#include "model/2d_graph.h"
#include "model/common_data_structure.h"
#include "c_lib/math.h"
#include "c_lib/math2.h"
#include "utilities/fileIO.h"
#include "model/common/keyval.h"
#include "model/common/stack.h"
#include "test/utils_test.c"
//#include "kernel_program_map/map.h"

int main()
{

	char pl_message[1000];	// Since char * or char [] are both variable are already reference address. we don't need to use ampersand.
	print_platform(pl_message);
	printf("Final output: %s\n", pl_message);

	// Testing struct initialization after long time located in common_data_structure
	pixel p0[10];
	int p_iter;
	for (p_iter = 0; p_iter < 10; p_iter++) {
		p0[p_iter].r = 100;
		p0[p_iter].g = 200;
		p0[p_iter].b = 255;
	}
	printf("Zero pixel : %d %d %d\n", p0[0].r, p0[0].g, p0[0].b);

	// Testing basic c_lib
	float sqr;
	sqr = math_square(3.0);
	printf("Square of 3 is %f", sqr);

	// Testing fileIO Library
	char* content;
	// Please keep in mind when file path providing to file_char_content is non existent will lead to as well segmentation fault;
	content = file_char_content("main/kernel_program_lib/array_add.pc");
	printf("File content: %s", content);

	// simple immutable string
	// char* test_string = "Thislong\n";


	 char* test_string = "This is very long long string for the test that it can be by default initialized and it is immutable "
			"hence changing anything in the string will lead to segmentation. And this is just for test its behavior";

	unsigned int char_count = 0;
	while(test_string[char_count] != '\0') {
		printf("%c", test_string[char_count]);
		char_count++;
	}
	printf("\n");

	// initializing keyvalue, 1 mean object, 0 mean array
	// you cannot initialize as string
	adv_kv_obj* kv1 = adv_init_kv(1);
	char c;


	/*
	// Verify stack feature
	adv_char_stack* c_stack;// = init_adv_char_stack('f');
	c_stack->c = NULL;
	c_stack->size = 0;
	push_adv_char_stack(c_stack, 'f');
	push_adv_char_stack(c_stack, 'i');
	push_adv_char_stack(c_stack, 'r');
	c = seek_adv_char_stack(c_stack);
	printf("\n seek stack: %c \n",c);
	c = pop_adv_char_stack(c_stack);
	printf("\n pop stack: %c \n",c);
	c = seek_adv_char_stack(c_stack);
	printf("\n %c \n",c);
	push_adv_char_stack(c_stack, 'r');
	push_adv_char_stack(c_stack, 's');
	push_adv_char_stack(c_stack, 't');

	while(c_stack->size > 0) {
		c = pop_adv_char_stack(c_stack);
		printf("\n pop stack: %c \n",c);
	}
	*/

	// kernel_program_list_map_ds kernal_list_map;

	// Testing kernel map loading

	// testing
	json_test();

    return 0;
}
