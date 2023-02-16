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
#include </usr/include/sys/sysinfo.h>

void printMem() {

  struct sysinfo myinfo;
  sysinfo(&myinfo);
  double total_mem = myinfo.mem_unit * myinfo.totalram;
  total_mem /= (1024.*1024.);
  double free_mem = myinfo.mem_unit * myinfo.freeram;
  free_mem /= (1024.*1024.);

  printf("Total mem: %e, free mem: %e\n",total_mem,free_mem);

}

#define N 10
int main() {

  printMem();
  size_t gig = 1<<30;
  char *buffers[10];
  for (int i=0; i<N; i++)
    buffers[i] = (char*) malloc( gig );
  printMem();
  for (int i=0; i<N; i++)
    memset(buffers[i],0,gig);
  printMem();

  return 0;
}

