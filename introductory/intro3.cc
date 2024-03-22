//Google Style Guide
#include <iostream>

int main() {
  unsigned int num_of_spoon;
  std::cin >> num_of_spoon;
  
  int deg = 1;
  unsigned int dif_num = 2;
  while (num_of_spoon > dif_num) {
    num_of_spoon -= dif_num;
    dif_num <<= 1;
    ++deg;
  }

  if (num_of_spoon == dif_num) {
    std::cout << deg << ' ' << 0;
  } else {
    std::cout << deg - 1 << ' ' << dif_num - num_of_spoon;
  }
  
  return 0;
}
