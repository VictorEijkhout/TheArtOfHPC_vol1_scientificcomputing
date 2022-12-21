#include <stdlib.h>
#include <stdio.h>

// need to compile with clang
#include <Accelerate/Accelerate.h>

#define assert_equal(x,y) ((x)-(y)<1.e-13 && (x)-(y)>-1.e-13)
int main() {

  int n=20;
  double *xarray,*yarray, scale=2.;

  //snippet scalecb
  xarray = new double[n]; yarray = new double[n];

  for (int i=0; i<n; i++)
    xarray[i] = 1.;
  cblas_dscal(n,scale,xarray,1);
  for (int i=0; i<n; i++)
    if (!assert_equal( xarray[i],scale ))
      printf("Error in index %d",i);
  //snippet end
  printf("Done.\n");

  return 0;
}

