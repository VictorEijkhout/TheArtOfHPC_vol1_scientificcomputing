/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2020
 ****
 **** bitprint.cxx : utility for printing floats as bit string
 ****
 ****************************************************************/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <bitset>

//codesnippet cppbitprint
void format(const std::string  &s)
{
  // sign bit
  std::cout << s.substr(0,1)  << ' ';
  // exponent
  std::cout << s.substr(1,8);
  // mantissa in groups of 4
  for(int walk=9;walk<32;walk+=4)
    std::cout << ' ' << s.substr(walk,4);
  // newline
  std::cout << "\n";
}
//codesnippet end

void printkey() {
  /*
   * Print key "s eee mmmmm"
   */
  std::stringstream key;
  key << "S"  
      << std::string( 8,'e') 
      << std::string(23,'m');
  format(key.str());
}

int main()
{

  /*
   * Read float,
   * - print hexfloat just to show how uninformative this is
   */
  float d = 0.1;
  std::cin >> d;
  std::cout << "Binary output of " << d << ":\n";
  std::cout << "\nhexfloat:" << std::hexfloat << d << '\n';
  
  /*
   * Print bit pattern:
   * - copy to unsigned int 32 bit
   * - print as bitset
   */
  printkey();
  //codesnippet cppbitprint
  uint32_t    u;
  std::memcpy(&u,&d,sizeof(u));
  std::bitset<32> b{u};
  std::stringstream s;
  s << std::hexfloat << b << '\n';
  format(s.str());
  //codesnippet end

  return 0;
}
