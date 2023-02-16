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

  // Let's print some bits
  int five = 5;
  printf("Five=%d, in bits: ",five);
  printBits(sizeof(five),&five);
  printf("\n");

  // Multiplication by shift:
  int ten =
YOUR CODE HERE
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
YOUR CODE HERE
      ;
    printf("Your number=%d, in bits: ",yours);
    printBits(sizeof(yours),&yours);
    printf(", last bit=%d",lastbit);
    printf("\n");
  } while (1);

  return 0;
}
