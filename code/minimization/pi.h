/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2020
 ****
 **** pi.h : headers for pi examples
 ****
 ****************************************************************/

#include <vector>
#include <cassert>

class Point {
private:
  float x,y;
  bool inside;
public:
  Point(float x,float y,bool inside)
    : x(x),y(y),inside(inside) {};
};

float quadratic_cost( std::vector<Point> set,std::vector<float> values) {
  assert(set.size()==values.size());
};
