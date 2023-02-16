/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2021
 ****
 **** d1.cxx : one-dimensional grid simulation
 ****
 ****************************************************************/

#include <iostream>
#include <sstream>
#include <iomanip>

#include <algorithm>
#include <bitset>
#include <random>

using namespace std;

#include <cassert>
#include <cmath>

#include "cxxopts.hpp"

std::random_device r;
std::default_random_engine generator{ r() };

class Node {
private:
  vector<float> work_per_patch;
  float execute_time{-1.};
public:
  Node( int size,float variance=1.5 )
    : work_per_patch(vector<float>(size,1.)) {
    if (variance<0.) throw(1);
    std::uniform_real_distribution<float> distribution( -variance, +variance );
    for ( auto &p : work_per_patch ) {
      p = exp( distribution(generator) );
      if (p<0.) throw(2);
    }
    sort( work_per_patch.begin(),work_per_patch.end(),greater<>() );
  };
  float execute( int ncores ) {
    if (execute_time<0) {
      vector<float> time(ncores,0.);
      for ( auto w : work_per_patch ) {
	assert(w>0);
	auto m = min_element( time.begin(),time.end() );
	*m += w;
      }
      auto m = max_element( time.begin(),time.end() );
      execute_time = *m;
    }
    return execute_time;
  };
};

class Domain {
private:
  vector<Node> nodes;
public:
  Domain( int nnodes,int patch_per_node,float variance=2. )
    : nodes(vector<Node>(nnodes,Node(patch_per_node,variance))) {};
  // execute the domain, with `c' cores per node
  float execute( int c ) {
    float t{0.};
    auto m = max_element
      ( nodes.begin(),nodes.end(),
	[c] (Node p,Node q) -> bool {
	  return p.execute(c)<q.execute(c); }
	);
    return m->execute(c);
  };
};

int main(int argc,char **argv)
{
  cxxopts::Options options("d1", "Simulate 1D domain");
  options.add_options()
    ("m,mess","use message passing")
    ("n,nodes", "number of nodes",       cxxopts::value<int>()->default_value("10"))
    ("p,points", "points per node",      cxxopts::value<int>()->default_value("32"))
    ("v,variance", "variance in work",   cxxopts::value<float>()->default_value("2.0"))
    ("t,trace", "print trace output")
    ("h,help","usage information")
    ;
  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    cout << options.help() << endl;
    return 1;
  }

  int
    ppnode   = result["p"].as<int>(),
    nodes    = result["n"].as<int>();
  float
    variance = result["v"].as<float>();
  bool mpi = result.count("mess");

  int Npatches = 1000000;
  for (int total_cores=10; total_cores<=Npatches/10; total_cores*=10) {
    cout << "Total cores: " << total_cores << endl;
    for (int nnodes=10; nnodes<=total_cores; nnodes*=10) {
      int ncores_per_node = total_cores/nnodes;
      Domain domain( nnodes,Npatches/nnodes,variance );
      cout << "Execution on "
	   << setw(6) << nnodes << " nodes of "
	   << setw(6) << ncores_per_node << " cores_per_node: "
	   << domain.execute(ncores_per_node)
	   << endl;
    }
  }

  return 0;
}
