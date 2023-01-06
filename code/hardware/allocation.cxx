/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** allocation.cxx : general allocation stuff. not used?
 ****
 ****************************************************************/

#include <iostream>
using std::cout, std::cin, std::endl;
#include <iomanip>
using std::setw;

#include <sstream>
using std::stringstream;
#include <iterator>
using std::ostream_iterator;

#include <vector>
using std::vector;

#include <numeric>
#include <random>
#include <algorithm>
#include <cassert>

#include "allocation.hpp"

template <typename R>
Cache<R>::Cache( std::vector<R> c,bool trace ) : thecache(c) {};
template <typename R>
Cache<R>::Cache( uint64_t cachesize_in_words,bool trace ) {
  //  : thecache( vector<R>(cachesize_in_words) ) {
  allocate(cachesize_in_words,trace);
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

// template <typename R>
// Cache<R> allocate_cache( uint64_t cachesize_in_words,bool trace ) {
//   vector<R> cache(cachesize_in_words,1.);

//   if (trace) {
//     stringstream report;
//     report << "Cachesize in words: " << setw(9) << cachesize_in_words ;
//     report <<         "; in bytes: " << setw(9) << (cachesize_in_words<<3); // bytes;
//     cout << report.str() << endl;
//   }

//   for ( auto &c : cache ) c += 1.2;
//   auto return_cache = Cache(cache);
//   if (trace) return_cache.check_alignment();
//   return return_cache;
// };

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
void Cache<R>::make_linked_list( size_t length,bool random_traversal,bool tracing ) {
  if (random_traversal) {
    vector<R> indices(length);
    //codesnippet linkedcache
    std::iota(indices.begin(),indices.end(),0);
    std::random_device r;
    std::mt19937 g(r());
    std::shuffle(indices.begin(), indices.end(), g);
    auto data = thecache.data();
    for (size_t i=0; i<indices.size(); i++)
      data[i] = indices[i];
    //codesnippet end
    if (tracing) {
      cout << "Pointer chasing: ";
      std::copy(indices.begin(), indices.end(),
		ostream_iterator<R>(std::cout, " "));
      cout << "\n";
    }
  } else {
    auto& data = cachedata();
    std::iota(data.begin(),data.end(),1.);
    data.back() = 0.;
    // for (size_t i=0; i<data.size(); i++)
    //   data[i] = (i+1) % length;
  }
  const auto& data = cachedata(); // the vector of doubles
  // for_each( data.begin(),data.end(),
  // 	    [] (auto e) { cout << e << " "; } );
  // cout << '\n';
  auto [minindex,maxindex] = std::minmax_element
    ( data.begin(),data.end() );
  // cout << "min traverse: " << (*minindex)
  //      << ", max traverse: " << (*maxindex)
  //      << " out of 0--" << data.size()-1 << '\n';
  assert( static_cast<size_t>(*minindex)==0 );
  assert( static_cast<size_t>(*maxindex)==data.size()-1 );
}

template <typename R>
R Cache<R>::traversal( size_t n_accesses,R res,bool tracing ) const {
  return res;
};
template <>
int Cache<int>::traversal( size_t n_accesses,int res,bool tracing ) const {
  //codesnippet linkedcachetraverse
  auto data = thecache.data();
  for (size_t i=0; i<n_accesses; i++) {
    res = data[res];
    //codesnippet end
    if (tracing)
      cout << res << " ";
  //codesnippet linkedcachetraverse
  }
  //codesnippet end
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
// template Cache<int> allocate_cache<int>(uint64_t,bool);
// template Cache<float> allocate_cache<float>(uint64_t,bool);
// template Cache<double> allocate_cache<double>(uint64_t,bool);
