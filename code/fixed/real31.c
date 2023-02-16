/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <iomanip>
using std::left;
using std::setw;

auto f(double x) {
  if (2*x<1)
    return 2*x;
  else
    return 2*x-1;
};

int main() {
  double current;
  cin >> current;
  for (int step=0; current!=0.; step++) {
    cout << setw(3) << left << step << ": " << current << endl;
    current = f(current);
  }
  return 0;
}
