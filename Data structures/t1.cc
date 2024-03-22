// Google Style Guide
#include <iostream>
#include <memory>

class Tree {
 public:
  Tree()
      : height_(0),
        tree_(nullptr) {}
  
  int ReadTree() {
    int curr_num;
    std::cin >> curr_num;
    int max_height = 0;
    while (curr_num) {
      height_ = 0;
      insert(tree_, curr_num);
      if (max_height < height_) {
        max_height = height_;
      }
      std::cin >> curr_num;
    }
    return max_height;
  }
  
 private:
  class Node {
   public:
    Node(int x)
        : data_(x),
          left_(nullptr),
          right_(nullptr) {}
        
    int data_;
    std::unique_ptr<Node> left_;
    std::unique_ptr<Node> right_;
  };

  void insert(std::unique_ptr<Node>& curr_tree, int n) {
    ++height_; 
    if (curr_tree == nullptr) {
      curr_tree = std::make_unique<Node>(n);
      return;
    }
    if (curr_tree->data_ == n) {
      return;
    }
    if (n < curr_tree->data_) {
      insert(curr_tree->left_, n);
    } else {
      insert(curr_tree->right_, n);
    }
  }
  
  int height_;
  std::unique_ptr<Node> tree_;
};

int main() {
  Tree tree;
  std::cout << tree.ReadTree();
  
  return 0;
}
