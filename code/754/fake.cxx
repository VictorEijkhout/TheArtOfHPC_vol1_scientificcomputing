/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2022
 ****
 **** https://randomascii.wordpress.com/2012/01/11/tricks-with-the-floating-point-format/
 ****
 ****************************************************************/

#include <iostream>
#include <sstream>
using std::cout,std::stringstream;
#include <string>
using std::string;
#include <tuple>
using std::tuple;

#include <fmt/format.h>
using fmt::format,fmt::print;

union Float_t {
  int32_t i;
  float f;
  // #ifdef _DEBUG
  struct
  {   // Bitfields for exploration. Do not use in production code.
    uint32_t mantissa : 23;
    uint32_t exponent : 8;
    uint32_t sign : 1;
  } bits;
  // #endif
};

class Float {
public:
  Float(float num = 0.0f) { parts.f = num; }

    // Portable extraction of components.
  int IntValue() const { return parts.i; };
  float FloatValue() const { return parts.f; };

  // extract fields by shifting the integer
  bool Negative() const {
    // get 23nd bit
    return (parts.i >> 31) != 0; };
  int32_t RawMantissa() const {
    // extract last 23 bits: 2^24 -1
    return parts.i & ((1 << 23) - 1); };
  int32_t EffectiveMantissa() const {
    return (1<<23) + RawMantissa(); };
  int32_t RawExponent() const {
    // shift the mantissa out, then lose the sign bit
    return (parts.i >> 23) & 0xFF; };
  bool Unnormalized() const { return RawExponent()==0; };
  unsigned short Normalization() {
    if ( Unnormalized() ) return 0; else return 1; };
  tuple<uint32_t,uint32_t,uint32_t> Fields() const {
    return {parts.bits.sign,parts.bits.exponent,parts.bits.mantissa}; };

  string as_string() {
    return fmt::format
      ("{}   {:0>8} x 2^{:0>+3}",
       (Negative() ? "-" : "+" ), RawMantissa(), RawExponent()
       );
  };
  string values_as_string() {
    if ( RawExponent()==255 ) return "InfNan";
    else
      return fmt::format
	("{} {}.{:>08} x 2^{:0>+3}",
	 (Negative() ? "-" : "+" ),
	 Normalization(),RawMantissa(),
	 RawExponent()-126
	 );
  };
private:
  Float_t parts;
};

int main() {

  Float zero{0.0f};
  cout <<  "zero = " << zero.as_string() << "\n";
  cout <<  "zero = " << zero.values_as_string() << "\n";

  Float one{1.0f};
  cout <<  "one  = " << one.as_string() << "\n";
  cout <<  "one  = " << one.values_as_string() << "\n";

  return 0;
}
