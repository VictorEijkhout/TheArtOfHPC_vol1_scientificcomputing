#include <stdlib.h>
#include <stdio.h>
//#include <Accelerate/Accelerate.h>

//snippet scalecf
void dscal_(int*,double*,double*,int*);
//snippet end

#define assert_equal(x,y) ((x)-(y)<1.e-13 && (x)-(y)>-1.e-13)
int main() {

  int n=20, ione=1;
  double *xarray,*yarray, scale=2.;

  //snippet scalecf
  xarray = new double[n]; yarray = new double[n];

  for (int i=0; i<n; i++)
    xarray[i] = 1.;
  dscal_(&n,&scale,xarray,&ione);
  for (int i=0; i<n; i++)
    if (!assert_equal( xarray[i],scale ))
      printf("Error in index %d",i);
  //snippet end

  return 0;
}

