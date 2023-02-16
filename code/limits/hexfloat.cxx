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
using std::endl;
using std::scientific;
using std::hexfloat;
using std::defaultfloat;
#include <limits>
#include <cmath>
#include <cfenv>

using floattype = double;

int main() {

  {
    auto x = static_cast<floattype>( 1 );
    cout << "one    " << scientific << x << " = " << hexfloat << x << endl;
  }

  { auto x = static_cast<floattype>( 2 );
    cout << "two    " << scientific << x << " = " << hexfloat << x << endl;
  }
  {
    auto x = static_cast<floattype>( 16 );
    cout << "16     " << scientific << x << " = " << hexfloat << x << endl;
  }    
  {
    auto x = static_cast<floattype>( 10 );
    cout << "10     " << scientific << x << " = " << hexfloat << x << endl;
  }    
  {
    auto x = static_cast<floattype>( 15 );
    cout << "15     " << scientific << x << " = " << hexfloat << x << endl;
  }    
  {
    auto x = static_cast<floattype>( 1 )/16;
    cout << "1/16   " << scientific << x << " = " << hexfloat << x << endl;
  }    
  {
    auto x = static_cast<floattype>( 1 )/16/16/16;
    cout << "1/16^3 " << scientific << x << " = " << hexfloat << x << endl;
  }    

  return 0;
}
