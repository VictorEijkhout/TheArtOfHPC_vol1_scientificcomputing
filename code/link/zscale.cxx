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
#include <complex.h>

//snippet zscale
extern "C" {
void zscal_(int*,double complex*,double complex*,int*);
}
//snippet end

#define assert_equal(x,y) (creal(x)-creal(y)<1.e-13 && creal(x)-creal(y)>-1.e-13)
int main() {

  int n=20, ione=1;
  //snippet zscale
  complex double *xarray,*yarray, scale=2.;
  xarray = new double complex[n]; yarray = new double complex[n];
  //snippet end
  
  for (int i=0; i<n; i++)
    xarray[i] = 1.;
  //snippet zscale
  zscal_(&n,&scale,xarray,&ione);
  //snippet end

  for (int i=0; i<n; i++)
    if (!assert_equal( xarray[i],scale ))
      printf("Error in index %d",i);
  printf("Done.\n");

  return 0;
}

