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
using std::cout, std::cin, std::endl;
#include <iomanip>
using std::setw, std::fixed, std::setprecision, std::scientific;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;

#include "clock.hpp"
#include "allocation.hpp"

#include "cxxopts.hpp"

#include <stdint.h>

int compute_elements_to_write(int associativity,size_t cachesize_in_words) {
  int shifts{1};
  while ( (associativity>>shifts) > 0 )
    shifts++;
  int division  = 1<<shifts;
  // std::cout << "associativity " << associativity
  // 	    << " gives division " << division << std::endl;
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
  double s{1.};
  for (int irepeat=0; irepeat<how_many_repeats; irepeat++) {
    size_t loc{0};
    if constexpr (ASSOC==1) {
	for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	  auto next_loc = static_cast<size_t>( cache[loc] );
	  cache[loc] += 1.1; 
	  loc = next_loc;
	}
      } else if (ASSOC==2) {
      for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	auto next_loc = static_cast<size_t>( cache[loc] );
	cache[loc] += s * (
			   + cache[loc+1*n_elements_to_write]
			   )
	  / static_cast<double>( n_elements_to_write );
	loc = next_loc;
      }
    } else if (ASSOC==3) {
      for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	auto next_loc = static_cast<size_t>( cache[loc] );
	cache[loc] += s * ( 
			   + cache[loc+1*n_elements_to_write]
			   + cache[loc+2*n_elements_to_write]
			    )
	  / static_cast<double>( n_elements_to_write );
	loc = next_loc;
      }
    } else if (ASSOC==4) {
      for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	auto next_loc = static_cast<size_t>( cache[loc] );
	cache[loc] += s * ( 
			   + cache[loc+1*n_elements_to_write]
			   + cache[loc+2*n_elements_to_write]
			   + cache[loc+3*n_elements_to_write]
			    )
	  / static_cast<double>( n_elements_to_write );
	loc = next_loc;
      }
    } else if (ASSOC==5) {
      for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	auto next_loc = static_cast<size_t>( cache[loc] );
	cache[loc] += s * ( 
			   + cache[loc+1*n_elements_to_write]
			   + cache[loc+2*n_elements_to_write]
			   + cache[loc+3*n_elements_to_write]
			   + cache[loc+4*n_elements_to_write]
			    )
	  / static_cast<double>( n_elements_to_write );
	loc = next_loc;
      }
    } else if (ASSOC==6) {
      for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	auto next_loc = static_cast<size_t>( cache[loc] );
	cache[loc] += s * ( 
			   + cache[loc+1*n_elements_to_write]
			   + cache[loc+2*n_elements_to_write]
			   + cache[loc+3*n_elements_to_write]
			   + cache[loc+4*n_elements_to_write]
			   + cache[loc+5*n_elements_to_write]
			    )
	  / static_cast<double>( n_elements_to_write );
	loc = next_loc;
      }
    } else if (ASSOC==7) {
      for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	auto next_loc = static_cast<size_t>( cache[loc] );
	cache[loc] += s * ( 
			   + cache[loc+1*n_elements_to_write]
			   + cache[loc+2*n_elements_to_write]
			   + cache[loc+3*n_elements_to_write]
			   + cache[loc+4*n_elements_to_write]
			   + cache[loc+5*n_elements_to_write]
			   + cache[loc+6*n_elements_to_write]
			    )
	  / static_cast<double>( n_elements_to_write );
	loc = next_loc;
      }
    } else if (ASSOC==8) {
      for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	auto next_loc = static_cast<size_t>( cache[loc] );
	cache[loc] += s * ( 
			   + cache[loc+1*n_elements_to_write]
			   + cache[loc+2*n_elements_to_write]
			   + cache[loc+3*n_elements_to_write]
			   + cache[loc+4*n_elements_to_write]
			   + cache[loc+5*n_elements_to_write]
			   + cache[loc+6*n_elements_to_write]
			   + cache[loc+7*n_elements_to_write]
			    )
	  / static_cast<double>( n_elements_to_write );
	loc = next_loc;
      }
    } else if (ASSOC==9) {
      for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	auto next_loc = static_cast<size_t>( cache[loc] );
	cache[loc] += s * ( 
			   + cache[loc+1*n_elements_to_write]
			   + cache[loc+2*n_elements_to_write]
			   + cache[loc+3*n_elements_to_write]
			   + cache[loc+4*n_elements_to_write]
			   + cache[loc+5*n_elements_to_write]
			   + cache[loc+6*n_elements_to_write]
			   + cache[loc+7*n_elements_to_write]
			   + cache[loc+8*n_elements_to_write]
			    )
	  / static_cast<double>( n_elements_to_write );
	loc = next_loc;
      }
    } else if (ASSOC==10) {
      for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ ) {
	auto next_loc = static_cast<size_t>( cache[loc] );
	cache[loc] += s * ( 
			   + cache[loc+1*n_elements_to_write]
			   + cache[loc+2*n_elements_to_write]
			   + cache[loc+3*n_elements_to_write]
			   + cache[loc+4*n_elements_to_write]
			   + cache[loc+5*n_elements_to_write]
			   + cache[loc+6*n_elements_to_write]
			   + cache[loc+7*n_elements_to_write]
			   + cache[loc+8*n_elements_to_write]
			   + cache[loc+9*n_elements_to_write]
			    )
	  / static_cast<double>( n_elements_to_write );
	loc = next_loc;
      }
    }
    for (int iwrite=0; iwrite<n_elements_to_write; iwrite++ )
      s += cache[iwrite];
    s /= static_cast<double>( n_elements_to_write );
  }
};

template<int ASSOC>
void cache_test( const size_t write_size_in_words, const int how_many_repeats, const bool random_traversal,bool trace=false) {
  Cache<double> cache(write_size_in_words * ASSOC,trace);
  //  auto cache = allocate_cache<double>(write_size_in_words * ASSOC);
  cache.make_linked_list(write_size_in_words,random_traversal,trace);
  auto cache_size = cache.size();
  cout << "Cache size=" << cache.size_in_kibytes() << " kib; " << ASSOC
       << " streams each write " << write_size_in_words << " elements\n";
  auto start_time = Clock::now();
  cache_writing<ASSOC>(cache,how_many_repeats,write_size_in_words);
  int microsec_duration = compute_microsec_duration(start_time);
  cache.force();
  string report =
    generate_runtime_report(microsec_duration,ASSOC,write_size_in_words,how_many_repeats);
  cout << report << endl;
}

int main(int argc,char **argv) {

  cxxopts::Options options("associativity", "Explore cache associativity");
  options.add_options()
    ("w,words", "write size per stream in words",   cxxopts::value<size_t>())
    ("W,Words", "write size per stream in k words",   cxxopts::value<size_t>())
    ("a,assoc","associativity (0 for 1-8)",cxxopts::value<int>()->default_value("0"))
    ("r,random","random traversal",cxxopts::value<bool>()->default_value("false"))
    ("t,trace","trace output",cxxopts::value<bool>()->default_value("false"))
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    cout << options.help() << endl;
    return 1;
  }

  clock_init();

  /*
   * Create cache data
   */
  size_t writesize_in_words;
  if (result.count("w")>0) 
    writesize_in_words = result["w"].as<size_t>();
  else if (result.count("W")>0) 
    writesize_in_words = result["W"].as<size_t>() << 10;
  else {
    cout << "Need w or W option\n"; throw;
  }
  cout << "Using cache size in words: " << writesize_in_words << '\n';
  bool random_traversal = result["random"].as<bool>();
  if (random_traversal)
    cout << "Random traversal of cache\n";
  else
    cout << "Sequential traversal of cache\n";
  bool trace = result["trace"].as<bool>();

  auto how_many_repeats = 100;
  auto associativity = result["a"].as<int>();
  if (associativity==0) {
    cache_test<1>(writesize_in_words,how_many_repeats,random_traversal,trace);
    cache_test<2>(writesize_in_words,how_many_repeats,random_traversal,trace);
    cache_test<3>(writesize_in_words,how_many_repeats,random_traversal,trace);
    cache_test<4>(writesize_in_words,how_many_repeats,random_traversal,trace);
    cache_test<5>(writesize_in_words,how_many_repeats,random_traversal,trace);
    cache_test<6>(writesize_in_words,how_many_repeats,random_traversal,trace);
    cache_test<7>(writesize_in_words,how_many_repeats,random_traversal,trace);
    cache_test<8>(writesize_in_words,how_many_repeats,random_traversal,trace);
    cache_test<9>(writesize_in_words,how_many_repeats,random_traversal,trace);
    cache_test<10>(writesize_in_words,how_many_repeats,random_traversal,trace);
  } else {
    //    cache_test<associativity>(writesize_in_words,cache,how_many_repeats,random_traversal,trace);
  }

  return 0;

}
