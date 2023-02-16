/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 **** vectorlib.h : headers for valuevector support lib
 ****
 ****************************************************************/

//#pragma once
#ifndef VECTORLIB_H
#define VECTORLIB_H

#include <vector>

#include <memory>

/****
 **** Vector
 ****/

class valuevector {
protected:
  std::vector<double> values;
public:
  valuevector( int dim );
  valuevector( std::vector<double> values );
  int size() const ;
  const double &at(int i) const ;
  double &set(int i) ;

  /*
   * Operations
   */
  valuevector rotate(double angle) const ;
  valuevector sigmoid() const ;

  /*
   * Arithmetic
   */
  valuevector operator+( const valuevector& other ) const ;
  valuevector operator-( const valuevector& other ) const ;
  valuevector operator-=( const valuevector& other ) const ;
  valuevector operator-() const ;
  valuevector operator/( const valuevector& other ) const ;
  valuevector invert() const ;
  valuevector operator*( const valuevector& other ) const ;
  valuevector operator*( double other ) const ;
  double inprod( const valuevector& other ) const ;
  valuevector squared() const ;

  /*
   * iterating
   */
private:
  int curloc{0};
public:
  valuevector begin() ;
  valuevector end() ;
  bool operator!=( const valuevector& other ) ;
  void operator++() ;
  double &operator*() ;
};

class unit_valuevector : public valuevector {
public:
  unit_valuevector( int dim,int idim )
    : valuevector(dim) { set(idim) = 1.; };
};

/****
 **** Matrix
 ****/

class matrix {
public:
  virtual valuevector operator*( const valuevector& other ) const = 0;
  virtual valuevector mvp( const valuevector& other ) const  = 0;
  virtual double d2fdxi2(int) const = 0;
};

class diagonal_matrix : public matrix {
private:
  valuevector diagonal;
public:
  diagonal_matrix( const valuevector& diagonal ) ;
  valuevector mvp( const valuevector& other ) const ;
  valuevector operator*( const valuevector& other ) const ;
  double d2fdxi2(int) const ;
};

/****
 **** Layer
 ****/

class layer {
private:
  valuevector bias;
  std::shared_ptr<matrix> weights;
public:
  layer( const valuevector& bias,std::shared_ptr<matrix> weights );
  valuevector multiply( const valuevector& input ) const ;
};

#endif
