// Google Style Guide
#include <string.h>

#include <iostream>
#include <vector>

int main() {
  long long n;
  std::cin >> n;
  long long m;
  std::cin >> m;
  
  std::vector<std::string> domen;
  std::vector<std::string> ip;
  char s[255];
  for (long long i = 0; i < n; ++i) {
    if (scanf("%s", s) != 0) {
      domen.push_back(s);
    }
    if (scanf("%s", s) != 0) {
      ip.push_back(s);
    }
  }
  
  bool flag = 0;
  for (long long i = 0; i < m; ++i) {
    flag = 0;
    if (scanf("%s", s) != 0) {
      for (long long j = 0; j < n; ++j) {
        if (s == domen[j]) {
          std::cout << ip[j] << std::endl;
          flag = 1;
          break;
        }
      }
      if (flag == 0) {
        std::cout << "PUSTO" << std::endl;
      }
    }
  }
    
  return 0;
}
