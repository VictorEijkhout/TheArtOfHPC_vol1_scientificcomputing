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

#include <vector>
using std::vector;

#include "clock.hpp"
#include "allocation.hpp"

int main() {

  clock_init();

  /*
   * Create cache data
   */
  uint64_t memorysize_in_bytes{ 5000000 };
  auto memorysize_in_words = memorysize_in_bytes/8;
  auto memory = allocate_cache<double>(memorysize_in_words);

  stringstream report;
  report 
    << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
    << "                Processing " << memorysize_in_words << " words\n"
    << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
  cout << report.str() << endl;

  auto how_many_repeats = 1000;
  int microsec_reference;
  for (int distance=1; distance<=0x10000; distance*=8 ) {

    stringstream report;
    report << "Dependence distance " << setw(2) << distance;

    /*
     * Timed kernel
     */
    int microsec_duration;
    auto stream_length = memory.size()-distance - 8 ;
    auto start_time = Clock::now();
    for (int r=0; r<how_many_repeats; r++) {
      for ( int t=0; t<stream_length; t++) {
	//cout << "r=" << r << ", d=" << distance << ", t=" << t << " out of " << memory.size() << endl;
	memory[t+distance] = 1.1 * memory[t] + 1.2;
      }
    }
    microsec_duration = compute_microsec_duration(start_time);

    /*
     * Prevent compiler optimization
     */
    cache_force(memory);

    if (distance==1) microsec_reference = microsec_duration;
    report << report_serial_time(microsec_duration,distance,microsec_reference);
    cout << report.str() << endl;

  }

  return 0;
}
