/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 **** minimlib.cxx : minimization library
 ****
 ****************************************************************/

#include <cassert>

#include <memory>
using std::make_shared;
using std::shared_ptr;

#include <numeric>
using std::accumulate;
using std::inner_product;

#include "vectorlib.h"
#include "minimlib.h"

/*
 * Ellipse
 */
ellipse::ellipse( const valuevector& axes,const valuevector& center )
  : axes(axes),center(center) {
  assert(axes.size()==center.size());
};
int ellipse::dimension() const { return axes.size(); };
double ellipse::eval( const valuevector& coordinate ) const {
    auto dim = coordinate.size();
    assert(dim==axes.size());
    auto shifted_coordinate = coordinate-center;
    auto scaled_coordinate = shifted_coordinate/axes;
    auto products = scaled_coordinate.squared();
    return accumulate(products.begin(),products.end(),0.);
  };
valuevector ellipse::grad( const valuevector& coordinate ) const {
    auto dim = coordinate.size();
    assert(dim==axes.size());
    auto shifted = coordinate-center;
    auto scaled = shifted/axes;
    auto timestwo = scaled*2.;
    return timestwo;
  };
shared_ptr<matrix> ellipse::delta( const valuevector& coordinate ) const {
    auto diag = axes.invert()*2.;
    return shared_ptr<matrix>( make_shared<diagonal_matrix>(diag) );
  };

/*
 * Rotated ellipse
 */
rotated_ellipse::rotated_ellipse
    ( const valuevector& axes,const valuevector& center,double angle )
    : ellipse(axes,center),angle(angle) {};
double rotated_ellipse::eval( const valuevector& coordinate ) const {
    auto dim = coordinate.size();
    assert(dim==axes.size());
    auto rotated_coordinate = coordinate.rotate(-angle);
    return ellipse::eval(rotated_coordinate);
  };
valuevector rotated_ellipse::grad( const valuevector& coordinate ) const {
    auto dim = coordinate.size();
    assert(dim==axes.size());
    auto rotated_coordinate = coordinate.rotate(-angle);
    auto rotated_gradient = ellipse::grad(rotated_coordinate);
    return rotated_gradient.rotate(angle);
  };
shared_ptr<matrix> rotated_ellipse::delta( const valuevector& coordinate ) const {
    auto diag = axes.invert()*2.;
    return shared_ptr<matrix>( make_shared<diagonal_matrix>(diag) );
};

/*
 * Minimization functions
 */

//codesnippet steepestdescentstep
valuevector steepest_descent_step
    ( const function& objective,const valuevector& point ) {
  auto grad = objective.grad(point);
  auto delta = objective.delta(point);

  auto search_direction( grad );
  auto hf = grad.inprod(search_direction);
  auto hfh = search_direction.inprod( delta->mvp(search_direction) );
  auto tau = - hf / hfh;
  auto new_point = point + ( search_direction * tau );
  return new_point;
};
//codesnippet end

//codesnippet stochasticdescentstep
valuevector stochastic_descent_step
    ( const function& objective,const valuevector& point, int idim,
      double damp) {
  int dim = objective.dimension();
  auto grad = objective.grad(point);
  auto delta = objective.delta(point);

  auto search_direction( unit_valuevector(dim,idim) );
  auto gradfi = grad.at(idim);
  auto hf = gradfi;
  auto hfh = delta->d2fdxi2(idim);
  auto tau = - hf / hfh;
  auto new_point = point + ( search_direction * (tau * damp) );

  return new_point;
};
//codesnippet end

