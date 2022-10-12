/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** Programs for hardware exploration
 ****
 **** denormal.cxx : saturation by multi-threading
 ****
 ****************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <iomanip>
using std::setw;
using std::scientific;
#include <sstream>
using std::stringstream;

#include <limits>
using std::numeric_limits;
#include <vector>
using std::vector;

#include "clock.hpp"
#include "allocation.hpp"

#include "cxxopts.hpp"

using floattype = float;

int main(int argc,char **argv) {

  // https://github.com/jarro2783/cxxopts
  cxxopts::Options options("denormal", "Decrease performance as denormal is reached");
  options.add_options()
    //    ("m,mult","multiplicative constant",   cxxopts::value<floattype>()->default_value(".999"))
    ("r,repeat", "how many repeats",         cxxopts::value<int>()->default_value("350"))
    ("t,trace", "print trace output")
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    cout << options.help() << endl;
    return 1;
  }

  bool trace = ( result.count("trace")>0 );

  int repeats{50};
  if (result.count("repeat"))
    repeats = result["r"].as<int>();

  clock_init();

  /*
   * Create cache data
   */
  uint64_t memorysize_in_bytes{ 5000000 };
  auto memorysize_in_words = memorysize_in_bytes/sizeof(floattype);
  Cache<floattype> memory(memorysize_in_words);

  if (trace) {
    stringstream report;
    report 
      << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
      << "        Processing " << memorysize_in_words << " words\n"
      << "        geometric sequence " << repeats << " terms " << "\n"
      << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    cout << report.str() << endl;
  }

  int microsec_reference{0};

  floattype
    minnormal = numeric_limits<floattype>::min(),
    eps = numeric_limits<floattype>::epsilon();
  cout <<scientific
       << "This float type:\nmin normal=" << minnormal
       << "; eps=" << eps
       << "\n";
  for ( auto startvalue : { static_cast<floattype>(1),
			   numeric_limits<floattype>::min() } ) {
    stringstream report;
    floattype ratio = static_cast<floattype>( .9 );
    report << "geometric progression from " << startvalue
           << " with ratio: " << ratio << "\n";
    /*
     * Timed kernel
     */
    int microsec_duration;
    auto stream_length = memory.size();
    auto start_time = Clock::now();

    //codesnippet computedenormal
    /* init data */
    for ( int t=0; t<stream_length; t++)
      memory[t] = startvalue;
    
    /* repeated scale the array */
    for (int r=0; r<repeats; r++) {
      for ( int t=0; t<stream_length; t++) {
	memory[t] = ratio * memory[t];
      }
      memory.front() = memory.back();
    }
    //codesnippet end
    microsec_duration = compute_microsec_duration(start_time);
    auto m = memory[0];
    report << "  smallest number computed: " << m ;
    if (m==0)
      report << " (flushed to zero)";
    else if (m<numeric_limits<floattype>::min())
      report << " (underflow)";
    report << "\n";

    /*
     * Prevent compiler optimization
     */
    //    memory.force();

    report << "  " << report_time_per_word(microsec_duration,repeats*stream_length);
    cout << report.str() << "\n";

  }

  return 0;
}
