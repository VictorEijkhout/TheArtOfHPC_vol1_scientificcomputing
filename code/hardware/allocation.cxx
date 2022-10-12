/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2020
 ****
 **** allocation.cxx : general allocation stuff. not used?
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

#include "allocation.hpp"

#include <cstdlib>
#include <new>
void* operator new(std::size_t size ) {
  std::align_val_t align{ static_cast<std::align_val_t>(4096) };
#if defined(_WIN32) || defined(__CYGWIN__)
    auto ptr = _aligned_malloc(size, static_cast<std::size_t>(align));
#else
    void *ptr;
    posix_memalign( &ptr,static_cast<size_t>( align ),size );
    // auto ptr = std::aligned_alloc /*aligned_alloc*/ (static_cast<std::size_t>(align), size);
#endif

    if (!ptr)
        throw std::bad_alloc{};
    return ptr;
}

template <typename R>
Cache<R>::Cache( std::vector<R> c,bool trace ) : thecache(c) {};
template <typename R>
Cache<R>::Cache( uint64_t cachesize_in_words,bool trace )
  : thecache( vector<R>(cachesize_in_words) ) {
  if (trace) {
    auto ptr = data();
    cout << "allocating cache at " << reinterpret_cast<intptr_t>(ptr) << endl;
  }
};

template <typename R>
void Cache<R>::allocate( uint64_t cachesize_in_words,bool trace ) {
  thecache = vector<R>(cachesize_in_words);
  if (trace) {
    auto ptr = data();
    cout << "allocating cache at " << reinterpret_cast<intptr_t>(ptr) << endl;
  }
};

template <typename R>
void Cache<R>::set( R v ) {
  for ( auto &e : thecache )
    e = v;
};

template <typename R>
void Cache<R>::check_alignment( ) {
  void *ptr = data();
  auto address_val = reinterpret_cast<intptr_t>(ptr);
  auto check_address = address_val;
  int bits, ialign;
  for (bits=0,ialign=1;
       (check_address<<bits)==address_val;
       bits+=1,ialign*=2,check_address=(check_address>>1) ) ;
  std::cout << "Ptr: " << ptr
	    << ", align: " << ialign
	    << " (check: addr=" << address_val << "==" << (check_address<<bits) << ")"
	    << '\n';
};

void operator delete(void* ptr, std::size_t size, std::align_val_t align) noexcept {
    std::cout << "delete: " << size << ", align: " 
              << static_cast<std::size_t>(align) 
              << ", ptr : " << ptr << '\n';
#if defined(_WIN32) || defined(__CYGWIN__) 
    _aligned_free(ptr);
#else
    free(ptr);
#endif
}

template <typename R>
Cache<R> allocate_cache( uint64_t cachesize_in_words,bool trace ) {
  vector<R> cache(cachesize_in_words,1.);

  if (trace) {
    stringstream report;
    report << "Cachesize in words: " << setw(9) << cachesize_in_words ;
    report <<         "; in bytes: " << setw(9) << (cachesize_in_words<<3); // bytes;
    cout << report.str() << endl;
  }

  for ( auto &c : cache ) c += 1.2;
  auto return_cache = Cache(cache);
  if (trace) return_cache.check_alignment();
  return return_cache;
};

//codesnippet cachesumstream
template <typename R>
R Cache<R>::sumstream(int repeats,size_t length,size_t byte_offset /* =0 default */ ) const {
  R s{0};
  size_t loc_offset = byte_offset/sizeof(R);
  const R *start_point = thecache.data()+loc_offset;
  for (int r=0; r<repeats; r++)
    for (int w=0; w<length; w++)
      s += *( start_point+w ) * r;
  return s;
};
//codesnippet end

template <typename R>
void Cache<R>::make_linked_list( size_t length ) {
  auto data = thecache.data();
  for (size_t i=0; i<length-1; i++)
    data[i] = i+1;
  data[length-1] = 0;
}

template <typename R>
R Cache<R>::traversal( size_t n_accesses,R res,bool tracing ) const {
  return res;
};
template <>
int Cache<int>::traversal( size_t n_accesses,int res,bool tracing ) const {
  auto data = thecache.data();
  for (size_t i=0; i<n_accesses; i++) {
    res = data[res];
    if (tracing)
      cout << res << " ";
  }
  if (tracing) cout << "\n";
  return res;
};

template <typename R>
void Cache<R>::force() {
  double s{0.}; for ( auto c : thecache ) s += c; if (s<0) std::cout << s;
};

template class Cache<int>;
template class Cache<float>;
template class Cache<double>;
template Cache<int> allocate_cache<int>(uint64_t,bool);
template Cache<float> allocate_cache<float>(uint64_t,bool);
template Cache<double> allocate_cache<double>(uint64_t,bool);
