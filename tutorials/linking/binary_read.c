#include <stdlib.h>
#include <stdio.h>

int main() {

  FILE *binfile;
  //codesnippet cbinread
  binfile = fopen("binarydata.out","rb");
  for (int i=0; i<10; i++) {
    int ival;
    fread(&ival,sizeof(int),1,binfile);
    printf("%d ",ival);
  }
  printf("\n");
  //codesnippet end
  fclose(binfile);

  return 0;
}
