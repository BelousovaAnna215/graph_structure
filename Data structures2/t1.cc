// Google Style Guide
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class SegmentTree {
 public:
  SegmentTree(int n)
      : num_(n),
        tree_(n) {}
        
  void ReadTree() {
    for (auto& elem : tree_) {
      std::cin >> elem;
    }
  }

  void BuildTree() {
    int tree_num = num_;
    if (num_ == 1) {
      return;
    }
    if (num_> 0 && (num_ & (num_ - 1)) != 0) {
      tree_num = pow(2, floor(log2(num_) + 1));
    }
    tree_.resize(2 * tree_num, 0);

    for (int i = tree_num ; i < 2 * tree_num; ++i) {
      tree_[i] = tree_[i - tree_num];
    }
  
    for (int i = tree_num - 1; i > 0; --i) {
      tree_[i] = std::max(tree_[2 * i], tree_[2 * i + 1]);
    }
    tree_[0] = tree_[1];
  }
  
  void PrintTree() const {
    for (auto elem : tree_) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }
  
  int FindMax(int left, int right) const {
    if (left == right) {
      return left;
    }
    int answer = 0;
    int n = tree_.size() / 2;
    left += n - 1;
    right += n - 1;
    int curr_left = left;
    int curr_right = right;
    while (curr_left <= curr_right) {
      if (curr_left & 1) {
        answer = std::max(answer, tree_[curr_left]);
      }
      if (!(curr_right & 1)) {
        answer = std::max(answer, tree_[curr_right]);
      }
      curr_left = (curr_left + 1) / 2;
      curr_right = (curr_right - 1) / 2;
    }		
    int index = left - n + 1;
    for (int i = left; i <= right; ++i) {
      if (tree_[i] == answer) {
        index = i - n + 1;
        break;
      }
    }
    return index;
  }
  
 private:
  int num_;
  std::vector<int> tree_;
};

int main() {
  int n;
  std::cin >> n;
  SegmentTree tree{n};
  
  tree.ReadTree();
  tree.BuildTree();
  
  int k, a, b;
  std::cin >> k;
  std::cin >> a >> b;
  std::cout << tree.FindMax(a, b);
  for (int i = 1; i < k; ++i) {
    std::cin >> a >> b;
    std::cout << " " << tree.FindMax(a, b);
  }
  
  return 0;
}
