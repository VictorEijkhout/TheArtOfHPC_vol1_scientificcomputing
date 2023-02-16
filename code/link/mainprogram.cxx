/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>

extern "C" {
void foo_(int*);
}
  
int main() {
  int i=3;
  foo_(&i);
  printf("is this 4? %d\n",i);
  return 0;
}
