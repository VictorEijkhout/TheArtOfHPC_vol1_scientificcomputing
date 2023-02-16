/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2021
 ****
 **** expinv.c : evaluating e^[-1}
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "math.h"

int main() {

  int nx;
  printf("x as integer:\n");
  scanf("%d",&nx);
  float x=nx;

  //answersnippet expinv
  float e_partial_sum = 1., i_partial_sum = 1., this_term=1.;
  int term, pm = -1;
  for ( term=1,pm=-1; ; term++ ) {
    this_term *= x / (float)(term);
    float last_partial  = e_partial_sum;
    e_partial_sum += this_term;
    i_partial_sum += pm * this_term;
    printf("Computed result from %2d terms: e^%d = %15.9e e^-%d = %15.9e\n",
	   term,(int)x,e_partial_sum,(int)x,i_partial_sum);
    if ( fabsf( (last_partial-e_partial_sum)/last_partial )<1.e-5 )
      break;
    pm = -pm; 
  }
  //answersnippet end

  return 0;
}
