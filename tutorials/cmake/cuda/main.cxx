/****************************************************************
 **** taken from: https://stackoverflow.com/questions/62139760/using-cmake-for-compiling-c-with-cuda-code
 ****************************************************************/

#include <stdio.h>
#include "kernels/test.cuh"

int main() {
  wrap_test_print();
  return 0;
}
