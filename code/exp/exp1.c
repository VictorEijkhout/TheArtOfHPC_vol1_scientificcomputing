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
#include "math.h"

int main() {
  //answersnippet eseries
  int n=10;
  int p,i;
  float res;
  for (p=1; p<10; p++) {
    float t = (1+1./n);
    res = 1.;
    for (i; i<n; i++)
      res *= t;
    printf("With 10^%d terms: %e\n",p,res);
    n *= 10;
  }
  //answersnippet end
  return 0;
}
