// OpenCL includes
#include <CL/cl.h>
#include <string.h>
#include <stdlib.h>

void print_platform(char *buffer) {
	cl_int CL_err = CL_SUCCESS;
    cl_uint numPlatforms = 0;
    cl_int ret;


    CL_err = clGetPlatformIDs( 0, NULL, &numPlatforms );

    if (CL_err == CL_SUCCESS)
        sprintf(buffer, "%u platform(s) found\n", numPlatforms);
    else
    	sprintf(buffer, "clGetPlatformIDs(%i)\n", CL_err);

    // Declare platform array and initialize
    cl_platform_id platforms[numPlatforms];
    ret = clGetPlatformIDs(numPlatforms, platforms, NULL);

    // Declare device-id for fetch
    cl_uint numDevices;
    int i;
    char temp_buffer[400];
    for (i = 0; i < (int)numPlatforms; i++) {
    	ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
    	if (CL_SUCCESS == ret) {
    		sprintf(temp_buffer, "platform count %u, device count: %i, device found status: (%i), Device no: %u\n", numPlatforms, i, ret, numDevices);
    	} else {
    		sprintf(temp_buffer, "device found status: (%i)\n",  ret);
    	}
    	strcat(buffer, temp_buffer);
    }

}
