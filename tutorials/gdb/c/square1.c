#include <stdlib.h>
#include <stdio.h>
//codesnippet gdbsquare1c
int main(int argc,char **argv) {
  int nmax,i;
  float *squares,sum;

  fscanf(stdin,"%d",&nmax);
  squares = (float*) malloc(nmax*sizeof(float));
  for (i=1; i<=nmax; i++) {
    squares[i] = 1./(i*i);
    sum += squares[i];
  }    
  printf("Sum: %e\n",sum);
//codesnippet end

  return 0;
}
