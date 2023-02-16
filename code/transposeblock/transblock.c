/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <time.h>
#include <sys/time.h>
typedef unsigned long long ulong_t;
#define get_usecs(t)   ((ulong_t)t.tv_sec * 1000000ULL + (ulong_t)t.tv_usec)

#ifndef NEXPERIMENT
#define NEXPERIMENT 100
#endif

int main(int argc,char **argv) {

  /*
   * Establish array size.
   * Non-default usage:
   * transregular -n 123
   */
  int N=1000;
  if (argc>1) {
    if (!strcmp(argv[1],"-h")) {
      printf("Usage: %s [-n 123]\n",argv[0]);
      return 0;
    } else if (!strcmp(argv[1],"-n") && argc>=3) {
      N = atoi(argv[2]);
    }
  }

  double A[N][N],B[N][N];
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++)
      B[i][j] = 1.*i*j;

  
  struct timeval start_time, stop_time;
  gettimeofday(&start_time, NULL);
  for (int iexperiment=0; iexperiment<NEXPERIMENT; iexperiment++) {
    for (int i=0; i<N; i++)
      for (int j=0; j<N; j++)
	A[i][j] += B[j][i];
  }
  gettimeofday(&stop_time, NULL);
  unsigned elapsed_us = (unsigned)(get_usecs(stop_time) - get_usecs(start_time));
  
  // Make sure the above copy is not optimized away
  double s = 0;
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++)
      s += A[i][j];

  printf("Time: %7.5f (checksum: %e)\n",elapsed_us/1000000.,s);

  return 0;
}
