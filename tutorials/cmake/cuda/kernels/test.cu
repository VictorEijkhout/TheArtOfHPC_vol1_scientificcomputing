/****************************************************************
 **** taken from: https://stackoverflow.com/questions/62139760/using-cmake-for-compiling-c-with-cuda-code
 ****************************************************************/

#include "test.cuh"
__global__ void test_print(){
  printf("Hello World!\n");
}

void wrap_test_print() {
  test_print<<<1, 1>>>();
  return;
}