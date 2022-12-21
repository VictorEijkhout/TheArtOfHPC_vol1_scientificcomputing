#include <iostream>
using namespace std;

#include "cxxopts.hpp"

#include <string>
#include <vector>

#include "cxxopts.hpp"

int main(int argc,char **argv) {

  cxxopts::Options options
    ("cxxopts", "Commandline options demo");
  options.add_options()
    ("h,help","usage information")
    ;
  options.add_options()
    ("n,ntimes","number of times",
     cxxopts::value<int>()->default_value("37")
     )
    ;
  options.add_options()
    ("keyword","whatever keyword",
     cxxopts::value<string>())
    ;
  options.parse_positional({"keyword"});

  auto result = options.parse(argc, argv);
  if (result.count("help")>0) {
    cout << options.help() << '\n';
    return 0;
  }

  auto number_of_times = result["ntimes"].as<int>();
  cout << "Using number of times: " << number_of_times << '\n';

  auto keyword = result["keyword"].as<string>();
  cout << "Found keyword: " << keyword << '\n';

  return 0;
}
