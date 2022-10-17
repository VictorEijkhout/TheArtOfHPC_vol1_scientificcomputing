/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** Programs for hardware exploration
 ****
 **** clock.cxx : timing
 ****
 ****************************************************************/

#include "clock.hpp"

#include <iomanip>
using std::setw, std::setprecision, std::fixed, std::scientific;

#include <sstream>
using std::stringstream;

#include <string>
using std::string;

#include <functional>
using std::function;

#include <thread>
using std::thread;

#include <vector>
using std::vector;

string clock_init() {
  auto
    num = Clock::period::num,
    den = Clock::period::den;
  stringstream s;
  s << "clock resolution: " << num << " / " << den
    << " = " << static_cast<double>(num)/static_cast<double>(den);
  return s.str();
};

int compute_microsec_duration( Clock::time_point start_time ) {
  auto duration = Clock::now()-start_time;
  auto microsec_duration =
    std::chrono::duration_cast<std::chrono::microseconds>(duration);
  return microsec_duration.count();
};

#include <functional>
using std::function;

int time_experiment( function< void() > experiment ) {
  auto start_time = Clock::now();
  experiment();
  auto microsec_duration = compute_microsec_duration(start_time);
  return microsec_duration;
};

std::pair<string,float> report_time_per_word
    (int microsec_duration,double number_of_accesses,
     function< string(int) > extra_text
     ) {
  stringstream report;

  report << " ran for " << setw(8) << microsec_duration << " usec"
	 << " on " << scientific << setprecision(2) << number_of_accesses << " accesses";

  float
    nanosec_duration = 1000. * static_cast<float>( microsec_duration ),
    nanosec_per_word = nanosec_duration / number_of_accesses;
  report << "; nsec per access: "
	 << fixed << setprecision(3) << setw(8) << nanosec_per_word;
  return {report.str(),nanosec_per_word};
};

string report_serial_time(int microsec_duration,int nprocs,int reference ) {
  stringstream report;
  float usec = microsec_duration * 1.e-6;
  report << ".. ran for " << setw(8) << setprecision(4) << usec << " usec";
  double
    serial_duration = nprocs * static_cast<double>( microsec_duration );
  report << ", equivalent serial time: " << setw(10) << serial_duration << " usec";
  if (reference>0) {
    int ieff = static_cast<int>( 1000*reference/microsec_duration/nprocs);
    float eff = ieff/10.f;
    report << " (efficiency: " << setw(5) << eff
	   << "% )";
  }
  return report.str();
};

string report_weak_scaling(int microsec_duration,int reference ) {
  stringstream report;
  report << ".. ran for " << setw(8) << microsec_duration << " usec";
  if (reference>0)
    report << " (efficiency: " << static_cast<int>( 100*reference/microsec_duration)
	   << "% )";
  return report.str();
};

string report_thread_overhead(int nthreads ) {
  vector<thread> threads; threads.reserve(nthreads);
  auto start_time = Clock::now();
  for ( int t=0; t<nthreads; t++)
    threads.push_back( thread( [] {} ) );
  for ( auto &t : threads )
    t.join();
  auto microsec_duration = compute_microsec_duration(start_time);
  stringstream report;
  report << "Overhead for " << nthreads << " threads: " 
	 << setw(8) << microsec_duration << " usec";
  return report.str();
};
