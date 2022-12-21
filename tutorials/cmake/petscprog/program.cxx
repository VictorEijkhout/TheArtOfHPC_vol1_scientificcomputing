#include <iostream>
using namespace std;

#include "petsc.h"

int main(int argc,char **argv) {
  PetscInitialize(&argc,&argv,0,0);
  PetscPrintf(MPI_COMM_WORLD,"Hello world\n");
  PetscFinalize();
  return 0;
}
