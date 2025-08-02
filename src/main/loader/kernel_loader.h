// OpenCL includes
#include <CL/cl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	cl_platform_id devicePlatform;
	cl_device_id deviceId;
	cl_context context;
	cl_command_queue commandQueue;
	int maxWorkUnits;
} compute_context;

typedef struct {
	cl_program program;
	cl_kernel kernelArrayADD;
	cl_kernel kernelArraySUM;
} program_context;

typedef struct {
	int verbose;
} DEBUG;

// to print error messages;
DEBUG debug;

char* sample_program() {
	return "// compute element-wise sums of INPUT1 and INPUT2;"
"__kernel void ArrayADD ("
"	int  wid,"
"	int  hgt,"
"	__global float *INPUT1,"
"	__global float *INPUT2,"
"	__global float *OUTPUT"
") {"
"	int totalwork = wid * hgt;"
"	int peIndex = get_global_id(0); // get process element index ID"
"	if (peIndex >= totalwork) { // to filter extras"
"		return;"
"	}"
"	OUTPUT[peIndex] = INPUT1[peIndex] + INPUT2[peIndex];"
"}"
""
"// compute row-wise sums of INPUT;"
"__kernel void ArraySUM ("
"	int  wid,"
"	int  hgt,"
"	__global float *INPUT,"
"	__global float *OUTPUT"
") {"
"	int totalwork = hgt;"
"	int peIndex = get_global_id(0); // get process element index ID"
"	if (peIndex >= totalwork) { // to filter extras"
"		return;"
"	}"
"	int i, startindex;"
"	float sum = 0.0f;"
"	startindex = wid * peIndex;"
"	for (i = 0; i < wid; i++) { // compute the sum of the row;"
"		sum += INPUT[startindex + i];"
"	}"
"	OUTPUT[peIndex] = sum;"
"}";
}

int selectDevice(compute_context cctx) {
	int i, j;
	cl_int ret;
	cl_uint numPlatforms;
	cl_uint numDevices;

	// get platform IDs;
	ret = clGetPlatformIDs(0, NULL, &numPlatforms);
	if (CL_SUCCESS != ret) {
 		if (debug.verbose) printf("Error clGetPlatformIDs() : %d\n", ret);
		return ret;
	}

	cl_platform_id platforms[numPlatforms];
	ret = clGetPlatformIDs(numPlatforms, platforms, NULL);

	size_t maxWItemSize3D[3];
	char local_dev_buf[250];
	cl_device_id devices[20]; // maximum number of GPU devices, say, 20;

	// search named device or the first GPU device if not specified;
    for (i = 0; i < numPlatforms; i++) {
		ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
		if (CL_SUCCESS != ret) {
			continue;
		}
 		ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU,
                	numDevices, devices, NULL);
		if (CL_SUCCESS != ret) {
			continue;
		}

       		for (j=0; j < numDevices; j++) {
            		ret = clGetDeviceInfo(devices[j], CL_DEVICE_NAME,
				sizeof(local_dev_buf), local_dev_buf, NULL);
			if (CL_SUCCESS != ret) {
 				if (debug.verbose) printf("Error clGetDeviceInfo() : %d\n", ret);
				return ret;
			}

			if (devicename==NULL || strcmp(devicename, local_dev_buf) == 0) {
         			ret = clGetDeviceInfo(devices[j],
                  			CL_DEVICE_MAX_WORK_ITEM_SIZES,
                   		 	sizeof(maxWItemSize3D), &maxWItemSize3D, NULL);

				// set prefered local group size==maxWorkUnits;
         		cctx.maxWorkUnits = (int)maxWItemSize3D[2];
				cctx.deviceId = devices[j];
				cctx.devicePlatform = platforms[i];

				delete [] platforms;
				return 0;
			}
		}
	}
	if (debug.verbose) {
		if (devicename==NULL) {
			printf("Error device not found.\n");
		} else {
			printf("Error device not found: %s\n", devicename);
		}
	}
	return -1;
}

int prepareProgramAndShadersWithData(compute_context cctx, char *programsource, program_context pctx) {
	// calculate program source length;
	int leng = 0;
	while (true) {
		if (programsource[leng]==0) {
			break;
		}
		leng++;
	}

	size_t src_size = leng;
	int ret;

	// create and build program;
	program = clCreateProgramWithSource(cctx.context,
			1, (const char**)&programsource, &src_size, &ret);
	if (CL_SUCCESS != ret) {
 		if (debug.verbose) printf("Error clCreateProgramWithSource() : %d\n", ret);
		return ret;
	}
	ret = (int)clBuildProgram(pctx.program, 1, &cctx.deviceId, NULL, NULL, NULL);
	if (CL_SUCCESS != ret) {
 		if (debug.verbose) printf("Error clBuildProgram() : %d\n", ret);
		return ret;
	}

	// create first kernel;
	kernelArrayADD = clCreateKernel(pctx.program, "ArrayADD", &ret);
	if (CL_SUCCESS != ret) {
 		if (debug.verbose) printf("Error clCreateKernel() : %d\n", ret);
		return ret;
	}

	// create second kernel;
	kernelArraySUM = clCreateKernel(pctx.program, "ArraySUM", &ret);
	if (CL_SUCCESS != ret) {
 		if (debug.verbose) printf("Error clCreateKernel() : %d\n", ret);
		return ret;
	}

	return 0;
}

int createConextAndCommandQueue(compute_context cctx) {
	int ret;

	// create context;
	cl_context_properties props[3];
	props[0] = CL_CONTEXT_PLATFORM;
	props[1] = (cl_context_properties)cctx.devicePlatform;
	props[2] = 0;
	cctx.context = clCreateContext(props, 1, &cctx.deviceId, NULL, NULL, &ret);
	if (CL_SUCCESS != ret) {
 		if (debug.verbose) printf("Error clCreateContext() : %d\n", ret);
		return ret;
	}

	cctx.commandQueue = clCreateCommandQueue(cctx.context, cctx.deviceId, 0, &ret);
	if (CL_SUCCESS != ret) {
 		if (debug.verbose)
 			printf("Error clCreateCommandQueueWithProperties() : %d\n", ret);
		return ret;
	}

	return 0;
}

function gpu_loader() {
	debug.verbose = 1;

	// selected GPU device, context and command queue;
	compute_context c_ctx;
	c_ctx.devicePlatform = NULL;
	c_ctx.deviceId = NULL;
	c_ctx.context = NULL;
	c_ctx.commandQueue = NULL;
	// recommended local work group size to be size core here is MALI GPU 610 core;
	c_ctx.maxWorkUnits = 16;


	// program and kernels;
	program_context p_ctx;
	p_ctx.program = NULL;
	p_ctx.kernelArrayADD = NULL;
	p_ctx.kernelArraySUM = NULL;

	// kernel program
	char* programchar = sample_program();

	int ret = 0;
	int wid = 100;
	int hgt = 100;
	int i,j = 0;

	// input value arrays
	float input1[wid*hgt];
	float input2[wid*hgt];

	for (i = 0; i < wid; i++) {
		for (j = 0; j < hgt; j++) {
			input1[i*hgt + j] = 2.00;
			input2[i*hgt + j] = 5.00;
		}
	}

	createConextAndCommandQueue(c_ctx);
	prepareProgramAndShadersWithData(c_ctx, programchar, p_ctx);

	// populate input arrays.

	// create GPU memory array blocks with initial input data.
	// this will copy input1 and input2 data into GPU memory blocks.
	cl_mem memINPUT1 = clCreateBuffer(c_ctx.context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_float) * (wid*hgt),
		input1, &ret);
	cl_mem memINPUT2 = clCreateBuffer(c_ctx.context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_float) * (wid*hgt),
		input2, &ret);

	// create GPU memory blocks for output values
	cl_mem memOUTPUT1 = clCreateBuffer(c_ctx.context,
		CL_MEM_READ_WRITE,
		sizeof(cl_float) * (wid*hgt),
		NULL, &ret);
	cl_mem memOUTPUT2 = clCreateBuffer(c_ctx.context,
		CL_MEM_READ_WRITE,
		sizeof(cl_float) * hgt,
		NULL, &ret);



	int k = 0;
	cl_kernel kernel;
	size_t global_work_size;
	size_t local_work_size;
	int localunits, globalunits, totalworkunits;

	// enqueue first command;
	kernel = p_ctx.kernelArrayADD;
	k = 0; // set kernel parameter arguments;
	clSetKernelArg(kernel, k++, sizeof(cl_int), &wid);
	clSetKernelArg(kernel, k++, sizeof(cl_int), &hgt);
	clSetKernelArg(kernel, k++, sizeof(cl_mem), &memINPUT1);
	clSetKernelArg(kernel, k++, sizeof(cl_mem), &memINPUT2);
	clSetKernelArg(kernel, k++, sizeof(cl_mem), &memOUTPUT1);

	// Ideally, the value of "maxWorkUnits" should be the core size of each GPU computing unit.
	// However OpenCL does not support API to get this value. So it will be set to
	// the lowest dimension maximum size, when you select a device.
	// If you know the core size of each GPU computing unit, you can override this value
	// as follows. For example, 16 is the core size of each computing unit for Orange Pi 5.
	// maxWorkUnits = 16;

	// determine local and global work sizes;
	totalworkunits = wid * hgt; // for each array element;
	localunits = c_ctx.maxWorkUnits;
	if (totalworkunits <= localunits) {
		localunits  = totalworkunits;
		globalunits = totalworkunits;
	} else {
		globalunits = (((totalworkunits - 1) / localunits) + 1) * localunits;
	}
	global_work_size = globalunits;
	local_work_size = localunits;

	cl_int ret = clEnqueueNDRangeKernel(commandQueue, p_ctx.kernel, 1, NULL,
		&global_work_size, &local_work_size, 0, NULL, NULL);
	if (CL_SUCCESS != ret) {
		printf("Enqueue failed: %d\n", ret);
	}

	// the following is to notify GPU to start processing.
	// This is optional and needed only after the first enqueue!
	clFlush(c_ctx.commandQueue);

	// enqueue second command;
	kernel = p_ctx.kernelArraySUM;
	k = 0; // set kernel parameter arguments;
	clSetKernelArg(kernel, k++, sizeof(cl_int), &wid);
	clSetKernelArg(kernel, k++, sizeof(cl_int), &hgt);
	clSetKernelArg(kernel, k++, sizeof(cl_mem), &memOUTPUT1); // output of previous command
	clSetKernelArg(kernel, k++, sizeof(cl_mem), &memOUTPUT2);

	// determine local and global work sizes;
	totalworkunits = hgt; // for each row;
	localunits = c_ctx.maxWorkUnits;
	if (totalworkunits <= localunits) {
		localunits  = totalworkunits;
		globalunits = totalworkunits;
	} else {
		globalunits = (((totalworkunits - 1) / localunits) + 1) * localunits;
	}
	global_work_size = globalunits;
	local_work_size = localunits;

	ret = clEnqueueNDRangeKernel(c_ctx.commandQueue, kernel, 1, NULL,
		&global_work_size, &local_work_size, 0, NULL, NULL);
	if (CL_SUCCESS != ret) {
		printf("Enqueue failed: %d\n", ret);
	}

	float output[hgt]; // to retrieve value here!

	clFinish(c_ctx.commandQueue); // wait until both commands are completed;
	clEnqueueReadBuffer(c_ctx.commandQueue, memOUTPUT2, CL_TRUE, 0,
		sizeof(cl_float) * hgt, output,
		0, NULL, NULL);

	for (j = 0; j < hgt; j++) {
		printf("%f -> ", output[j]);
	}

}

