/****************************************************************
 ****
 **** This program source is part of
 **** Introduction to High-performance Scientific Computing
 **** by Victor Eijkhout
 **** copyright Victor Eijkhout 2011-2020
 ****
 **** gdb example program
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>

int main(int argc,char **argv) {
  int nmax,i;
  float *squares,sum;

  printf("loop upper bound?\n");
  fscanf(stdin,"%d",nmax);
  for (i=1; i<=nmax; i++) {
    squares[i] = 1./(i*i);
    sum += squares[i];
  }    
  printf("Sum: %e\n",sum);

  return 0;
}

/*
  1. You probably get a `segmentation fault'. Which line causes that? Repair.
  2. You are still getting a segmentation fault. Which line? Can you fix?
     Hint: use `print' on the various entities.
*/
