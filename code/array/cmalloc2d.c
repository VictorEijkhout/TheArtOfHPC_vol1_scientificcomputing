/****************************************************************
 ****
 **** This program source is part of
 **** Introduction to High-performance Scientific Computing
 **** by Victor Eijkhout
 **** copyright Victor Eijkhout 2011-2021
 ****
 **** cmallod2d : ways of allocating a 2D array
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main() {

  int rows,cols;
  printf("rowsize / columnsize=");
  scanf("%d",&rows);   scanf("%d",&cols);
  assert(rows>=1); assert(cols>=1);
  printf("%d,%d\n",rows,cols);

  //codesnippet cmallocsizenn
  int (*numbers)[cols] = malloc( sizeof(int[rows][cols]) );
  //codesnippet end

  assert( (long)numbers==(long)(numbers[0]) );

  int *first_number = &(numbers[0][0]);
  int len = rows*cols;
  printf("filling with numbers 0--%d\n",len-1);
  for (int num=0; num<len; num++)
    *( first_number+num ) = num;
  //codesnippet cmallocsizenn2
  printf("Check: [r-1][c-1]: %d\n",numbers[rows-1][cols-1]);
  //codesnippet end
  if (len>=2) {
    printf("ROWLEN\n");
    //codesnippet cmallocsizenn3
    long row2row = (long)(numbers[1])-(long)(numbers[0]);
    printf("row length bytes=%ld, ints=%ld\n",row2row,row2row/sizeof(int));
    //codesnippet end
    printf("rowlen\n");
  }

  {
    int numbers[5][6][7];
    int count=0;
    for (int i=0; i<5; i++)
      for (int j=0; j<6; j++)
	for (int k=0; k<7; k++)
	  numbers[i][j][k] = count++;
    printf("[2,2,0]: %d / %d\n",numbers[2][2][0],**( numbers[2]+2 ));
  }
  {
    int (*numbers)[6][7] = malloc( sizeof(int[5][6][7]) );
    int count=0;
    for (int i=0; i<5; i++)
      for (int j=0; j<6; j++)
	for (int k=0; k<7; k++)
	  numbers[i][j][k] = count++;
    printf("[2,2,0]: %d / %d\n",numbers[2][2][0],**( numbers[2]+2 ));
  }


  return 0;
}
