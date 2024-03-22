// Google Style Guide
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class SegmentTree {
 public:
  SegmentTree(int64_t n)
      : num_(n),
        tree_(n) {}
        
  void ReadTree() {
    for (auto& elem : tree_) {
      std::cin >> elem;
    }
  }

  void BuildTree() {
    if (num_ == 1) {
      tree_.resize(2 * num_, tree_[0]);
      return;
    }
    if (num_> 0 && (num_ & (num_ - 1)) != 0) {
      num_ = pow(2, floor(log2(num_) + 1));
    }
    tree_.resize(2 * num_, 0);

    for (int i = num_ ; i < 2 * num_; ++i) {
      tree_[i] = tree_[i - num_];
    }
  
    for (int i = num_ - 1; i > 0; --i) {
      tree_[i] = tree_[2 * i] + tree_[2 * i + 1];
    }
    tree_[0] = tree_[1];
  }
  
  void PrintTree() const {
    for (auto elem : tree_) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }
  
  int64_t Sum(int64_t left, int64_t right) const {
    if (left == right) {
      return tree_[left + num_];
    }
    int64_t sum = 0;
    int64_t n = tree_.size() / 2;
    left += n;
    right += n;
    while (left <= right) { 
      if (left & 1) {
        sum += tree_[left];
      }
      if (!(right & 1)) {
        sum += tree_[right];
      }
      left = (left + 1) / 2;
      right = (right - 1) / 2;
    }		
    return sum;
  }
  
  void Change(int64_t index, int64_t value) {
    int64_t n = tree_.size() / 2;
    index += n;
    tree_[index] = value;
    while (index /= 2) {
      tree_[index] = tree_[2 * index] + tree_[2 * index + 1];
    }
  }
  
 private:
  int64_t num_;
  std::vector<int64_t> tree_;
};

int main() {
  int64_t n;
  std::cin >> n;
  SegmentTree tree{n};
  
  tree.ReadTree();
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
