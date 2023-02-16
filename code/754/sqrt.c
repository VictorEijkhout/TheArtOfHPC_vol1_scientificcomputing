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
#include <math.h>

int main() {
  long int nstart = 100000000;
  for (long int n=nstart,nstep=0; ; n+=nstart,nstep++) {
    if (nstep%10000==0)
      printf("At %ld\n",n);
    long int n_maybe = (long int) sqrt( (double)n*(double)n );
    if (n!=n_maybe) {
      printf("not id for n=%ld\n",n);
      break;
    }
  }
  return 0;
}

// At 2305843000100000000
// not id for n=2305843009300000000     
