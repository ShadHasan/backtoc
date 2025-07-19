// C standard includes
#include <stdio.h>
#include "utilities/opencl/platform.h"
#include "model/common_data_structure.h"
#include "c_lib/math.h"
#include "c_lib/math2.h"
#include "utilities/fileIO.h"
#include "kernel_program_map/map.h"


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
	content = file_char_content("main/kernel_lib/array_add.pc");
	printf("File content: %s", content);

	// Testing common data
	kernel_program_list_map_ds kernal_list_map;

	// Testing kernel map loading

    return 0;
}
