/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2023
 ****
 **** Programs for hardware exploration
 ****
 **** branch.cxx : branch prediction
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
    ("p,probability","probability of test being true",
     cxxopts::value<float>()->default_value(".5f"))
    ("t,trace", "print trace output")
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    cout << options.help() << endl;
    return 1;
  }

  float p = result["p"].as<float>();
  bool trace = ( result.count("trace")>0 );

  clock_init();

  /*
   * Create cache data
   */
  uint64_t memorysize_in_bytes{ 5000000 };
  auto memorysize_in_words = memorysize_in_bytes/sizeof(floattype);
  Cache<floattype> memory(memorysize_in_words);
  memory.setrandom(p);

  stringstream report;
  if (trace) {
    report 
      << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
      << "        Iterate with hit probability: " << p << '\n'
      << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
  }

  int microsec_reference{0};

  /*
   * Timed kernel
   */
  int microsec_duration;
  auto stream_length = memory.size();
  auto start_time = Clock::now();

  /* init data */
  float s{0.f};
  for ( int t=0; t<stream_length; t++)
    if (memory[t]<p)
      s += memory[t];
  memory.front() = memory.back();

  microsec_duration = compute_microsec_duration(start_time);
  if (s<0) report << s; // just to prevent compiler optimization
  auto [s_acc,n_acc ] = report_time_per_word(microsec_duration,stream_length);
  report << "nsec/access: " << n_acc;
  cout << report.str() << "\n";

  return 0;
}
