/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** foo.cxx : C++ file for Make tutorial
 ****
 ****************************************************************/

#include <iostream>
using std::cout;

#include "bar.h"

int main()
{
  int a=2;
  cout << bar(a) << '\n';
  return 0;
}
