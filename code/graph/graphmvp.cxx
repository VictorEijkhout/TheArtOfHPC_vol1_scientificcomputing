#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <vector>
using std::vector;
#include <functional>
using std::function;

using vectorvalue = int;
const vectorvalue undefined = -1;
using matrixvalue = bool;
const matrixvalue empty = false;
const matrixvalue filled = true;

class Vector {
private:
  vector<vectorvalue> values;
public:
  Vector( int n )
    : values( vector<vectorvalue>(n,undefined) ) {};
  // indexing
  vectorvalue& operator[](int i) { return values[i]; };
  int size() const { return values.size(); };
  const vectorvalue& operator[](int i) const { return values[i]; };
  // operations
  void addin( const Vector& other,function< vectorvalue(vectorvalue,vectorvalue) > plus ) {
    const int N = size();
    for ( int e=0; e<N; e++ )
      values[e] = plus(values[e],other[e] );
  };
  // utility
  bool different( const Vector& other ) const {
    bool result = false; const int n = size();
    for ( int i=0; i<n; i++ )
      result = result || ( values[i]!=other[i] );
    return result;
  };
  Vector& unit(int i) { values.at(i) = 0; return *this; };
  string str() const {
    stringstream ss;
    for ( auto v : values )
      if (v==undefined) ss << " .";
      else ss << " " << v;
    return ss.str();
  };
};

class AdjacencyMatrix {
private:
  vector< vector<matrixvalue> > adjacency;
public:
  AdjacencyMatrix(int n)
    : adjacency( vector<vector<matrixvalue>>( n,vector<matrixvalue>(n,empty) ) ) {
  };
  int size() const { return adjacency.size(); };
  AdjacencyMatrix& diagonal() {
    const int n = size();
    for ( int row=0; row<n; row++ )
      adjacency[row][row] = filled;
    return *this;
  };
  AdjacencyMatrix& circular() {
    const int n = size();
    for ( int row=0; row<n; row++ )
      adjacency[row][ (row+1) % n ] = filled;
    return *this;
  };
  //codesnippet graphmultiply
  Vector leftmultiply
      ( const Vector& left,
	function< vectorvalue( vectorvalue,matrixvalue ) > mult,
	function< vectorvalue( vectorvalue,vectorvalue ) > add
	) const {
    const int n = size();
    Vector result(n);
    for ( int row=0; row<n; row++ ) {
      Vector partial(n);
      for ( int col=0; col<n; col++ )
	partial[col] = mult( left[row],adjacency[row][col] );
      result.addin(partial,add);
    }
    return result;
  };
  //codesnippet end
  string str() const {
    stringstream ss; ss << "\n";
    for ( auto row : adjacency ) {
      for ( auto v : row )
	if (v==empty) ss << " ."; else ss << " x";
      ss << "\n";
    }
    return ss.str();
  };
};
 
int main() {

  cout << "EXAMPLE1\n";
  {
    /*
     * Apply a shift matrix once
     */
    int N = 5;
    auto circular = AdjacencyMatrix(N).circular();
    cout << "Shift matrix:" << circular.str();
    auto unitvector = Vector(N).unit(2);
    cout << "Input : " << unitvector.str() << "\n";
    //codesnippet graphshift
    auto mult =
      [] ( vectorvalue v,matrixvalue m ) -> vectorvalue {
	if (m==empty) return undefined;
	else return v;
      };
    auto add =
      [] ( vectorvalue x,vectorvalue y ) -> vectorvalue {
	if (x==undefined) return y;
	else return x;
      };
    auto shiftedvector = circular.leftmultiply
      ( unitvector,mult,add );
    //codesnippet end
    cout << "Output: " << shiftedvector.str() << "\n";
  }
  cout << "example1\n";

  cout << "EXAMPLE2\n";
  {
    int N = 5;
    auto circular = AdjacencyMatrix(N).circular();
    cout << "Shift matrix:" << circular.str();
    //codesnippet graphpathmultadd
    auto mult =
      [] ( vectorvalue v,matrixvalue m ) -> vectorvalue {
	if (m==empty) return undefined;
	else if (v==undefined) return v;
	else return v+1;
      };
    auto add = 
      [] ( vectorvalue x,vectorvalue y ) -> vectorvalue {
	if (x==undefined) return y;
	else if (y==undefined) return x;
	else // return minimum
	  return ( x<y ? x : y );
      };
    //codesnippet end
    auto distancevector = Vector(N).unit(N/2);
    cout << "Input : " << distancevector.str() << "\n";
    //codesnippet graphdistloop
    for ( int step=0; ; step++ ) {
      auto stepvector = circular.leftmultiply
	( distancevector,mult,add );
      auto olddistances = distancevector;
      distancevector.addin( stepvector,add );
      if (not distancevector.different(olddistances))
	break;
      cout << "step " << step << ": " << distancevector.str() << "\n";
    }
    //codesnippet end
  }
  cout << "example2\n";

  return 0;
}
