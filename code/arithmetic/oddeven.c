/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2020
 ****
 **** oddeven.c : exercise for testing odd/even on an integer, using bit operation
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>

int main() {

  // first read a number
  int i;
  fscanf(stdin,"%d",&i);

  //answersnippet imod2
  int
    i_without_unit = (i>>1)<<1;
  printf("i mod 2: %d\n",i-i_without_unit);

  int
    last_bit_of_i = i&1;
  printf("i mod 2: %d\n",last_bit_of_i);
  //answersnippet end
  
  return 0;
}
