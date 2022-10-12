/****************************************************************
 ****
 **** This program source is part of
 **** Introduction to High-performance Scientific Computing
 **** by Victor Eijkhout
 **** copyright Victor Eijkhout 2011-2021
 ****
 **** c99.c :  C99 array handling
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>

void set_last( int x[],int len,int value ) {
  x[len-1] = value;
}

int main() {

  //codesnippet c99array
  int len;
  scanf("%d",&len);
  int x[len];
  //codesnippet end

  set_last(x,len,3);
  printf("%d\n",x[len-1]);

  return 0;
}
