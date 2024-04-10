/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2024
 ****
 **** Programs for hardware exploration
 ****
 **** clock.hpp : timing signatures
 ****
 ****************************************************************/

#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <functional>
#include <string>
#include <tuple>

#include <chrono>
using Clock = std::chrono::high_resolution_clock ;

std::string clock_init();
int compute_microsec_duration( Clock::time_point start_time );

int time_experiment( std::function< void() > experiment );

std::pair<std::string,float> report_time_per_word
    (int microsec_duration,double number_of_accesses,
     std::function< std::string(int) > = [] (int i ) -> std::string { return std::string(""); } );
std::string report_serial_time(int microsec_duration,int nprocs,int=0 );
std::string report_weak_scaling(int microsec_duration,int reference );
std::string report_thread_overhead(int nthreads );

#endif
