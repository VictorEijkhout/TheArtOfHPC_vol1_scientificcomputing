#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main() {

  void *ptr;
  auto align{4096}, size{10000};
  posix_memalign( &ptr,align,size );
  cout << ptr << endl;
  cout << ptr % align << endl;

  return 0;
}
