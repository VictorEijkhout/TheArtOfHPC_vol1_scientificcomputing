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

#ifndef N
#define N 100
#endif

int main() {
  double x = 6.28;
  int nterms = N;
  {
    double term = x, sum = term, oldsum = sum;
    for (int i=1; i<=nterms; i+=2) {
      term *= - x*x / (double)((i+1)*(i+2));
      //printf("%d: %e\n",i,term);
      sum += term;
      if (oldsum==sum) {
	printf("At iteration %d the term gets too small\n",i);
	break;
      } else oldsum = sum;
    }
    printf("Sum: %e\n\n",sum);
  }

  {
    double term = x, sum = term;
    for (int i=1; i<=nterms; i+=2) {
      term *= - x*x / (double)((i+1)*(i+2));
      sum += term;
    }
    printf("Sum: %e\n\n",sum);
  }

  {
    double term = x, sum = term;
    double power = x, factorial = 1., factor = 1.;
    for (int i=1; i<=nterms; i+=2) {
      power *= -x*x;
      factorial *= (factor+1)*(factor+2); factor += 2;
      term = power / factorial;
      sum += term;
    }
    printf("Sum: %e\n\n",sum);
  }
  
  return 0;
}
