/****************************************************************
 ****
 **** This program source is part of
 **** Introduction to High-performance Scientific Computing
 **** by Victor Eijkhout
 **** copyright Victor Eijkhout 2011-2023
 ****
 **** undefined.cxx : program with undefined reference
 ****
 ****************************************************************/

int f(int,int);
int f(int n) { return n; };

int main() {
  f(1,2);
  return 0;
};

 
