/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 **** minimlib.h : headers for minimization functionality
 ****
 ****************************************************************/

//#pragma once
#ifndef MINIMLIB_H
#define MINIMLIB_H

#include <memory>

#include "vectorlib.h"

/*
 * Pure virtual function for objective functions
 */
//codesnippet functiondef
class function {
public:
  virtual double eval( const valuevector& coordinate ) const = 0;
  virtual valuevector grad( const valuevector& coordinate ) const = 0;
  virtual std::shared_ptr<matrix> delta( const valuevector& coordinate ) const = 0;
  virtual int dimension() const = 0;
};
//codesnippet end

/*
 * Quadratic objective functions
 */
class ellipse : public function {
protected:
  valuevector axes,center;
public:
  ellipse( const valuevector& axes,const valuevector& center ) ;
  int dimension() const ;
  double eval( const valuevector& coordinate ) const ;
  valuevector grad( const valuevector& coordinate ) const ;
  std::shared_ptr<matrix> delta( const valuevector& coordinate ) const ;
};

class rotated_ellipse : public ellipse {
private:
  double angle;
public:
  rotated_ellipse( const valuevector& axes,const valuevector& center,double angle ) ;
  double eval( const valuevector& coordinate ) const ;
  valuevector grad( const valuevector& coordinate ) const ;
  std::shared_ptr<matrix> delta( const valuevector& coordinate ) const ;
};

/*
 * Search minimization
 */

valuevector steepest_descent_step
    ( const function&,const valuevector& );
valuevector stochastic_descent_step
    ( const function&,const valuevector&, int, double=1.);

#endif
