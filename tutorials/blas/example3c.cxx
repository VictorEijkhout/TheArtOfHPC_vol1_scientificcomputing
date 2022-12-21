#include <stdlib.h>
#include <stdio.h>

// need to compile with clang
#include <Accelerate/Accelerate.h>

#define assert_equal(x,y) ((x)-(y)<1.e-13 && (x)-(y)>-1.e-13)

int main() {

  int m=20,n=2*n;
  double *xarray,*yarray, *matrix, alpha,beta;

  xarray = new double[n]; yarray = new double[m];
  matrix = new double[m*n];

  //snippet mvpc
  for (int j=0; j<n; j++) {
    xarray[j] = 1.;
    for (int i=0; i<m; i++)
      matrix[ i+j*m ] = 1.;
  }

  alpha = 1.; beta = 0.;
  cblas_dgemv(CblasColMajor,
	      CblasNoTrans,m,n, alpha,matrix,m, xarray,1, beta,yarray,1);

  for (int i=0; i<m; i++)
    if (!assert_equal( yarray[i],(double)n ))
      printf("Error in index %d",i);
  //snippet end

  printf("Done.\n");

  return 0;
}

