/****************************************************************
 ****************************************************************
 ****
 **** This text file is part of the source of 
 **** `Introduction to High-Performance Scientific Computing'
 **** by Victor Eijkhout, copyright 2012-2021
 ****
 **** Deep Learning Network code 
 **** copyright 2021 Ilknur Mustafazade
 ****
 ****************************************************************
 ****************************************************************/

#ifndef SRC_VECTOR_H
#define SRC_VECTOR_H
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>

class Vector {
public:
    std::vector<float> vals;
    Vector();
    Vector( std::vector<float> vals );
	Vector(int size, int init);
    int size() const;
	int r;
	int c=1;
	void show();
    void add(Vector &v1);
	void set_ax( float a, Vector &x );
    const std::vector<float>& values() const { return vals; };
    float *data() { return vals.data(); };
    const float *data() const { return vals.data(); };
    void zeros();
    void square();
    Vector operator-(); // Unary negate operator
    Vector& operator=(const Vector& m2); // Copy constructor
    Vector operator+(const Vector &m2); // Element-wise addition
    Vector operator*(const Vector &m2); // Hadamard Product Element-wise multiplication
    Vector operator/(const Vector &m2); // Element-wise division
    Vector operator-(const Vector &m2); // Element-wise subtraction
    friend Vector operator-(const float &c, const Vector &m); // for constant
    friend Vector operator*(const float &c, const Vector &m); // for constant-matrix multiplication
    friend Vector operator/(const Vector &m, const float &c); // for matrix-constant division

};

class Categorization {
private:
  std::vector<float> _probabilities;
public:
  Categorization( Vector v )
    : _probabilities(v.values()) {};
  Categorization( std::vector<float> p)
    : _probabilities(p) {};
  Categorization(int n)
    : _probabilities( std::vector<float>(n) ) {};
  Categorization(int n,int i)
    : _probabilities( std::vector<float>(n) ) {
    _probabilities.at(i) = 1.;
  };
  const std::vector<float>& probabilities() const { return _probabilities; };
  int size() const { return _probabilities.size(); };
  void normalize() {
    auto it = std::max_element(_probabilities.begin(), _probabilities.end());
    std::fill(_probabilities.begin(), _probabilities.end(), 0);
    *it = 1;
  };
  bool close_enough( const Categorization& approx ) const {
    return close_enough( approx.probabilities() );
  };
  bool close_enough( const std::vector<float>& approx ) const {
    assert( size()==approx.size() );
    //return _probabilities==approx;
    bool close{true};
    for ( int i=0; i<size(); i++) {
      close = close and 
	( ( _probabilities.at(i)==approx.at(i) )
	  or ( approx.at(i)==0. and ( std::abs(_probabilities.at(i))<1.e-5 ) )
	  or ( std::abs( (_probabilities.at(i)-approx.at(i))/approx.at(i) )<1.e-5 )
	  );
    }
    return close;
  };
};
  
#endif //SRC_VECTOR_H
