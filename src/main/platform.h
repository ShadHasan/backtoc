// OpenCL includes
#include <CL/cl.h>
#include <string.h>
#include <stdlib.h>

void print_platform(char *buffer) {
	cl_int CL_err = CL_SUCCESS;
    cl_uint numPlatforms = 0;


    CL_err = clGetPlatformIDs( 0, NULL, &numPlatforms );

    if (CL_err == CL_SUCCESS)
        sprintf(buffer, "%u platform(s) found\n", numPlatforms);
    else
    	sprintf(buffer, "clGetPlatformIDs(%i)\n", CL_err);

}
