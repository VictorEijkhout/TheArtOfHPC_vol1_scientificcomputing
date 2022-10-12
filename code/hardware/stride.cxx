/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** Programs for hardware exploration
 ****
 **** stride.cxx : measure nsec / word for different strides, sequential
 ****
 ****************************************************************/

#include <iostream>
using std::cout, std::cin, std::endl;
using std::boolalpha;
#include <sstream>
using std::stringstream;
#include <iomanip>
using std::setw, std::setprecision, std::scientific;

#include <vector>
using std::vector;

#include "clock.hpp"
#include "allocation.hpp"

#include "cxxopts.hpp"
#include "omp.h"

using floattype = double;

int main(int argc,char ** argv) {

  // https://github.com/jarro2783/cxxopts
  cxxopts::Options options("stride", "Decrease performance with increasing stride");
  options.add_options()
    ("k,kilobyte", "data size in kbyte",   cxxopts::value<int>()->default_value("32"))
    ("f,flush","flush cache between passes")
    ("r,repeat", "how many repeats",         cxxopts::value<int>()->default_value("10"))
    ("t,trace", "print trace output")
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    cout << options.help() << endl;
    return 1;
  }

  cout << "Using " << sizeof(floattype) << "-byte words" << endl;
  cout << endl;

  /*
   * Create cache data
   * - cache_kbytes : actual size in kilobytes
   * - arraysize_in_bytes : twice L1 size
   */
  size_t datasize_in_words{0};
  {
    int cache_kbytes{0};
    try { cache_kbytes         = result["k"].as<int>(); } catch(...) {}
    cout << "Using data size of " << cache_kbytes << " kbytes" << endl;
    uint64_t datasize_in_bytes = cache_kbytes<<10;
    datasize_in_words = datasize_in_bytes/sizeof(floattype);
  }

  //auto how_many_repeats = 1000;
  int how_many_repeats{0};
  try { how_many_repeats = result["r"].as<int>(); } catch(...) {}

  bool flush{false};
  if (result.count("flush"))
    flush  = true;

  bool tracing{false};
  if (result.count("trace"))
    tracing = true;

  cout << "Write pass repeated " << how_many_repeats << " times"
       << ", flush cache: " << boolalpha << flush
       << endl;

  /*
   * Single-threaded data
   */
  auto write_data = allocate_cache<floattype>(datasize_in_words,tracing);
  write_data.allocate(datasize_in_words,tracing);
  auto flush_data = allocate_cache<floattype>(datasize_in_words);
  flush_data.allocate(datasize_in_words,false);

  cout << endl;
  clock_init();
  int microsec_reference;
  for (int stride : {1,2,3,4,5,6,7,8} ) {

    stringstream report;
    report << "Stride "    << setw(2) << stride
	   << ", hitting " << setw(6) << datasize_in_words/stride << " elements of the array";

    /*
     * Timed kernel
     */
    int microsec_duration;
    auto start_time = Clock::now();
    float nwrites{0.};
    {
      float nw{0.};
      floattype *write_array = write_data.data();
      floattype *flush_array = flush_data.data();
      for (int irepeat=0; irepeat<how_many_repeats; irepeat++) {
	int location{0};
	for ( ; location<datasize_in_words; location+=stride,nw+=1. ) {
	  //if (stride>1) cout << location << "\n";
	  write_array[location] = (location/2.1)*write_array[location] + 1.2;
	}
	//cout << "last loc: " << location << ", writes: " << nw << "\n";
	if (flush)
	  for ( int location=0; location<datasize_in_words; location+=stride,nw+=1. ) {
	    flush_array[location] = (location/2.1)*flush_array[location] + 1.2;
	  }
      }
      nwrites += nw;
    }
    microsec_duration = compute_microsec_duration(start_time);
    //    cout << microsec_duration << "usec, " << nwrites << " words touched" << endl;

    /*
     * Timing processing
     */
    auto [report_string,nsec_per_word] = report_time_per_word(microsec_duration,nwrites);
    // if (stride==1) microsec_reference = microsec_duration;
    // report << report_serial_time(microsec_duration,nwrites,microsec_reference);
    cout << report_string << endl;

    /*
     * Prevent compiler optimization
     */
    // data.force();
    // for ( auto &c : np_data )
    //   c.force();

  }

  return 0;
}
