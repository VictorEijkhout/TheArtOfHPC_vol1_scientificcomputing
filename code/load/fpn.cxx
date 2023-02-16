/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** fpn.cxx : illustrating a simple load balancing scheme
 ****
 ****************************************************************/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {

  const int nprocs = 5;
  for (int npoints=1; npoints<4*nprocs; npoints++) {
    vector<int> beginend(nprocs+1);
    for (int p=0; p<=nprocs; p++)
      beginend[p] = p*npoints/nprocs;
    cout << npoints << "/" << nprocs << ": ";
    for (int p=0; p<nprocs; p++)
      cout << beginend[p+1]-beginend[p] << " ";
    cout << "\n";
  }

  return 0;
}
