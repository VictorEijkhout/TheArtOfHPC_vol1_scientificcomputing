/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** Programs for hardware exploration
 ****
 **** falsesharing-omp.cxx : false sharing with OpenMP
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
    ("r,repeat","how many repeats",cxxopts::value<int>()->default_value("100"))
    ("t,trace", "print trace output")
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    cout << "Usage: falsesharing [ -t ]" << endl;
    return 1;
  } 

  int how_many_repeats{0};
  try { how_many_repeats = result["r"].as<int>(); } catch(...) {}

  bool tracing{false};
  if (result.count("trace")>0)
    tracing = true;

  clock_init();

  int np;
#pragma omp parallel shared(np)
#pragma omp single
  np = omp_get_num_threads();

  /*
   * Create cache data
   */
  uint64_t datasize_in_bytes{ 500000000 };
  auto datasize_in_words = datasize_in_bytes/8;
  Cache<floattype> streaming_data;
  streaming_data.allocate( datasize_in_words );

  const auto stream_length = 9000;
  assert(stream_length<=datasize_in_words/np);
  stringstream report;
  report << "Running with " << np << " threads"
	 << "; each doing stream length=" << stream_length;
  cout << report.str() << endl;

  const int max_spacing{16};
  vector<floattype> results(max_spacing*np,0.);
  int microsec_reference;

  //codesnippet sharedwrite
  for (int spacing : {16,12,8,4,3,2,1,0} ) {
    //codesnippet end

    stringstream report;
    report << "Spacing " << setw(2) << spacing;

    auto start_time = Clock::now();
    float operations{0};
#pragma omp parallel reduction(+:operations)
    {
      //codesnippet sharedwrite
      int iproc = omp_get_thread_num();
      //codesnippet end
      if (iproc>=np/2) goto skip;

      /*
       * where do we read: everyone the same array
       */
      floattype *read_stream = streaming_data.data();

      /*
       * where do we write:
       * the threads are `spacing' apart
       */
      //codesnippet sharedwrite
      floattype *write_addr = results.data() + iproc*spacing;
      //codesnippet end

#ifndef ATOMIC
      //codesnippet sharedwrite
      for (int r=0; r<how_many_repeats; r++) {
	for (int w=0; w<stream_length; w++) {
	  *write_addr += *( read_stream+w );
	}
      }
      //codesnippet end
#else
      for (int r=0; r<how_many_repeats; r++) {
	for (int w=0; w<stream_length; w++) {
#         pragma omp atomic
	  *write_addr += *( read_stream+w );
	}
      }
#endif
      operations += how_many_repeats*stream_length;
    skip: ;
    }
    int microsec_duration
      = compute_microsec_duration(start_time);

    if (spacing==max_spacing) microsec_reference = microsec_duration;
    report << report_serial_time(microsec_duration,1,microsec_reference);
    report << "; operation count: " << operations;
    cout << report.str() << endl;

  }

  return 0;
}
