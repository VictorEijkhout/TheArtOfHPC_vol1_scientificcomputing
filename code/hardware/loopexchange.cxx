/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** copyright 2010-2020
 ****
 **** Programs for hardware exploration
 ****
 **** loopexchange.cxx : demonstrate compiler resolution of dependence
 ****
 **** UNDER DEVELOPMENT
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::boolalpha;
#include <sstream>
using std::stringstream;
#include <iomanip>
using std::setw;
using std::setprecision;
using std::scientific;

#include <vector>
using std::vector;

#include "clock.hpp"
#include "allocation.hpp"

#include "cxxopts.hpp"
#include "omp.h"

using floattype = double;

#ifndef LEVELS
#define LEVELS 100
#endif
#ifndef KSIZE
#define KSIZE 1000
#endif

void level_recur( floattype write_data[KSIZE][LEVELS],int levels,int datasize_in_words,float *nw);

int main(int argc,char ** argv) {

  // https://github.com/jarro2783/cxxopts
  cxxopts::Options options("stride", "Decrease performance with increasing stride");
  options.add_options()
    ("k,kilobyte", "data size in kbyte",   cxxopts::value<int>()->default_value("32"))
    //    ("f,flush","flush cache between passes")
    ("l,levels","number of levels",        cxxopts::value<int>()->default_value("100"))
    ("r,repeat", "how many repeats",         cxxopts::value<int>()->default_value("10"))
    ("t,trace", "print trace output")
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    cout << options.help() << endl;
    return 1;
  }

  int np;
#pragma omp parallel shared(np)
#pragma omp single
  np = omp_get_num_threads();

  cout << "Using " << np << " cores, "
       << sizeof(floattype) << "-byte words"
       << endl;

  /*
   * Create cache data
   * - cache_kbytes : actual size in kilobytes
   * - arraysize_in_bytes : twice L1 size
   */
  size_t datasize_in_words{-1};
  {
    int cache_kbytes{KSIZE};
    // try { cache_kbytes         = result["k"].as<int>(); } catch(...) {}
    cout << "Using data size of " << cache_kbytes << " kbytes" << endl;
    uint64_t datasize_in_bytes = cache_kbytes<<10;
    datasize_in_words = datasize_in_bytes/sizeof(floattype);
  }
  int levels = LEVELS; // result["l"].as<int>();
  cout << "Number of levels: " << levels << endl;

  int how_many_repeats{0};
  try { how_many_repeats = result["r"].as<int>(); } catch(...) {}

  bool flush{false};
  if (result.count("flush"))
    flush  = true;

  bool tracing{false};
  if (result.count("trace"))
    tracing = true;

  cout << "Write pass repeated " << how_many_repeats << " times"
    //       << ", flush cache: " << boolalpha << flush
       << endl;

  /*
   * Multi-threaded data
   */
  // vector< Cache<floattype> > write_data( np );
  // for ( auto &c : write_data )
  //   c.allocate(levels*datasize_in_words,tracing);
  // vector< Cache<floattype> > flush_data( np );
  // for ( auto &c : flush_data )
  //   c.allocate(levels*datasize_in_words,false);
  floattype write_array[KSIZE][LEVELS][np];

  cout << endl;
  clock_init();
  int microsec_reference;
  for (int stride : {1,2,3,4,5,6,7,8} ) {

    stringstream report;
    report << "Stride " << setw(2) << stride
	   << ", hitting " << setw(6) << datasize_in_words/stride << " elements";

    /*
     * Timed kernel
     */
    int microsec_duration;
    auto start_time = Clock::now();
    float nwrites{0.};
#pragma omp parallel shared(nwrites,write_array)
    {
      float nw{0.};
      int iproc = omp_get_thread_num();
      // floattype *write_array = write_data.at(iproc).data();
      // floattype *flush_array = flush_data.at(iproc).data();
      for (int irepeat=0; irepeat<how_many_repeats; irepeat++) {
	level_recur( &( write_array[0][0][iproc] ),levels,datasize_in_words,&nw );
      }
      if (iproc==0)
	nwrites += nw;
    }
    // end of omp parallel region
    microsec_duration = compute_microsec_duration(start_time);

    /*
     * Timing processing
     */
    report << report_time_per_word(microsec_duration,nwrites);
    // if (stride==1) microsec_reference = microsec_duration;
    // report << report_serial_time(microsec_duration,nwrites,microsec_reference);
    cout << report.str() << endl;

    /*
     * Prevent compiler optimization
     */
    // data.force();
    // for ( auto &c : np_data )
    //   c.force();

  }

  return 0;
}

void level_recur( floattype write_data[KSIZE][LEVELS],int levels,int datasize_in_words,float *nw) {
  for ( int level=1; level<levels; level++) {
    for ( int location=0; location<datasize_in_words; location+=stride,nw+=1. ) {
      write_array[location] = (location/2.1)*write_array[location] + 1.2;
    }
  }
}
