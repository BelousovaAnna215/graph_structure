// Google Style Guide
#include <iostream>
#include <vector>

int main() {
  long long n;
  std::cin >> n;
  long long k;
  std::cin >> k;
  
  std::vector<long long> array;
  const int kOne = 1;
  for (long long i = 0; i < k; ++i) {
    array.push_back(kOne);
  }
  
  const long long kNum = 1000000007;
  long long elem = 0;
  for (long long i = k; i <= n; ++i) {
    elem = 0;
    for (long long j = 0; j < k; ++j) {
      elem += array[i - 1 - j];
      elem %= kNum;
    }
    array.push_back(elem);
  }
  
  std::cout << array[n];
    
  return 0;
}
