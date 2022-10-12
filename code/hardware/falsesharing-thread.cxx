/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2020
 ****
 **** Programs for hardware exploration
 ****
 **** bandwidth.cxx : saturation by multi-threading
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <iomanip>
using std::setw;
#include <sstream>
using std::stringstream;

#include <thread>
using std::thread;

#include <vector>
using std::vector;

#include "cassert"

#include "clock.hpp"
#include "allocation.hpp"

#include "cxxopts.hpp"
#include "omp.h"

using floattype = double;

int main(int argc,char **argv) {

  // https://github.com/jarro2783/cxxopts
  cxxopts::Options options("stride", "Decrease performance with increasing stride");
  options.add_options()
    ("t,trace", "print trace output")
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    cout << "Usage: falsesharing [ -t ]" << endl;
    return 1;
  } 
  bool tracing{false};
  if (result.count("trace")>0)
    tracing = true;

  stringstream report;
  clock_init();

  int np;
#pragma omp parallel shared(np)
#pragma omp master
  np = omp_get_num_threads();
  report << "Running with " << np << " threads";

  /*
   * Create cache data
   */
  uint64_t datasize_in_bytes{ 500000000 };
  auto datasize_in_words = datasize_in_bytes/8;
  Cache<floattype> streaming_data;
  streaming_data.allocate( datasize_in_words );
  streaming_data.set(1.);

  const auto stream_length = 100000;
  assert(stream_length<=datasize_in_words/np);
  report << "; each doing stream length=" << stream_length;
  cout << report.str() << endl;

  const auto how_many_repeats = 100000;
  const int max_spacing{16};
  vector<floattype> results(max_spacing*np,0.);
  int microsec_reference;
  float operations{0};

  auto stream_writer = 
    [=] (floattype *read_stream,floattype *write_addr) {
    for (int r=0; r<how_many_repeats; r++) {
      for (int w=0; w<stream_length; w++) {
	*write_addr += *( read_stream+w );
      }
    }
  };

  /*
   * Compute serial reference time
   */
  {
    floattype *read_stream = streaming_data.data();
    floattype *write_addr = results.data();
    auto start_time = Clock::now();
    stream_writer( read_stream,write_addr );
    int microsec_duration
      = compute_microsec_duration(start_time);
    auto operations = static_cast<floattype>(how_many_repeats)*stream_length;
    microsec_reference = microsec_duration;
    stringstream report;
    report << "serial write took " << microsec_reference << " usec";
    report << "; operation count: " << operations;
    cout << report.str() << endl;
  }

  for (int spacing : {16,12,8,4,3,2,1} ) {

    stringstream report;
    report << "P=" << np;
    report << "; spacing " << setw(2) << spacing;

    /*
     * To avoid bandwidth considerations,
     * everyone reads the same stream
     */
    floattype *read_stream = streaming_data.data();

    /****
     **** Spawn all threads
     ****/
    auto start_time = Clock::now();
    vector<thread> threads(np);
    for (int iproc=0; iproc<np; iproc++) {
      /*
       * Every thread has a unit accumulator; 
       * accumulators are spaced `spacing' apart
       */
      floattype *write_addr = results.data() + iproc*spacing;
      *write_addr = static_cast<floattype>(0);
      /*
       * Spawn thread
       */
      threads.at(iproc) =
	thread( /* function: */ stream_writer, /* arguments: */ read_stream,write_addr );
    }
    /*
     * Wait till all threads done
     */
    for ( auto &t : threads )
      t.join();

    /****
     **** Timing and analysis
     ****/
    int microsec_duration
      = compute_microsec_duration(start_time);

    /*
     * Checksum should be one
     */
    floattype checksum{0};
    if (spacing==0)
      checksum = results.at(0);
    else {
      for (int iproc=0; iproc<np; iproc++)
	checksum += results.at(iproc*spacing);
    }
    report << "; check="
	   << checksum/ ( static_cast<floattype>(how_many_repeats)*stream_length*np );
    report << "; runtime=" << microsec_duration;
    report << "; ratio par/seq=" 
	   << setw(3) << static_cast<float>(microsec_duration)/microsec_reference;
    cout << report.str() << endl;

  }

  return 0;
}
