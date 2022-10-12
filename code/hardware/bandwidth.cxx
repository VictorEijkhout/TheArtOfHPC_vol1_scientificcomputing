/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** Programs for hardware exploration
 ****
 **** bandwidth.cxx : saturation by multi-threading
 ****
 ****************************************************************/

#include <iostream>
using std::cout, std::cin, std::endl;
#include <iomanip>
using std::setw;
#include <sstream>
using std::stringstream;

#include <vector>
using std::vector;

#include <thread>
using std::thread;

#include "clock.hpp"
#include "allocation.hpp"

#include "cxxopts.hpp"

int main(int argc,char **argv) {

  // https://github.com/jarro2783/cxxopts
  cxxopts::Options options("bandwidth", "Saturate bandwidth through streaming threads");
  options.add_options()
    ("k,kilobyte", "data size in kbyte",   cxxopts::value<int>()->default_value("32"))
    ("t,threads", "number of threads", cxxopts::value<int>()->default_value("48"))
    ("s,stride","stride in thread count",cxxopts::value<int>()->default_value("4"))
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    cout << options.help() << endl;
    return 1;
  }
  int max_threads{8},thread_stride{2};
  max_threads =  result["t"].as<int>();
  thread_stride = result["s"].as<int>();

  clock_init();

  /*
   * Create cache data
   */
  uint64_t memorysize_in_bytes = 1024*result["k"].as<int>();
  auto memorysize_in_words = memorysize_in_bytes/8;

  stringstream report;
  report 
    << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
    << "                Processing " << memorysize_in_words << " words\n"
    << "                over up to " << max_threads << " threads\n"
    << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
  cout << report.str() << endl;

  auto how_many_repeats = 100000;
  vector<thread> threads; threads.reserve(max_threads);
  vector<double> results;
  int microsec_reference;
  for (int nthreads=1; nthreads<=max_threads; 
       nthreads+=nthreads==1 ? thread_stride-1 : thread_stride ) {

    stringstream report;
    report << "Threads " << setw(2) << nthreads;

    /*
     * Report overhead
     */
    cout << report_thread_overhead(nthreads) << endl;

    /*
     * Timed kernel
     */
    auto memory = allocate_cache<double>( nthreads * memorysize_in_words );
    auto stream_length = memorysize_in_words;
    auto start_time = Clock::now();
    //codesnippet bandwidththreads
    vector<double> results(nthreads,0.);
    for ( int t=0; t<nthreads; t++) {
      auto start_point = t*stream_length;
      threads.push_back
	( thread( [=,&results] () {
	    results[t] = memory.sumstream(how_many_repeats,stream_length,start_point);
	  } ) );
    }
    for ( auto &t : threads )
      t.join();
    //codesnippet end
    int microsec_duration = compute_microsec_duration(start_time);

    /*
     * Prevent compiler optimization
     */
    memory.force();
    threads.clear();

    if (nthreads==1) microsec_reference = microsec_duration;
    report << report_weak_scaling(microsec_duration,microsec_reference);
    cout << report.str() << endl;

  }

  return 0;
}
