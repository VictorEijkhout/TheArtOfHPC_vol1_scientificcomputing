// -*- c++ -*-
#include "test.h"
__global__ void test_print(){
  printf("Hello World!\n");
}

void wrap_test_print() {
  test_print<<<1, 1>>>();
  cudaDeviceSynchronize();	
  return;
}