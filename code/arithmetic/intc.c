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

#include "printbits.c"

int main() {

  // first read a number
  int i;
  fscanf(stdin,"%d",&i);
  printf("Int %11d : ",i); printBits(sizeof(i),&i); printf("\n");

  // then flip the "sign bit"
  int s;
  s =
    i ^ (1<<31) // solution
    ;
  printf("sgn %11d : ",s); printBits(sizeof(s),&s); printf("\n"); 

  // better: flip all bits
  int c;
  c =
    i ^ 0xffffffff // solution
    ;
  printf("flp %11d : ",c); printBits(sizeof(c),&c); printf("\n"); 

  // then add one; this should be the negative of "i"
  int n;
  n = c+1;
  printf("chk %11d : ",n); printBits(sizeof(n),&n); printf("\n"); 
  
  printf("\n");

  return 0;
}
