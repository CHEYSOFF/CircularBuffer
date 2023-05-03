#include "lib/CCircuitalBuffer.cpp"
#include "lib/CCircuitalBufferExt.cpp"
#include <iostream>
#include <algorithm>
#include <ostream>

int main() {
  CCircuitalBufferExt<int> a = {5, 1, -12};
//  CCircuitalBufferExt<int> b = {2, 7, 21};
//  std::cout << a.max_size();
//  a.assign({2, 7, 21});
//  std::cout << a.max_size();
//  a.assign({3, 4, 6, 7});
//  std::cout << a.max_size();
  std::cout << a;
  std::sort(a.begin(), a.end());
  std::cout << a;
}
