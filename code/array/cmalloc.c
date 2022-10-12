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

//codesnippet cmallocpass
void set_last( float *x,int len,float value ) {
  x[len-1] = value;
}
//codesnippet end

//codesnippet cmalloc2d
#define INDEX(i,j,m,n) (i)*(n)+(j)
void set_corner( float *array,int m,int n,float v ) {
  array[ INDEX(m-1,n-1,m,n) ] = v;
}
//codesnippet end

int main() {

  int len;
  scanf("%d",&len);

  printf("MALLOC1D\n");
  //codesnippet cmallocpass
  float *x;
  x = (float*) malloc( len*sizeof(float) );
  set_last(x,len,3.14);
  printf("%e\n",x[len-1]);
  //codesnippet end
  printf("malloc1d\n");

  printf("MALLOC2D\n");
  //codesnippet cmalloc2d
  float *y;
  y = (float*) malloc( len*len*sizeof(float) );
  set_corner( y,len,len,5.12 );
  printf("%e\n",y[ INDEX(len-1,len-1,len,len) ]);
  printf("malloc2d\n");
  //codesnippet end

  return 0;
}
