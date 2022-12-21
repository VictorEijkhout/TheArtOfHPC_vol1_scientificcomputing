#include <iostream>
#include <vector>
using namespace std;

#include "mkl_cblas.h"

int main() {
  vector<double> values{1,2,3,2,1};
  auto maxloc = cblas_idamax ( values.size(),values.data(),1);
  cout << "Max abs at: " << maxloc << " (s/b 2)" << '\n';

  return 0;
}
