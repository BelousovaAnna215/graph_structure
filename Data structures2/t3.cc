// Google Style Guide
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(int64_t n)
      : num_(n),
        array_(n),
        tree_(n, 0) {}

  void BuildTree() {
    for (auto& elem : array_) {
      std::cin >> elem;
    }
    for (int i = 0; i < num_; ++i) {
      Modify(i, array_[i]);
    }
  }
  
  int64_t Sum(int64_t left, int64_t right) const {
    return PrefixSum(right) - PrefixSum(left - 1);
  }
  
  void Change(int64_t index, int64_t value) {
    int c_value = value - array_[index];
    array_[index] = value;
    Modify(index, c_value);
  }
  
 private:
  void Modify(int64_t i, int64_t value) {
    while (i < num_) {
      tree_[i] += value;
      i = i | (i + 1);
    }
  }
  
  int64_t PrefixSum(int64_t right) const {
    int64_t res = 0;
    while (right >= 0) {
      res += tree_[right];
      right = (right & (right + 1)) - 1;
    }
    return res;
  }
       
  int64_t num_;
  std::vector<int64_t> array_;
  std::vector<int64_t> tree_;
};

int main() {
  int64_t n;
  std::cin >> n;
  FenwickTree tree{n};
  
  tree.BuildTree();
  
  int64_t m;
  std::cin >> m;
  int64_t a, b;
  char c;
  while (m--) {
    std::cin >> c >> a >> b;
    if (c == 's') {
      --a;
      --b;
      std::cout << tree.Sum(a, b) << " " ;
    }
    if (c == 'u') {
      --a;
      tree.Change(a, b);
    }
  }
  
  return 0;
}
