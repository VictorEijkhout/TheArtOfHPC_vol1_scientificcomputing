/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2020
 ****
 **** printbits.c : utility function for print an int as bit string
 ****
 ****************************************************************/

//codesnippet cprintbits
void printBits(size_t const size, void const * const ptr)
{
  unsigned char *b = (unsigned char*) ptr;
  unsigned char byte;
  int i, j;

  for (i=size-1;i>=0;i--)
    for (j=7;j>=0;j--) {
      byte = (b[i] >> j) & 1;
      printf("%u", byte);
    }
}
//codesnippet end
