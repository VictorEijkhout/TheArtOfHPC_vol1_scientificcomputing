/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2020
 ****
 **** power.c : print powers of 2, including as bit string
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "printbits.c"

int main() {

  for (int power=0,two_to_the_n=1; power<32; power++) {
    printf("Two-to-the %2d = ",power);
    printBits(sizeof(two_to_the_n),&two_to_the_n);
    printf("  = %d",two_to_the_n);
    printf("\n");
    // update the two-to-the-n power
    two_to_the_n <<= 1; // solution
  }

  printf("\n");

  return 0;
}
