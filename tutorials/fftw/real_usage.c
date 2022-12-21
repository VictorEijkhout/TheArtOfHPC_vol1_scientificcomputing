#include <stdlib.h>
#include <stdio.h>
#include <rfftw.h>

#ifndef N
#define N 10
#endif

int main() {

  double in[N],out[N];
  fftw_plan plan;
  fftw_r2r_kind kind = FFTW_DHT;
  unsigned flags = 0;

  plan = fftw_plan_r2r_1d(N,in,out, kind, flags );

  //  p = rfftw_create_plan(N, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE);
  
}
