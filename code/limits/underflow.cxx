/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016=2020 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** underflow.cxx : illustration of underflow
 **** this example is no-op on most architectures. Try IBM Power?
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
using std::hexfloat;
using std::defaultfloat;
#include <limits>
#include <cmath>
#include <cfenv>

using floattype = double;

int main() {

  auto tb = std::numeric_limits<floattype>::tinyness_before;
  cout << "Tinyness before: " << std::boolalpha
	    << tb << '\n';
 
  auto min_float = std::numeric_limits<floattype>::min();
  auto denorm_max = std::nextafter(min_float, 0);
  cout << "min float : " << std::hexfloat << min_float << "\n";
  cout << "max denorm: " << denorm_max << "\n";
  auto eps = std::numeric_limits<floattype>::epsilon();
  cout << "epsilon   : " << defaultfloat << eps << " = " << hexfloat << eps << "\n";
  auto one = static_cast<floattype>(1);
  auto one_plus_eps = one + eps;
  cout << hexfloat
       << "One " << one << " plus eps " << eps << " = " << one_plus_eps << "\n";
  cout << "1+eps > one : " << (one_plus_eps>one) << "\n";

  std::feclearexcept(FE_ALL_EXCEPT);
 
  auto result = denorm_max*one_plus_eps; // Underflow only if tinyness_before
 
  if(std::fetestexcept(FE_UNDERFLOW))
    cout << "Underflow exception detected\n";
  else
    cout << "No underflow exception detected\n";
 
  cout << std::scientific << denorm_max << " x " << one_plus_eps  <<  " = "
	    << result << '\n';
  cout << std::hexfloat   << denorm_max << " x " << one_plus_eps  <<  " = "
	    << result << '\n';
}
