/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to High-Performance Scientific Computing
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-7
 ****
 **** root.cxx : a program with floating point exceptions
 ****
 ****************************************************************/

// this is needed to enable floating point exception catching
#include <fenv.h>

#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::sqrt;

float root(float n)
{
  float r;
  r = sqrt(n);
  return r; 
}
 
int main() {

  // this is needed to enable floating point exception catching
  //  feenableexcept(FE_INVALID | FE_OVERFLOW); 
  
  for (int i=1; i<50; i++) {
    float x,y, xi = i;
    x = 200 + .02*xi*xi*xi - 25*xi;
    y = root(x);
    cout << "Root of " << x << " is " << y << endl;
  }

  return 0;
}
