#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <vector>
using std::vector;

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
  // vector<char> buffers[10];
  // for (int i=0; i<N; i++)
  //   buffers[i] = vector<char>( gig );
  vector<char> b1(gig);
  vector<char> b2(gig);
  vector<char> b3(gig);
  vector<char> b4(gig);
  vector<char> b5(gig);
  printMem();

  return 0;
}

