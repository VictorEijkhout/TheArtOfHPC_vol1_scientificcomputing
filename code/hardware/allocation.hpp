/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2024
 ****
 **** Programs for hardware exploration
 ****
 **** allocation.cxx : memory management
 ****
 ****************************************************************/

#ifndef ALLOCATION_HPP
#define ALLOCATION_HPP

#include <cstdint> // for uint64_t
#include <functional>
#include <span>
#include <string>

template <typename R>
class Cache {
private:
  // alignas(4096)
  R* _allocation{NULL};
  R* _base_ptr{NULL};
  //! \todo should really be mdspan nstreams x cachesize_in_words
  std::span<R> thecache;
  uint64_t cachesize_in_words{4096}, padded_cachesize_in_words{4096};
  int align_bytes = 64;
  int nstreams{1}; bool _trace{false};
public:
  Cache() = default;
  Cache( uint64_t cachesize_in_words );
  ~Cache();
  auto& align( int bytes=4096 ) { align_bytes = bytes; return *this; };
  auto& trace(bool v=true)      { _trace = v;          return *this; };
  auto& multiplex(int nt=1 )    { nstreams = nt;       return *this; };
  void allocate();
  auto data() { return thecache; }; //! \todo do we need this?
  // for rule-of-three: https://en.cppreference.com/w/cpp/language/rule_of_three
  Cache( const Cache<R>& original );
  Cache& operator=( const Cache<R>& original ) = delete;
private:
  void check_alignment();
public:
  Cache<R> get_stream(int=0);
  float stream_bytes(int stride=1);
  void set( R v );
  void setrandom( R mx );
  void transform_in_place( std::function< void(R&) > f,int stride=1,int nrepeats=1 );
  R& front() { return thecache[0]; };
  R& back()  { return thecache[cachesize_in_words-1]; };

  /*
   * Iterator
   */
  class iter {
  private:
    R* seek{0};
  public:
    using value_type = R; // std::iter_value_t required by std::indirectly_readable <= std::input_iterator <= std::input_range
    iter() = default; // std::default_initializable required by std::semiregular <= std::sentinel_for
    iter(R* s) : seek(s) {};
    R& operator*() const { return *seek; }; // const, required by std::indirectly_readable <= std::input_iterator <= std::input_range
    iter& operator++() { seek++; return *this; };
    iter operator++(int i) { iter tmp(*this); operator++(); return tmp; };
    bool operator==( const iter& other ) const { return seek==other.seek; }; // const, required by std::equality_comparable <= std::sentinel_for
    bool operator<( const iter& other ) const { return seek<other.seek; }; // const also added, not required for an std::input_iterator
    using difference_type = std::ptrdiff_t;
    difference_type operator-( const iter& other ) const { return seek-other.seek; }; // const also added, not required for an std::input_iterator, but needed for OpenMP
  };
  iter begin() { return iter(thecache.data()); };
  iter end() { return iter(thecache.data()+thecache.size()); };

  /*
   * indexing
   */
  R &operator[](int idx) { return thecache[idx]; };
  const R &operator[](int idx) const { return thecache[idx]; };
  auto size() { return cachesize_in_words*nstreams; };
  R sumstream(int,size_t,size_t=0) const;
  void make_linked_list( size_t length,bool,bool=false );
  R traversal( size_t n_accesses,R res,bool=false ) const;
  void force();
};

template <typename R,int A>
R sum_stream( std::span<R> stream );

std::string kib_size( uint64_t s );
std::string human_size( uint64_t s );

#endif
