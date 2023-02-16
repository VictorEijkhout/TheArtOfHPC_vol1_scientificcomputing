/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 **** bits.c : print a number as bit string
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "printbits.c"

int main() {

  // Let's print some bits
  //codesnippet printbits5
  int five = 5;
  printf("Five=%d, in bits: ",five);
  printBits(sizeof(five),&five);
  printf("\n");
  //codesnippet end

  // Multiplication by shift:
  int ten =
    five << 1 // solution
    ;
  printf("Ten=%d, in bits: ",ten);
  printBits(sizeof(ten),&ten);
  printf("\n");

  // Read a number and test odd/even:
  int yours;
  do {
    fscanf(stdin,"%d",&yours);
    if (yours==0) break;
    int lastbit =
      yours & 1 // solution
      ;
    printf("Your number=%d, in bits: ",yours);
    printBits(sizeof(yours),&yours);
    printf(", last bit=%d",lastbit);
    printf("\n");
  } while (1);

  return 0;
}
