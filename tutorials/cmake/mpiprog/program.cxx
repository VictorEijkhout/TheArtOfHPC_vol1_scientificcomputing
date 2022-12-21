#include <iostream>
using namespace std;

#include "mpi.h"

int main() {
  MPI_Init(0,0);
  int nprocs,procid;
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&procid);
  if (procid==0)
    cout << "Number of processes: " << nprocs << '\n';
  MPI_Finalize();
  return 0;
}
