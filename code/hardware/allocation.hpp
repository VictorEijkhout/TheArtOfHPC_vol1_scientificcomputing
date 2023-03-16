/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** Programs for hardware exploration
 ****
 **** allocation.cxx : memory management
 ****
 ****************************************************************/

#ifndef ALLOCATION_HPP
#define ALLOCATION_HPP

#include <iostream>
#include <iomanip>

#include <sstream>
using std::stringstream;

#include <vector>

template <typename R>
class Cache {
private:
  std::vector<R> thecache;
public:
  Cache() {};
  Cache( std::vector<R> c,bool=false );
  Cache( uint64_t cachesize_in_words,bool=false );
  //  Cache( const Cache<R>& );
private:
  void allocate( uint64_t cachesize_in_words,bool=false );
  void check_alignment();
public:
  void set( R v );
  void setrandom( R mx );

  /*
   * indexing
   */
  R &operator[](int idx) { return thecache[idx]; };
  const R &operator[](int idx) const { return thecache[idx]; };
  R& front() { return thecache.front(); };
  const R& front() const { return thecache.front(); };
  R& back() { return thecache.back(); };
  const R& back() const { return thecache.back(); };
  const auto cachedata() const { return thecache; };
  auto& cachedata() { return thecache; };
  R* data() { return thecache.data(); };
  auto size() { return thecache.size(); };
  size_t size_in_bytes() { return size()*sizeof(R); };
  size_t size_in_kibytes() { return size_in_bytes()>>10; };
  R sumstream(int,size_t,size_t=0) const;
  void make_linked_list( size_t length,bool,bool=false );
  R traversal( size_t n_accesses,R res,bool=false ) const;
  void force();
};

// template <typename R>
// Cache<R> allocate_cache( uint64_t cachesize_in_words,bool=false );

#endif
