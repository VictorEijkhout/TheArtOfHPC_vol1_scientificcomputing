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
#include <string>
using std::string;
#include <sstream>
using std::stringstream;

#include "clock.hpp"
#include "allocation.hpp"

#include <vector>
using std::vector;

#include <stdint.h>

int compute_elements_to_write(int associativity,uint64_t cachesize_in_words) {
  int shifts{1};
  while ( (associativity>>shifts) > 0 )
    shifts++;
  int division  = 1<<shifts;
  std::cout << "associativity" << associativity
	    << " gives division " << division << std::endl;
  return cachesize_in_words/division;
};

string generate_runtime_report
( int microsec_duration,int associativity,int n_elements_to_write,int how_many_repeats) {
  stringstream report;
  report << "Associativity " << setw(2) << associativity;
  double number_of_accesses = associativity *
    static_cast<double>(n_elements_to_write) * static_cast<double>(how_many_repeats);
  auto [sreport,freport] = report_time_per_word(microsec_duration,number_of_accesses);
  report << sreport;
  return report.str();
};

template <int ASSOC>
void cache_writing(Cache<double> &cache,int how_many_repeats,int n_elements_to_write) {
    for (int irepeat=0; irepeat<how_many_repeats; irepeat++) {
      if constexpr (ASSOC==1) {
	for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	  cache[iwrite] += 1.1; 
	}
      } else if (ASSOC==2) {
	for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	  cache[iwrite] += cache[iwrite+n_elements_to_write];
	}
      } else if (ASSOC==3) {
	for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	  cache[iwrite] += cache[iwrite+n_elements_to_write]
	    + cache[iwrite+2*n_elements_to_write];
	}
      } else if (ASSOC==4) {
	for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	  cache[iwrite] += cache[iwrite+n_elements_to_write]
	    + cache[iwrite+2*n_elements_to_write]
	    + cache[iwrite+3*n_elements_to_write];
	}
      } else if (ASSOC==5) {
	for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	  cache[iwrite] += cache[iwrite+n_elements_to_write]
	    + cache[iwrite+2*n_elements_to_write]
	    + cache[iwrite+3*n_elements_to_write]
	    + cache[iwrite+4*n_elements_to_write];
	}
      } else if (ASSOC==6) {
	for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	  cache[iwrite] += cache[iwrite+n_elements_to_write]
	    + cache[iwrite+2*n_elements_to_write]
	    + cache[iwrite+3*n_elements_to_write]
	    + cache[iwrite+4*n_elements_to_write]
	    + cache[iwrite+5*n_elements_to_write];
	}
      } else if (ASSOC==7) {
	for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	  cache[iwrite] += cache[iwrite+n_elements_to_write]
	    + cache[iwrite+2*n_elements_to_write]
	    + cache[iwrite+3*n_elements_to_write]
	    + cache[iwrite+4*n_elements_to_write]
	    + cache[iwrite+5*n_elements_to_write]
	    + cache[iwrite+6*n_elements_to_write];
	}
      } else if (ASSOC==8) {
	for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	  cache[iwrite] += cache[iwrite+n_elements_to_write]
	    + cache[iwrite+2*n_elements_to_write]
	    + cache[iwrite+3*n_elements_to_write]
	    + cache[iwrite+4*n_elements_to_write]
	    + cache[iwrite+5*n_elements_to_write]
	    + cache[iwrite+6*n_elements_to_write]
	    + cache[iwrite+7*n_elements_to_write];
	}
      }
    }
}

template<int ASSOC>
void cache_test( Cache<double>& cache, int how_many_repeats) {
    const int n_elements_to_write =
      compute_elements_to_write(ASSOC,cache.size());
    auto start_time = Clock::now();
    cache_writing<ASSOC>(cache,how_many_repeats,n_elements_to_write);
    int microsec_duration = compute_microsec_duration(start_time);
    cache.force();
    string report =
      generate_runtime_report(microsec_duration,ASSOC,n_elements_to_write,how_many_repeats);
    cout << report << endl;
  }

int main() {

  clock_init();

  /*
   * Create cache data
   */
  uint64_t cachesize_in_bytes{ 0xffff };
  auto cachesize_in_words = cachesize_in_bytes/8;
  auto cache = allocate_cache<double>(cachesize_in_words);

  auto how_many_repeats = 100;
  cache_test<1>(cache,how_many_repeats);
  cache_test<2>(cache,how_many_repeats);
  cache_test<3>(cache,how_many_repeats);
  cache_test<4>(cache,how_many_repeats);
  cache_test<5>(cache,how_many_repeats);
  cache_test<6>(cache,how_many_repeats);
  cache_test<7>(cache,how_many_repeats);
  cache_test<8>(cache,how_many_repeats);

#if 0
  // 1
  {
    const int associativity{1};
    const int n_elements_to_write =
      compute_elements_to_write(associativity,cachesize_in_words);
    auto start_time = Clock::now();
    cache_writing<associativity>(cache,how_many_repeats,n_elements_to_write);
    int microsec_duration = compute_microsec_duration(start_time);
    cache.force();
    string report =
      generate_runtime_report(microsec_duration,associativity,n_elements_to_write,how_many_repeats);
    cout << report << endl;
  }

  // 2
  {
    const int associativity{2};
    const int n_elements_to_write =
      compute_elements_to_write(associativity,cachesize_in_words);
    auto start_time = Clock::now();
    cache_writing<associativity>(cache,how_many_repeats,n_elements_to_write);
    int microsec_duration = compute_microsec_duration(start_time);
    cache.force();
    string report =
      generate_runtime_report(microsec_duration,associativity,n_elements_to_write,how_many_repeats);
    cout << report << endl;
  }

  // 3
  {
    const int associativity{3};
    const int n_elements_to_write =
      compute_elements_to_write(associativity,cachesize_in_words);
    auto start_time = Clock::now();
    cache_writing<associativity>(cache,how_many_repeats,n_elements_to_write);
    int microsec_duration = compute_microsec_duration(start_time);
    cache.force();
    string report =
      generate_runtime_report(microsec_duration,associativity,n_elements_to_write,how_many_repeats);
    cout << report << endl;
  }

  // 4
  {
    const int associativity{4};
    const int n_elements_to_write =
      compute_elements_to_write(associativity,cachesize_in_words);
    auto start_time = Clock::now();
    cache_writing<associativity>(cache,how_many_repeats,n_elements_to_write);
    int microsec_duration = compute_microsec_duration(start_time);
    cache.force();
    string report =
      generate_runtime_report(microsec_duration,associativity,n_elements_to_write,how_many_repeats);
    cout << report << endl;
  }

  // 5
  {
    const int associativity{5};
    const int n_elements_to_write =
      compute_elements_to_write(associativity,cachesize_in_words);
    auto start_time = Clock::now();
    cache_writing<associativity>(cache,how_many_repeats,n_elements_to_write);
    int microsec_duration = compute_microsec_duration(start_time);
    cache.force();
    string report =
      generate_runtime_report(microsec_duration,associativity,n_elements_to_write,how_many_repeats);
    cout << report << endl;
  }

  // 6
  {
    const int associativity{6};
    const int n_elements_to_write =
      compute_elements_to_write(associativity,cachesize_in_words);
    auto start_time = Clock::now();
    cache_writing<associativity>(cache,how_many_repeats,n_elements_to_write);
    int microsec_duration = compute_microsec_duration(start_time);
    cache.force();
    string report =
      generate_runtime_report(microsec_duration,associativity,n_elements_to_write,how_many_repeats);
    cout << report << endl;
  }

  // 7
  {
    const int associativity{7};
    const int n_elements_to_write =
      compute_elements_to_write(associativity,cachesize_in_words);
    auto start_time = Clock::now();
    cache_writing<associativity>(cache,how_many_repeats,n_elements_to_write);
    int microsec_duration = compute_microsec_duration(start_time);
    cache.force();
    string report =
      generate_runtime_report(microsec_duration,associativity,n_elements_to_write,how_many_repeats);
    cout << report << endl;
  }

  // 8
  {
    const int associativity{8};
    const int n_elements_to_write =
      compute_elements_to_write(associativity,cachesize_in_words);
    auto start_time = Clock::now();
    cache_writing<associativity>(cache,how_many_repeats,n_elements_to_write);
    int microsec_duration = compute_microsec_duration(start_time);
    cache.force();
    string report =
      generate_runtime_report(microsec_duration,associativity,n_elements_to_write,how_many_repeats);
    cout << report << endl;
  }
#endif

}
