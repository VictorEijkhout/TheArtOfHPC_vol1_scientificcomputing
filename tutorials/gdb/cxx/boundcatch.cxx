/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to High-Performance Scientific Computing
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-7
 ****
 **** boundcatch.cxx : catching bounds stuff with exceptions
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

int main() {

  int upper = 20;
  vector<double> values(upper);

  for (int i=0; i<upper; i++) {
    int indx = 10*i+i*i; 
    cout << indx << endl;
    //values[indx] = i+2;
    values.at(indx) = i+2;

  }

  return 0;
}

#if 0
    try {
      values.at(indx) = i+2;
    } catch (...) {
	cout << "Problem setting index " << indx
	     << " at i=" << i << endl;
	throw(1);
    }
#endif
