/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to High-Performance Scientific Computing
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-7
 ****
 **** hello.cxx : a hello world program
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
  feenableexcept(FE_INVALID | FE_OVERFLOW); 
  float x,y;

  cout << "Input a number: ";
  cin >> x; cout << endl;
  y = root(x);
  cout << "Root of " << x << " is " << y << endl;
  return 0;
}
