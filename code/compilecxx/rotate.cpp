/****************************************************************
 ****
 **** This program source is part of
 **** Introduction to High-performance Scientific Computing
 **** by Victor Eijkhout
 **** copyright Victor Eijkhout 2011-2020
 ****
 **** rotate.cxx : simple program to play with compiler optimizations
 ****
 ****************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

//codesnippet givensfunx
void rotate(double& x,double& y,double alpha) {
  double x0 = x, y0 = y;
  x = cos(alpha) * x0 - sin(alpha) * y0;
  y = sin(alpha) * x0 + cos(alpha) * y0;
  return;
}
//codesnippet end

#include <chrono>
using namespace std::chrono;
using myclock = steady_clock;

#define NREPS 10000000

int main() {
  
  double x=.5, y=.5, alpha=1.57;
  auto starttime = myclock::now();
  for (int i=0; i<NREPS; i++)
    rotate(x,y,alpha);
  auto endtime = myclock::now();
  auto duration = endtime-starttime;
  auto u_duration = duration_cast<microseconds>(duration);
  printf("Done after %lld usec\n",u_duration.count());

  return 0;
}
