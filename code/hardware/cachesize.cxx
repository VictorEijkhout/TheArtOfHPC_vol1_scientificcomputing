/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
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
#include "clock.hpp"
#include "allocation.hpp"

#include "cxxopts.hpp"

using inttype = int;

int main(int argc,char **argv) {

  // https://github.com/jarro2783/cxxopts
  cxxopts::Options options("cachesize", "Detect cache sizes");
  options.add_options()
    ("b,bytes","cache size in bytes",cxxopts::value<size_t>())
    ("w,words","cache size in words",cxxopts::value<inttype>())
    ("W,kilowords","cache size in kilo words",cxxopts::value<inttype>())
    ("t,trace","tracing",cxxopts::value<bool>()->default_value("false"))
    ("l,linear","linear traversal",cxxopts::value<bool>()->default_value("false"))
    ("h,help","usage information")
    ;
  //   ("t,threads", "number of threads", cxxopts::value<int>())
  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    cout << options.help() << endl;
    return 1;
  }
  auto tracing = result["t"].as<bool>();
  auto random_traversal = not result["l"].as<bool>();

  // the int type used for the cache, which is also the type for the size
  int cachesize_in_words;
  if (result.count("kilowords")) {
    cachesize_in_words = result["W"].as<inttype>() * 1024;
  } else if (result.count("words")) {
    cachesize_in_words = result["w"].as<inttype>();
  } else if (result.count("bytes")) {
    size_t cachesize_in_bytes = result["b"].as<size_t>();
    cachesize_in_words = cachesize_in_words / sizeof(inttype);
  } else {
    cout << "Need either -b/--bytes or -w/--words option\n";
    return 1;
  }

  clock_init();

  for (int ndiv=0; cachesize_in_words>=2; cachesize_in_words/=2 ) {

    stringstream report;
    report << "Cachesize in words: " << setw(9) << cachesize_in_words << " ";

    /*
     * Create cache data
     */
    auto cache = allocate_cache<inttype>(cachesize_in_words);
    cache.make_linked_list(cachesize_in_words,random_traversal,tracing);

    /*
     * Loop until you have an accurate enough result
     */
    for (int attempt=1,how_many_repeats=10; ; attempt++,how_many_repeats*=2 ) {
      size_t number_of_accesses = how_many_repeats * cachesize_in_words;
      /*
       * Timed kernel
       */
      auto start_time = Clock::now();
      int result{0};
      result = cache.traversal(number_of_accesses,result,tracing);
      auto microsec_duration = compute_microsec_duration(start_time);

      /*
       * Time processing
       */
      if (microsec_duration>10) {
	if (result<0) cout << result << "\n";
	//report << " (at attempt " << setw(4) << attempt << ")" ;
	auto [result_string,nsec_per_word] =
	  report_time_per_word(microsec_duration,number_of_accesses);
	report << result_string;
	auto bandwidth_in_mbytepsec = 
	  ( 1. / nsec_per_word ) * 1.e3 * sizeof(inttype);
	report << " bw (mb/sec): " << bandwidth_in_mbytepsec;
	break;
      }
    } 
    cout << report.str() << endl;
  }

  return 0;
}
