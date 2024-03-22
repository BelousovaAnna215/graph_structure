// Google Style Guide
#include <iostream>
#include <vector>

class Wires {
 public:
  Wires(int n, int k)
      : count_(k),
        array_(n) {}
  
  void ReadFromStream() {
    for (auto& elem : array_) {
      std::cin >> elem;
    }
  }
  
  int Solve() const {
    int left_border = 0, right_border = 1e8;
    int max_len = 0;
    while (left_border <= right_border) {
      int middle = (left_border + right_border) >> 1;
      if (middle == 0) {
        left_border = middle + 1;
        continue;
      }
      int curr_amount = Calc(middle);
      if (curr_amount < count_) {
        right_border = middle - 1;
      } else if (curr_amount >= count_) {
        left_border = middle + 1;
        if (middle > max_len) {
          max_len = middle;
        }
      }
    }
    return max_len;
  }

 private:
  int Calc(int len) const {
    int res = 0;
    for (auto elem : array_) {
      res += elem / len;
    }
    return res;
  }
  
  int count_;
  std::vector<int> array_;
};

int main() {
    int n, k;
    std::cin >> n >> k;
    Wires arr(n, k);
    
    arr.ReadFromStream();
    std::cout << arr.Solve();
    
    return 0;
}

