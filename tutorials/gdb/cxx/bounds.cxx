/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to High-Performance Scientific Computing
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-7
 ****
 **** bounds.cxx : array bounds violation
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

int main() {

  double values[20];

  int upper = 20;
  for (int i=0; i<upper; i++) {
    int indx = 10*i+i*i; 
    cout << indx << endl;
    values[indx] = i+2;
  }

  return 0;
}
