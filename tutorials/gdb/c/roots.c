#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//codesnippet gdbrootsc
float root(int n) 
{
  float r;
  r = sqrt(n);
  return r; 
}
 
int main() {
  feenableexcept(FE_INVALID | FE_OVERFLOW); 
  int i;
  float x=0;
  for (i=100; i>-100; i--)
    x += root(i+5);
  printf("sum: %e\n",x);
//codesnippet end
  return 0;
}
