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

void setelement( double x[], int i, double v ) {
  x[i] = v;
}

int main() {
  double x[4];

  setelement( x, 1, 3.14 );
  printf("x[%d]=%e\n",1,x[1]);

  return 0;
}
