/****************************************************************
 ****
 **** This program source is part of
 **** Introduction to High-performance Scientific Computing
 **** by Victor Eijkhout
 **** copyright Victor Eijkhout 2011-2021
 ****
 **** cansi.c : ansi C array handling
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>

//codesnippet cansisetstar
void set_pointer( int *array, int loc, int value ) {
  array[loc] = value;
}
//codesnippet end

//codesnippet cansiset1d
void set_last( int array[],int len, int value ) {
  array[len-1] = value;
}
//codesnippet end

//codesnippet cansipass2d
void set_corner( int array[][10],int len, int value ) {
  array[len-1][9] = value;
}
//codesnippet end

int main() {

  printf("SET1D\n");
  //codesnippet cansiset1d
  int x[5];
  set_last(x,5,3);
  printf("%d\n",x[4]);
  //codesnippet end
  printf("set1d\n");

  printf("SETSTAR\n");
//codesnippet cansisetstar
  set_pointer(x,2,1);
  printf("%d\n",x[2]);
//codesnippet end
  printf("setstar\n");

  printf("SET2D\n");
  //codesnippet cansiset2d
  int y[2][2];
  y[0][0] = 1; y[0][1] = 2; y[1][0] = 3; y[1][1] = 4;
  int *yloc = (int*)y;
  for (int i=0; i<4; i++)
    printf("%d ",*(yloc++));
  printf("\n");
  //codesnippet end
  printf("set2d\n");

  printf("PASS2D\n");
  //codesnippet cansipass2d
  int z[8][10];
  set_corner( z,8,12 );
  printf("%d\n",z[7][9]);
  //codesnippet end
  printf("pass2d\n");

  return 0;
}
