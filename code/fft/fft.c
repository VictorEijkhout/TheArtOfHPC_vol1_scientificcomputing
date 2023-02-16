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
#include <math.h>
#include <complex.h>

// compute points 0..2pi
void compute_xs(double x[],int n) {
  double pi = 4.*atan(1.0);
  for (int i=0; i<n; i++)
    x[i] = 2*pi*i/(double)n;
}

// compute roots of unity
void compute_exps(double complex exps[],double x[],int n) {
  for (int i=0; i<n; i++) {
    double xi = x[i];
    exps[i] = cos(xi) + sin(xi)*I; // e^{ijx}
    printf("(%f + %f i)\n",creal(exps[i]),cimag(exps[i]));
  }
}

// function values
void compute_fs(double f[],int n,int example) {
  for (int i=0; i<n; i++)
    f[i] = 1.;
}

void compute_fc(double complex coef[],double f[],double complex exps[],int n) {
  for (int i=0; i<n; i++) {
    double complex c = 0. + 0*I;
    for (int j=0; j<n; j++) {
      c += f[j] * conj( exps[(i*j)%(n)] );
    }
    coef[i] = c/n;
  }
}

#ifndef N
#define N 32
#endif

int main() {

  double x[N], f[N];
  double complex exps[N],coef[N],trns[N];

  // compute points 0..2pi
  compute_xs(x,N);
  // compute roots of unity
  compute_exps(exps,x,N);

  // function values
  compute_fs(f,N,0);
  // transformed coefficients
  compute_fc(coef,f,exps,N);
  
  printf("Coefficients:\n");
  for (int i=0; i<N; i++)
    printf("%d: %f + %f i\n",i,creal(coef[i]),cimag(coef[i]));

  return 0;
}
