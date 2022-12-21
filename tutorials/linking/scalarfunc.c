#include <stdlib.h>
#include <stdio.h>

float root(int i) {
  return .61*i;
}

void rootsubr_(int *i,float *x) {
  *x = root(*i);
};

int rootfunc_(int *i) {
  return root(*i);
};

