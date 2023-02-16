/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2020
 ****
 **** expfact.c : evaluating e
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "math.h"

int main() {

  int how_many_terms;
  printf("How many terms?\n");
  scanf("%d",&how_many_terms);

  //answersnippet expfact
  float partial_sum=1., inverse_factorial=1.;
  int last_iteration=0; float last_partial_sum=0.;
  for (int term=1; term<=how_many_terms; term++) {
    inverse_factorial /= (float)(term);
    float old_partial_sum = partial_sum;
    partial_sum += inverse_factorial;
    if (partial_sum==old_partial_sum && last_iteration==0) {
      last_iteration = term; last_partial_sum = partial_sum;
    }
  }
  //answersnippet end
  printf("Computed result from %2d terms: %15.9e\n",how_many_terms,partial_sum);
  if (last_iteration==0)
    printf("  all iterations evaluated\n");
  else
    printf("  last iteration evaluated: %d\n",last_iteration);

  //answersnippet expfactback
  partial_sum = 0.;
  for (int term=how_many_terms; term>=1; term--) {
    partial_sum += inverse_factorial;
    inverse_factorial *= term;
  }
  partial_sum += 1.;
  //answersnippet end
  printf("  recomputed result:           %15.9e\n",partial_sum);
  
  return 0;
}
