// OpenCL includes
#include <CL/cl.h>
#include <string.h>
#include <stdlib.h>

void print_platform(char *message_buffer) {
	cl_int CL_err = CL_SUCCESS;
    cl_uint numPlatforms = 0;
    cl_int ret;


    CL_err = clGetPlatformIDs( 0, NULL, &numPlatforms );

    if (CL_err == CL_SUCCESS)
        sprintf(message_buffer, "%u platform(s) found\n", numPlatforms);
    else
    	sprintf(message_buffer, "clGetPlatformIDs(%i)\n", CL_err);

    // Declare platform array and initialize
    cl_platform_id platforms[numPlatforms];
    ret = clGetPlatformIDs(numPlatforms, platforms, NULL);

    // Declare device-id for fetch
    cl_uint numDevices;

    int i, j;

    char local_dev_buf[250];
    cl_device_id devices[20]; // maximum number of GPU devices, say, 20;

    char temp_message_buffer[400];

    for (i = 0; i < (int)numPlatforms; i++) {
    	ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
    	if (CL_SUCCESS == ret) {
    		sprintf(temp_message_buffer, "In total platform: %u, platform serial count: %i, device found status in platform(0 mean good): %i, Total Device found: %u\n", numPlatforms, i, ret, numDevices);
    	} else {
    		sprintf(temp_message_buffer, "device found status: (%i)\n",  ret);
    		continue;
    	}
    	ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
		if (CL_SUCCESS != ret) {
			continue;
		}
		strcat(message_buffer, temp_message_buffer);
		for (j=0; j < (int)numDevices; j++) {
			ret = clGetDeviceInfo(devices[j], CL_DEVICE_NAME, sizeof(local_dev_buf), local_dev_buf, NULL);
			if (CL_SUCCESS != ret) {
				sprintf(temp_message_buffer, "Error clGetDeviceInfo() : %d\n", ret);
			} else {
				sprintf(temp_message_buffer, "Found device name: : %s\n", local_dev_buf);
			}
		}
    	strcat(message_buffer, temp_message_buffer);
    }

}
