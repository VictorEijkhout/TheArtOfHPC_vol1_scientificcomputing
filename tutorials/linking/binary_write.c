#include <stdlib.h>
#include <stdio.h>

int main() {

  //codesnippet cbinwrite
  FILE *binfile;
  binfile = fopen("binarydata.out","wb");
  for (int i=0; i<10; i++)
    fwrite(&i,sizeof(int),1,binfile);
  fclose(binfile);
  //codesnippet end

  return 0;
}
