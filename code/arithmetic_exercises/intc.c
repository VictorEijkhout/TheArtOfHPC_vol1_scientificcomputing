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

  // first read a number
  int i;
  fscanf(stdin,"%d",&i);
  printf("Int %11d : ",i); printBits(sizeof(i),&i); printf("\n");

  // then flip the "sign bit"
  int s;
  s =
YOUR CODE HERE
    ;
  printf("sgn %11d : ",s); printBits(sizeof(s),&s); printf("\n"); 

  // better: flip all bits
  int c;
  c =
YOUR CODE HERE
    ;
  printf("flp %11d : ",c); printBits(sizeof(c),&c); printf("\n"); 

  // then add one; this should be the negative of "i"
  int n;
  n = c+1;
  printf("chk %11d : ",n); printBits(sizeof(n),&n); printf("\n"); 
  
  printf("\n");

  return 0;
}
