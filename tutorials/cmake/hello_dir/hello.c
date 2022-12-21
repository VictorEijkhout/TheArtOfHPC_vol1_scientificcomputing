#include <stdlib.h>
#include <stdio.h>

#include "compute.h"
#include "output.h"

int main() {
  int result = f();
  g(result);
  return 0;
}
