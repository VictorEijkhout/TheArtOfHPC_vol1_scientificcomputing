#include <cmath>
#include <optional>
using std::optional;
#include <tuple>
using std::tuple,std::pair,std::make_pair;

#include <fmt/format.h>
using fmt::format,fmt::print;

template< typename T >
optional< pair<T,T> > quadratic( T a, T b, T c ) {
  auto d = b*b - 4 * a * c ;
  if ( d >= static_cast<T>(0) ) {
    T r1,r2;
    if ( b >= static_cast<T>(0)) {
      r1 = (-b - std::sqrt(d)) / (2*a) ;
    } else {
      r1 = (-b + std::sqrt(d)) / (2*a) ;
    }
    r2 = c / (r1 * a) ;
    return make_pair(r2,r1);
  } else return {};
};

template< typename T >
optional< pair<T,T> > textbook(T a, T b, T c) {
  auto d = b*b - 4 * a * c ;
    if ( d >= static_cast<T>(0) ) {
      T r1,r2;
      r1 = (-b - std::sqrt(d)) / (2*a) ;
      r2 = (-b + std::sqrt(d)) / (2*a) ;
      return make_pair(r1,r2);
    } else return {};
};

template< typename T >
T eval(T a, T b, T c, T x) {
  return a*x*x + b*x + c;
}

template< typename T >
T rel(T x,double y) {
  return std::abs( (x-y)/y );
}

using real = double;
int main() {
  for ( int p=3; p<=10; p++ ) {
    real eps = std::pow(10,-p);

    auto [a,b,c] = tuple<real,real,real>( eps, static_cast<real>(-1)-eps*eps, eps ) ;
    print("================\ncoefficients {:.2e} {:.2e} {:.2e}\n",a,b,c) ;
    if (b==static_cast<real>(-1))
      print(".... underflow in b coefficient!\n");

    if ( auto r = textbook(a, b, c) ; r.has_value()) {
      auto [r1, r2] = r.value();
      auto s1 = eval(a,b,c,r1), s2 = eval(a,b,c,r2);
      auto e1 = rel(r1,eps), e2 = rel(r2,static_cast<double>(1)/eps);
      print("textbook zeros {:.3e} {:.3e} evaluate to {: .3e} {: .3e}, error {: .3e} {:.3e}\n",
	    r1,r2,s1,s2,e1,e2 ) ;
    } else print(">>>> could not compute zeros\n");
    if ( auto r = quadratic(a, b, c) ; r.has_value()) {
      auto [r1, r2] = r.value();
      auto s1 = eval(a,b,c,r1), s2 = eval(a,b,c,r2);
      auto e1 = rel(r1,eps), e2 = rel(r2,static_cast<double>(1)/eps);
      print("accurate zeros {:.3e} {:.3e} evaluate to {: .3e} {: .3e}, error {: .3e} {:.3e}\n",
	    r1,r2,s1,s2,e1,e2 ) ;
    } else print(">>>> could not compute zeros\n");
  }
  return 0;
};

