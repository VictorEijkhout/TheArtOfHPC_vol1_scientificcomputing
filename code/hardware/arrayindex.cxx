/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2020
 ****
 **** Programs for hardware exploration
 ****
 **** cachesize.cxx : measure performance as function of cachesize
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <iomanip>
using std::setw;
using std::fixed;
using std::setprecision;
using std::scientific;
#include <sstream>
using std::stringstream;

#include <chrono>
#include <vector>
using std::vector;

#include "cxxopts.hpp"
#include <stdint.h>

/*
 * includes for the hardware project
 */
#include "clock.hpp"
#include "allocation.hpp"

/*
 * Specific for this code
 */
#ifndef NREPEATS 
#define NREPEATS 1
#endif
#define INDEXf(i,j,k,m,n,o) (i) + ( (j)  + (k) * (o) ) * (n)

using floattype = double;

int main(int argc,char **argv) {

  // https://github.com/jarro2783/cxxopts
  cxxopts::Options options("cachesize", "Detect cache sizes");
  // options.add_options()
  //   ("t,threads", "number of threads", cxxopts::value<int>())
  //   ;
  // auto result = options.parse(argc, argv);

  clock_init();

  int isize=1000,jsize=100,ksize=1000,
    matsize = isize*jsize*ksize;

  /*
   * Loop until you have an accurate enough result
   */
  int microsec_duration;
  {
    vector<floattype> mat(matsize,1);
    /*
     * Timed run
     */
    auto start_time = Clock::now();
    for (int repeat=0; repeat<NREPEATS; repeat++) {
      for (int i=0; i<isize; i++)
	for (int j=0; j<jsize; j++)
	  for (int k=0; k<ksize; k++)
	    mat[ INDEXf(i,j,k,isize,jsize,ksize) ] += 1.; //+ .01*i + .01*j + .01*k;
    }
    microsec_duration = compute_microsec_duration(start_time);
    floattype sum = 0.;
    for_each( mat.begin(),mat.end(),[&sum] (floattype e) { sum += e; } );
    cout << "ijk: " << microsec_duration << " for " << sum << "\n";
  }
  {
    vector<floattype> mat(matsize,1);
    /*
     * Timed run
     */
    auto start_time = Clock::now();
    for (int repeat=0; repeat<NREPEATS; repeat++) {
      for (int k=0; k<ksize; k++)
	for (int j=0; j<jsize; j++)
	  for (int i=0; i<isize; i++)
	    mat[ INDEXf(i,j,k,isize,jsize,ksize) ] += 1.; //+ .01*i + .01*j + .01*k;
    }
    microsec_duration = compute_microsec_duration(start_time);
    floattype sum = 0.;
    for_each( mat.begin(),mat.end(),[&sum] (floattype e) { sum += e; } );
    cout << "kji: " << microsec_duration << " for " << sum << "\n";
  }

  return 0;
}
