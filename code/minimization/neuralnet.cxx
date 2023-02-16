/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2020
 ****
 **** neuralnet.cxx : basic of neural net computing
 ****
 ****************************************************************/

#include <cassert>

#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::fixed;
using std::setprecision;

#include <numeric>
using std::accumulate;
using std::inner_product;

#include <vector>

#include <cmath>
using std::atan;
using std::sin;
using std::cos;
constexpr double pi() { return atan(1)*4; };

#include <CLI/CLI.hpp>

/*
 * included libraries for this application
 */
#include "vectorlib.h"

int main(int argc,char **argv) {

  CLI::App app;
  app.description("\nBuilding a neural net\n");
  int testrun{0};
  app.add_option("-t",testrun,"Test run number; zero for all",
		 /* list default: */ true);
  CLI11_PARSE(app, argc, argv);

  if (testrun==1 or testrun<=0) {
    valuevector unnormed(25);
    for (int i=0; i<25; i++)
      unnormed.set(i) = i-11.5;
    auto normed = unnormed.sigmoid();
    auto eprv{-1.};
    for ( auto e : normed ) {
      assert( (e>=0.) and (e<=1.) and (e>=eprv) );
      eprv = e;
    }
    cout << "Sigmoid turns increasing vector into normalized increasing" << endl;
  }

  return 0;
}
