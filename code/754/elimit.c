/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2020
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {
  //answersnippet elimit
  float n=1;
  for (int k=1; k<=10; k++) {
    float one_plus_one_over_n = 1+1./n;
    float e_ish = pow( one_plus_one_over_n, n);
    printf("step %2d one_plus_one_over_n=%12.10f e-ish=%e\n",
	   k,one_plus_one_over_n,e_ish);
    n *=10;
  }
  //answersnippet end
  return 0;
}
