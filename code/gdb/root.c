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
#include <math.h>

float root(float n)
{
  float r;
  r = sqrt(n);
  return r; 
}
 
int main() {
  float x=9,y;
  for (int i=0; i<20; i++) {
    y = root(x);
    printf("root: %e\n",y);
    x -= 1.1;
  }

  return 0;
}

/*
  1. observe the NaN
  2. use `break' or `break if' to stop when 
     you are about to take the root of a negative number
  3. use `where' and `frame' to determine the iteration that 
     caused this.
*/
