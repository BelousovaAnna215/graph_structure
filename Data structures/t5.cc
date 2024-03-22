// Google Style Guide
#include <algorithm>
#include <iostream>
#include <vector>

class Array {
 public:
  Array(int n)
      : num_(n),
        mas_(n),
        answer_(n + 1, 0) {}
  
  void ReadArray() {
    for (auto& elem : mas_) {
      std::cin >> elem;
    }
  }
  
  int MinLength() {
    std::sort(mas_.begin(), mas_.end());
    answer_[2] = mas_[1] - mas_[0];
    answer_[3] = mas_[2] - mas_[0];
    for (int i = 4; i <= num_; ++i) {
      answer_[i] = mas_[i - 1] - mas_[i - 2];
      if (answer_[i - 1] < answer_[i - 2]) {
        answer_[i] += answer_[i - 1];
      } else {
        answer_[i] += answer_[i - 2];
      }
    }
    return answer_[num_];
  }
  
 private:
  int num_;
  std::vector<int> mas_;
  std::vector<int> answer_;
};

int main() {
  int n;
  std::cin >> n;
  Array array{n};
  array.ReadArray();
  std::cout << array.MinLength();
  
  return 0;
}
 

