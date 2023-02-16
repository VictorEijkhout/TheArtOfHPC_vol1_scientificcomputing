/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 **** vectorlib.cxx : valuevector support lib
 ****
 ****************************************************************/

#include <cassert>

#include <cmath>
using std::atan;
using std::sin;
using std::cos;
using std::exp;

#include <memory>
using std::make_shared;
using std::shared_ptr;

#include <iostream>
using std::cout;
using std::endl;

#include <vector>

#include "vectorlib.h"

/****
 **** Vector class
 ****/

/*
 * Constructors
 */
valuevector::valuevector( int dim )
  : values( std::vector<double>(dim,0.) ) {};
valuevector::valuevector( std::vector<double> values )
    : values(values) {};

int valuevector::size() const { return values.size(); };
const double &valuevector::at(int i) const { return values.at(i); };
double &valuevector::set(int i) { return values.at(i); };

/*
 * Operations
 */
valuevector valuevector::rotate(double angle) const {
    auto rotated_coordinate(*this);
    auto new0 = cos(angle)* at(0) - sin(angle) * at(1);
    auto new1 = sin(angle)* at(0) + cos(angle) * at(1);
    rotated_coordinate.set(0) = new0;
    rotated_coordinate.set(1) = new1;
    return rotated_coordinate;
  };
valuevector valuevector::sigmoid() const {
  auto normed(*this);
  // HM. for ( auto &e : normed ) e = 1. / (1.+exp(-e));
  for (int i=0; i<values.size(); i++) {
    auto e = at(i);
    normed.values.at(i) = e = 1. / (1.+exp(-e));
  }
  return normed;
};

/*
 * Arithmetic
 */
valuevector valuevector::operator+( const valuevector& other ) const { auto dim = size();
    assert( dim==other.size() );
    valuevector plus(dim);
    for (int idim=0; idim<dim; idim++)
      plus.set(idim) = values.at(idim)+other.at(idim);
    return plus;
  };
valuevector valuevector::operator-( const valuevector& other ) const { auto dim = size();
    assert( dim==other.size() );
    valuevector minus(dim);
    for (int idim=0; idim<dim; idim++)
      minus.set(idim) = values.at(idim)-other.at(idim);
    return minus;
  };
valuevector valuevector::operator-=( const valuevector& other ) const {
    return (*this)-other; };
valuevector valuevector::operator-() const { auto dim = size();
    valuevector minus(dim);
    for (int idim=0; idim<dim; idim++)
      minus.set(idim) = -values.at(idim);
    return minus;
  };
valuevector valuevector::operator/( const valuevector& other ) const { auto dim = size();
    assert( dim==other.size() );
    valuevector quotient(dim);
    for (int idim=0; idim<dim; idim++)
      quotient.set(idim) = values.at(idim)/other.at(idim);
    return quotient;
  };
valuevector valuevector::invert() const { auto dim = size();
    valuevector quotient(dim);
    for (int idim=0; idim<dim; idim++)
      quotient.set(idim) = 1./values.at(idim);
    return quotient;
  };
valuevector valuevector::operator*( const valuevector& other ) const { auto dim = size();
    assert( dim==other.size() );
    valuevector product(dim);
    for (int idim=0; idim<dim; idim++)
      product.set(idim) = values.at(idim)*other.at(idim);
    return product;
  };
valuevector valuevector::operator*( double other ) const { auto dim = size();
    valuevector product(dim);
    for (int idim=0; idim<dim; idim++)
      product.set(idim) = values.at(idim)*other;
    return product;
  };
double valuevector::inprod( const valuevector& other ) const { auto dim = size();
    assert( dim==other.size() );
    auto value{0.};
    for (int idim=0; idim<dim; idim++)
      value += values.at(idim)*other.at(idim);
    return value;
  };
valuevector valuevector::squared() const { auto dim = size();
    valuevector squareds(dim);
    for (int idim=0; idim<dim; idim++)
      squareds.set(idim) = values.at(idim)*values.at(idim);
    return squareds;
  };

  /*
   * iterating
   */
valuevector valuevector::begin() { curloc = 0; return *this; };
valuevector valuevector::end() { curloc = size(); return *this; }
bool valuevector::operator!=( const valuevector& other ) { return curloc!=other.curloc; };

void valuevector::operator++() { curloc++; };
double &valuevector::operator*() { return values.at(curloc); };

/****
 **** Matrix class
 ****/

diagonal_matrix::diagonal_matrix( const valuevector& diagonal )
  : diagonal(diagonal) {};
valuevector diagonal_matrix::mvp( const valuevector& other ) const {
  return (*this)*other;
};
valuevector diagonal_matrix::operator*( const valuevector& other ) const {
  return diagonal*other;
};
double diagonal_matrix::d2fdxi2(int idim) const {
  return diagonal.at(idim);
};


/****
 **** Layer class
 ****/

layer::layer( const valuevector& bias,shared_ptr<matrix> weights )
  : bias(bias),weights(weights) {};

valuevector layer::multiply( const valuevector& input ) const {
  auto product = weights->mvp(input) - bias;
  return product.sigmoid();
};
