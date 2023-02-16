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
using std::vector;

#include <CLI/CLI.hpp>

/*
 * included libraries for this application
 */
#include "vectorlib.h"
#include "pi.h"

int main(int argc,char **argv) {

  CLI::App app;
  app.description("\nBuilding a neural net\n");
  int nsamples{10};
  app.add_option("-n",nsamples,"Number of samples to train on",
		 /* list default: */ true);
  CLI11_PARSE(app, argc, argv);

  vector<Point> training_set(nsamples,{0.,0.,true});
  vector<float> computed_values(nsamples);

  cout << "Computed cost: " << quadratic_cost(training_set,computed_values) << "\n";

  return 0;
}
