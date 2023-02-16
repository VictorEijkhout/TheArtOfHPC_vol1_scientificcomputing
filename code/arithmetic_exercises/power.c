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

void printBits(size_t const size, void const * const ptr)
{
  unsigned char *b = (unsigned char*) ptr;
  unsigned char byte;
  int i, j;

  for (i=size-1;i>=0;i--)
    {
      for (j=7;j>=0;j--)
	{
	  byte = (b[i] >> j) & 1;
	  printf("%u", byte);
	}
    }
  //  puts("");
}


int main() {

  for (int power=0,two_to_the_n=1; power<32; power++) {
    printf("Two-to-the %2d = ",power);
    printBits(sizeof(two_to_the_n),&two_to_the_n);
    printf("  = %d",two_to_the_n);
    printf("\n");
    // update the two-to-the-n power
YOUR CODE HERE
  }

  printf("\n");

  return 0;
}
