// OpenCL includes
#include <CL/cl.h>


function gpu_loader(char* kernel_job_set) {
	int verbose = 1; // to print error messages;

	// selected GPU device, context and command queue;
	cl_platform_id   devicePlatform = NULL;
	cl_device_id     deviceId = NULL;
	cl_context       context = NULL;
	cl_command_queue commandQueue = NULL;

	// recommended local work group size;
	int maxWorkUnits = 16;

	// program and kernels;
	cl_program program = NULL;
	cl_kernel*  program_list = NULL;
}
