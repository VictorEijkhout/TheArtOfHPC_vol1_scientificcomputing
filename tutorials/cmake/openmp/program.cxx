#include <iostream>
using namespace std;

#include "omp.h"

int main() {
  double t = omp_get_wtime();
  cout << "time: " << t << '\n';
  return 0;
}
