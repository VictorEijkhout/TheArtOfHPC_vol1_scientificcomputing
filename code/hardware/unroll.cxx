/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** Programs for hardware exploration
 ****
 **** unroll.cxx : saturation by multi-threading
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

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "clock.hpp"
#include "allocation.hpp"

#include "cxxopts.hpp"

int main(int argc,char **argv) {

  // https://github.com/jarro2783/cxxopts
  cxxopts::Options options("bandwidth", "Saturate bandwidth through streaming threads");
  options.add_options()
    ("k,kilobyte", "data size in kbyte",   cxxopts::value<int>()->default_value("128"))
    ("m,model", "fp model for intel", cxxopts::value<string>()->default_value("unknown"))
    ("u,unroll", "max unroll factor", cxxopts::value<int>()->default_value("1"))
    ("r,repeat", "repeats", cxxopts::value<int>()->default_value("100"))
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    cout << options.help() << endl;
    return 1;
  }
  int unroll_max = result["u"].as<int>();
  int repeats = result["r"].as<int>();
  auto model = result["m"].as<string>();
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
    // << "                unroll by  " << unroll_max << " \n"
    << "                using memory model: " << model << "\n"
    << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
  cout << report.str() << endl;

  auto how_many_repeats = 100000;
  vector<double> results;
  int microsec_reference;
  for (int unroll : {1,2,4,8} ) {

    stringstream report;
    report << "Unroll " << setw(2) << unroll;
    bool fail{false};

    /*
     * Timed kernel
     */
    auto memory = allocate_cache<double>( 2 * memorysize_in_words );
    auto stream_length = memorysize_in_words;
    auto a_stream = memory.data(), b_stream = memory.data()+memorysize_in_words;
    auto iterations = memorysize_in_words/unroll;
    double s{0.};
    auto start_time = Clock::now();
    for (int r=0; r<repeats; r++) {
      switch (unroll) {
      case 1 :
	for (int i=0; i<iterations; i++) {
	  s += a_stream[i]*b_stream[i];
	}
	break;
      case 2 : {
	double s0,s1;
	for (int i=0; i<iterations; i+=unroll) {
	  s0 += a_stream[unroll*i+0]*b_stream[unroll*i+0];
	  s1 += a_stream[unroll*i+1]*b_stream[unroll*i+1];
	}
	s += s1+2;
      }
	break;
      case 4 : {
	double s0,s1,s2,s3;
	for (int i=0; i<iterations; i+=unroll) {
	  s0 += a_stream[unroll*i+0]*b_stream[unroll*i+0];
	  s1 += a_stream[unroll*i+1]*b_stream[unroll*i+1];
	  s2 += a_stream[unroll*i+2]*b_stream[unroll*i+2];
	  s3 += a_stream[unroll*i+3]*b_stream[unroll*i+3];
	}
	s += s0+s1+s2+s3;
      }
	break;
      default: cout << "unroll factor " << unroll << " not implemented\n";
	fail = true;
      }
      if (fail) break;
    }
    if (fail) continue;
    int microsec_duration = compute_microsec_duration(start_time);
    if (s<0) cout << s;

    /*
     * Prevent compiler optimization
     */
    memory.force();

    if (unroll==1) microsec_reference = microsec_duration;
    report << report_weak_scaling(microsec_duration,microsec_reference);
    cout << report.str() << endl;

  }

  return 0;
}
