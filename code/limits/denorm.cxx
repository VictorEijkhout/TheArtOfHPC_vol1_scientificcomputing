/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016=2020 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** denorm.cxx : illustration of underflow
 ****
 ****************************************************************/

#include <iostream>
#include <limits>
#include <cmath>
#include <cfenv>

int main() {

  auto tb = std::numeric_limits<double>::tinyness_before;
  std::cout << "Tinyness before: " << std::boolalpha
	    << tb << '\n';
 
  double min_denorm = std::numeric_limits<double>::denorm_min();
  std::cout << "min denorm:  " << std::hexfloat << min_denorm << "\n";

  double multiplier = 2.; //1 + std::numeric_limits<double>::epsilon();
 
  std::feclearexcept(FE_ALL_EXCEPT);
 
  double result = min_denorm*multiplier; // Underflow only if tinyness_before
 
  if(std::fetestexcept(FE_UNDERFLOW))
    std::cout << "Underflow detected\n";
  else
    std::cout << "No underflow detected\n";
 
  std::cout << std::scientific << min_denorm << " x " << multiplier  <<  " = "
	    << result << '\n';
  std::cout << std::hexfloat   << min_denorm << " x " << multiplier  <<  " = "
	    << result << '\n';
}
