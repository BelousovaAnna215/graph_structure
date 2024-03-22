// Google Style Guide
#include <iostream>
#include <vector>

int main() {
  unsigned int n;
  std::cin >> n;
  
  std::vector<long long> array;
  long long elem;
  for (size_t i = 0; i < n; ++i) {
      std::cin >> elem;
      array.push_back(elem);
  }

  unsigned int num_begin = 0, num_end = n - 1;
  long long sum_begin = array[num_begin], sum_end = array[num_end];
  while (num_end - num_begin > 1) {
    if (sum_begin > sum_end) {
      sum_end += array[--num_end];
    } else {
      sum_begin += array[++num_begin];
    } 
  }
  
  if (sum_begin > sum_end) {
    std::cout << sum_begin;
  } else {
    std::cout << sum_end;
  }
    
  return 0;
}
