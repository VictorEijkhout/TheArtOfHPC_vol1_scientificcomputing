/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** ellipse.cxx : minimization by steepest descent of a quadratic function
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::fixed;
using std::setprecision;

#include <cmath>
double pi() { return std::atan(1)*4; };
#include <cassert>

#include "cxxopts.hpp"

/*
 * included libraries for this application
 */
#include "vectorlib.h"
#include "minimlib.h"

int main(int argc,char **argv) {

  // CLI::App app;
  // int testrun{0};
  // app.add_option("-t",testrun,"Test run number; zero for all",
  // 		 /* list default: */ true);
  // app.description("\nSteepest descent on quadratic functions\n");
  // CLI11_PARSE(app, argc, argv);

  cxxopts::Options options("ellipse", "Gradient descent on an ellipse");
  options.add_options()
    ("t,testrun", "test run number, zero for all", cxxopts::value<int>()->default_value("0"))
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    cout << options.help() << endl;
    return 1;
  }
  auto testrun = result["t"].as<int>();

  /*
   * Ellipse with axes 1 / 1 and center (0,0)
   */
  if (testrun==1 or testrun==0) {
    try {
      cout << "Evaluate circle" << endl;
      //ellipse circle( {1.,1.},{0.,0.} );
      ellipse circle( valuevector( {1.,1.} ),valuevector( {0.,0.} ) );
      auto should_be_zero = circle.eval( valuevector( { 0.,0. } ) );
      cout << "should be zero: " << should_be_zero << endl;
      cout << endl;
    } catch (...) { cout << "ellipse test failed" << endl; throw;
    }
  }

  /*
   * Ellipse with axes 1 / 1 and center (1,1)
   */
  if (testrun==2 or testrun==0) {
    try {
      cout << "Evaluate shifted circle" << endl;
      ellipse circle( valuevector( {1.,1.} ),valuevector( {1.,1.} ) );
      auto should_be_zero = circle.eval( valuevector( { 1.,1. } ) );
      cout << "should be zero: " << should_be_zero << endl;
      auto should_be_two = circle.eval( valuevector( { 2.,2. } ) );
      cout << "should be two: " << should_be_two << endl;
      cout << endl;
    } catch (...) { cout << "shifted ellipse test failed" << endl; throw;
    }
  }

  /*
   * Compute gradients in circle w/ center (0,0)
   */
  if (testrun==3 or testrun<=0) {
    cout << "Gradient in circle" << endl;
    ellipse circle( valuevector( {1.,1.} ),valuevector( {0.,0.} ) );
    auto should_point_right = circle.grad( valuevector( { 1.,0. } ) );
    cout << "should point right (size 2): "
  	 << should_point_right.at(0) << "," << should_point_right.at(1)
  	 << endl;
    auto should_point_up = circle.grad( valuevector( { 0.,1. } ) );
    cout << "should point up (size 2): "
  	 << should_point_up.at(0) << "," << should_point_up.at(1)
  	 << endl;
    cout << endl;
  }

  /*
   * Compute gradients in circle w/ center (1,1)
   */
  if (testrun==4 or testrun==0) {
    cout << "Gradient in shifted circle" << endl;
    ellipse circle( valuevector( {1.,1.} ),valuevector( {1.,1.} ) );
    auto should_point_right = circle.grad( valuevector( { 2.,1. } ) );
    cout << "should point right (size 2): "
  	 << should_point_right.at(0) << "," << should_point_right.at(1)
  	 << endl;
    auto should_point_up = circle.grad( valuevector( { 1.,2. } ) );
    cout << "should point up (size 2): "
  	 << should_point_up.at(0) << "," << should_point_up.at(1)
  	 << endl;
    cout << endl;
  }

  if (testrun==5 or testrun==0) {
    cout << "Search in a perfect circle" << endl;
    ellipse circle
      ( valuevector( {1.,1.} ),valuevector( {0.,0.} ) );
    valuevector search_point( { 1.,1. } );
    auto value = circle.eval(search_point);
    for (int step=0; step<5 and value>.0001; step++) {
      cout << "Step " << step << " "
           << "(" << search_point.at(0)
           << "," << search_point.at(1) << "); "
           << "value: " << value << endl;
      auto grad = circle.grad(search_point);
      cout << grad.at(0) << "," << grad.at(1) << endl;
      search_point -= grad*.25;
      value = circle.eval(search_point);
    }
    cout << endl;
  }

  if (testrun==6 or testrun==0) {
    cout << "Search in a skinny ellipse" << endl;
    ellipse circle
      ( valuevector( {1.,.1} ),valuevector( {0.,0.} ) );
    valuevector search_point( { 1.,1. } );
    for (int step=0; step<5; step++) {
      auto value = circle.eval(search_point);
      cout << "Step " << step << " "
	   << "(" << search_point.at(0) << "," << search_point.at(1) << "); "
	   << "value: " << value << endl;
      auto grad = circle.grad(search_point);
      auto fraction = .25;
      while ( circle.eval( search_point - grad*fraction ) > value ) {
	fraction /= 2.;
	cout << ".. backtrack to " << fraction << endl;
      }
      search_point -= grad*fraction;
    }
    cout << endl;
  }

  if (testrun==7 or testrun==0) {
    cout << "Optimal stepsize in a perfect circle" << endl;
    cout << "  DescentCircle" << endl;
    //codesnippet descentcircle
    ellipse circle
      ( valuevector( {1.,1.} ),valuevector( {0.,0.} ) );
    valuevector search_point( { 1.,1. } );
    auto value = circle.eval(search_point);

    auto new_point = steepest_descent_step(circle,search_point);

    auto new_value = circle.eval(new_point);
    cout << "Starting point "
	 << "(" << search_point.at(0)
	 << "," << search_point.at(1) << "); "
	 << "with value: " << value << "\n"
	 << "  becomes "
	 << "(" << new_point.at(0)
	 << "," << new_point.at(1) << "); "
	 << "with value: " << new_value << endl;
    //codesnippet end
    cout << "  descentcircle" << endl;
    cout << endl;
  }

  if (testrun==8 or testrun==0) {
    cout << "Optimal stepsize in a skinny ellipse" << endl;
    cout << "  DescentEllipse" << endl;
    //codesnippet descentellipse
    ellipse circle( valuevector( {1.,.1} ),valuevector( {0.,0.} ) );
    valuevector search_point( { 1.,1. } );
    auto value = circle.eval(search_point);
    for (int step=0; step<5 and value>.0001; step++) {

      auto new_point = steepest_descent_step(circle,search_point);

      auto new_value = circle.eval(new_point);
      cout << "Starting point " << fixed
  	 << "(" << setprecision(4) << search_point.at(0)
         << "," << setprecision(4) << search_point.at(1) << "); "
         << "with value: " << value << "\n"
  	 << "  becomes "
  	 << "(" << setprecision(4) << new_point.at(0)
         << "," << setprecision(4) << new_point.at(1) << "); "
  	 << "with value: " << new_value << endl;
      search_point = new_point; value = new_value;
    }
    //codesnippet end
    cout << "  descentellipse" << endl;
    cout << endl;
  }

  if (testrun==9 or testrun==0) {
    cout << "Stochastic descent in a skinny ellipse" << endl;
    ellipse circle( valuevector( {1.,.1} ),valuevector( {0.,0.} ) );
    auto dim = circle.dimension();

    valuevector search_point( { 1.,1. } );
    auto value = circle.eval(search_point);

    for (int step=0; step<5 and value>.00001; step++) {
      for (int idim=0; idim<dim and value>.00001; idim++) {

	auto new_point = stochastic_descent_step(circle,search_point,idim);

	auto new_value = circle.eval(new_point);
	cout << "Step " << step << ", direction " << idim << " "
	     << "point (" << search_point.at(0) << "," << search_point.at(1) << "); "
	     << "with value: " << value
	     << ", becomes "
	     << "(" << new_point.at(0) << "," << new_point.at(1) << "); "
	     << "with value: " << new_value << endl;
	search_point = new_point; value = new_value;
      }
    }
    cout << endl;
  }

  if (testrun==10 or testrun==0) {
    cout << "Stochastic descent in a rotated ellipse" << endl;
    rotated_ellipse circle( valuevector( {1.,.1} ),valuevector( {0.,0.} ), pi()/6. );
    auto dim = circle.dimension();

    valuevector search_point( { 1.,1. } );
    auto value = circle.eval(search_point);

    for (int step=0; step<15 and value>.00001; step++) {
      for (int idim=0; idim<dim and value>.00001; idim++) {

	auto new_point = stochastic_descent_step(circle,search_point,idim,.2);

	auto new_value = circle.eval(new_point);
	cout << "Step " << step << ", direction " << idim << " "
	     << "point (" << search_point.at(0) << "," << search_point.at(1) << "); "
	     << "with value: " << value
	     << ", becomes "
	     << "(" << new_point.at(0) << "," << new_point.at(1) << "); "
	     << "with value: " << new_value << endl;
	search_point = new_point; value = new_value;
      }
    }
    cout << endl;
  }

  return 0;
}
