#include "hipacc_cl_altera.clh"

#define HIPACC_MAX_WIDTH     1024
#define HIPACC_MAX_HEIGHT    1024

#define getWindow(ARRAY, __y, __x) ARRAY[__y][__x]

float clGaussianFilterGKernelKernel(float input[5][5]){ 
      float sum = 0; 
      sum += 0.005008f * getWindow(input, 0, 0);
      sum += 0.017300f * getWindow(input, 0, 1);
      sum += 0.026151f * getWindow(input, 0, 2);
      sum += 0.017300f * getWindow(input, 0, 3);
      sum += 0.005008f * getWindow(input, 0, 4);
      sum += 0.017300f * getWindow(input, 1, 0);
      sum += 0.059761f * getWindow(input, 1, 1);
      sum += 0.090339f * getWindow(input, 1, 2);
      sum += 0.059761f * getWindow(input, 1, 3);
      sum += 0.017300f * getWindow(input, 1, 4);
      sum += 0.026151f * getWindow(input, 2, 0);
      sum += 0.090339f * getWindow(input, 2, 1);
      sum += 0.136565f * getWindow(input, 2, 2);
      sum += 0.090339f * getWindow(input, 2, 3);
      sum += 0.026151f * getWindow(input, 2, 4);
      sum += 0.017300f * getWindow(input, 3, 0);
      sum += 0.059761f * getWindow(input, 3, 1);
      sum += 0.090339f * getWindow(input, 3, 2);
      sum += 0.059761f * getWindow(input, 3, 3);
      sum += 0.017300f * getWindow(input, 3, 4);
      sum += 0.005008f * getWindow(input, 4, 0);
      sum += 0.017300f * getWindow(input, 4, 1);
      sum += 0.026151f * getWindow(input, 4, 2);
      sum += 0.017300f * getWindow(input, 4, 3);
      sum += 0.005008f * getWindow(input, 4, 4);

      return sum; 
}

__kernel __attribute__((reqd_work_group_size(1, 1, 1))) 
void lambda_141290(__global float* restrict  OUT, __global float* restrict  IN) {
    process(1, float, float, OUT, ARRY, IN, ARRY, HIPACC_MAX_WIDTH, HIPACC_MAX_HEIGHT, clGaussianFilterGKernelKernel, 5, 5, UNDEFINED);
}
