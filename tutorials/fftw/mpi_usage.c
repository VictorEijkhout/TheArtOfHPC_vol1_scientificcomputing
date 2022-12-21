/*
 * two-processor parallel version of basic_usage.c
 */

#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <fftw3.h>

#define N 16
#define M_PI 3.1415926535897932384626433832795028

int main(void) {

  MPI_Init(0,0);
  int nprocs,procid;
  MPI_Comm comm;
  MPI_Comm_size(comm,&nprocs);
  MPI_Comm_rank(comm,&procid);
  int Nlocal = N/nprocs;
  if (N%nprocs!=0) {
    if (procid==0)
      printf("Number of processors has to divide in problem size\n");
    MPI_Abort(comm,0);
  }
  fftw_complex *in,*out,*in2;
  in = (fftw_complex*) malloc(Nlocal*sizeof(fftw_complex));
  out = (fftw_complex*) malloc(Nlocal*sizeof(fftw_complex));
  in2 = (fftw_complex*) malloc(Nlocal*sizeof(fftw_complex));
  fftw_plan p, q;
  int i;

  /* prepare a cosine wave */
  int first = procid * Nlocal;
  for (ilocal = 0; ilocal < N; ilocal++) {
    int i = first+ilocal;
    in[ilocal][0] = cos(3 * 2*M_PI*i/N);
    in[ilocal][1] = 0;
  }

  /* forward Fourier transform, save the result in 'out' */
  p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  for (i = 0; i < N; i++)
    printf("freq: %3d %+9.5f %+9.5f I\n", i, out[i][0], out[i][1]);
  fftw_destroy_plan(p);

  /* backward Fourier transform, save the result in 'in2' */
  printf("\nInverse transform:\n");
  q = fftw_plan_dft_1d(N, out, in2, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(q);
  /* normalize */
  for (i = 0; i < N; i++) {
    in2[i][0] *= 1./N;
    in2[i][1] *= 1./N;
  }
  for (i = 0; i < N; i++)
    printf("recover: %3d %+9.5f %+9.5f I vs. %+9.5f %+9.5f I\n",
	   i, in[i][0], in[i][1], in2[i][0], in2[i][1]);
  fftw_destroy_plan(q);

  fftw_cleanup();
  return 0;
}
