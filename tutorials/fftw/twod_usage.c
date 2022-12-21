/*
 * example from:
 * http://www.fftw.org/fftw3_doc/2d-MPI-example.html#g_t2d-MPI-example
 */

#include <stdlib.h>
#include <math.h>
#include <fftw3-mpi.h>

#define N 16
#define M_PI 3.1415926535897932384626433832795028

int main(int argc, char **argv)
{
  const ptrdiff_t N0 = N, N1 = N;
  fftw_plan plan;
  fftw_complex *data;
  ptrdiff_t alloc_local, local_n0, local_0_start;

  MPI_Init(&argc, &argv);
  fftw_mpi_init();

  /* get local data size and allocate */
  alloc_local = fftw_mpi_local_size_2d(N0, N1, MPI_COMM_WORLD,
				       &local_n0, &local_0_start);
  data = fftw_alloc_complex(alloc_local);

  /* create plan for in-place forward DFT */
  plan = fftw_mpi_plan_dft_2d(N0, N1, data, data, MPI_COMM_WORLD,
			      FFTW_FORWARD, FFTW_ESTIMATE);    

  /* initialize data to some function my_function(x,y) */
  for (int i = 0; i < local_n0; ++i)
    for (int j = 0; j < N1; ++j) {
      data[i*N1 + j][0] = cos(3 * 2*M_PI*i/N);
      // = my_function(local_0_start + i, j);
      data[i*N1 + j][1] = 0;
    }

  /* compute transforms, in-place, as many times as desired */
  fftw_execute(plan);

  fftw_destroy_plan(plan);

  MPI_Finalize();
}
