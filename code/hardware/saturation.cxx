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

#include <thread>
using std::thread;

#include "clock.hpp"
#include "allocation.hpp"

using floattype = double;

int main() {

  clock_init();

  /*
   * Create cache data
   */
  const int maxthreads{16};
  uint64_t memorysize_in_bytes{ 500000000 };
  auto memorysize_in_words = memorysize_in_bytes/8;
  auto memory = allocate_cache<floattype>(memorysize_in_words);

  {
    int nthreads{4};
    stringstream report;
    report << "Thread overhead of " << nthreads << " threads";

    /*
     * Measure the overhead of thread spawning
     */
    vector<thread> threads(nthreads);
    int microsec_duration;
    auto start_time = Clock::now();
    for ( int t=0; t<nthreads; t++) {
      threads.at(t) =
	thread
	(
	 [] {}
	 );
    }
    for ( auto &t : threads )
      try {
	t.join();
      } catch (...) {
	std::cerr << "Could not join\n";
      // } catch (const std::__1::system_error& ia) {
      // 	std::cerr << "Invalid argument: " << ia.what() << '\n';
      }
    microsec_duration = compute_microsec_duration(start_time);
    report << report_serial_time(microsec_duration,1,microsec_duration);
    cout << report.str() << endl;
  }


  for (int nthreads=1; nthreads<=maxthreads; nthreads++) {
    const auto stream_length = memorysize_in_words/nthreads;
    stringstream report;
    report << "Running with " << nthreads << " threads"
	   << "; each doing stream length=" << stream_length;
    cout << report.str() << endl;
    report.clear();

    auto how_many_repeats = 10;
    vector<double> results(nthreads,0.);
    int microsec_reference;
    vector<thread> threads(nthreads);

    /*
     * Timed kernel
     */
    int microsec_duration;
    auto start_time = Clock::now();
    for ( int t=0; t<nthreads; t++) {
      auto source_loc = t*stream_length;
      // assert( source_loc+stream_length<=memory.size() );
      double *start_point = memory.data()+source_loc;
      int result_loc = t;
      double *write_point = start_point; // results.data()+result_loc;
      threads.at(t) =
	thread
	(
	 [how_many_repeats,stream_length,start_point] (double *write_point) {
	   for (int r=0; r<how_many_repeats; r++)
	     for (int w=0; w<stream_length; w++) {
	       *write_point += *( start_point+w );
	       *write_point *= r+.5 ;
	     }
	 }, write_point
	 );
    }
    for ( auto &t : threads )
      try {
	t.join();
      } catch (...) {
	std::cerr << "Trouble joining" << '\n';
      }
    microsec_duration = compute_microsec_duration(start_time);

    /*
     * Prevent compiler optimization
     */
    memory.force();

    if (nthreads==1) microsec_reference = microsec_duration;
    report << report_serial_time(microsec_duration,1,microsec_reference);
    cout << report.str() << endl;

  }

  return 0;
}
