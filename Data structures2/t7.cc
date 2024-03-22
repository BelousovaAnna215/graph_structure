// Google Style Guide
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>

class Treap {
 public:
  int Get(int index) {
    std::shared_ptr<Node> less;
    std::shared_ptr<Node> greater;
    std::shared_ptr<Node> equal;
    Split(root_, index, less, greater);
    Split(greater, 1, equal, greater);
    int result = equal->value_;
    less = Merge(less, equal);
    root_ = Merge(less, greater);
    return result;
  }
  
  void PushBack(int value) {
    std::shared_ptr<Node> elem(new Node(value));
    root_ = Merge(root_, elem);
  }
  
  void Front(int left, int right) {
    std::shared_ptr<Node> less;
    std::shared_ptr<Node> greater;
    std::shared_ptr<Node> equal;
    Split(root_, left, less, greater);
    Split(greater, right - left + 1, equal, greater);
    less = Merge(equal, less);
    root_ = Merge(less, greater);
  }
  
 private:
  static std::minstd_rand generator;
  
  struct Node {
    Node(int v) 
        : value_(v),
          priority_(generator()),
          size_(1) {}
          
    int value_;
    int priority_;
    int size_;
    std::shared_ptr<Node> left_ = nullptr;
    std::shared_ptr<Node> right_ = nullptr;
  };
  
  std::shared_ptr<Node> root_ = nullptr;
  
  static int GetSize(std::shared_ptr<Node> n) {
    if (n) {
      return n->size_;
    } else {
       return 0;
    }
  }
  
  static void Update(std::shared_ptr<Node> n) {
    if (n) {
      n->size_ = GetSize(n->left_) + 1 + GetSize(n->right_);
    }
  }
  
  static std::shared_ptr<Node> Merge(std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
    if (!a || !b) {
      if (a) {
        return a;
      } else {
        return b;
      }
    }
    if (a->priority_ > b->priority_) {
      a->right_ = Merge(a->right_, b);
      Update(a);
      return a;
    } else {
      b->left_ = Merge(a, b->left_);
      Update(b);
      return b;
    }
  }
  
  static void Split(std::shared_ptr<Node> n, int k, std::shared_ptr<Node>& a, std::shared_ptr<Node>& b) {
    if (!n) {
      a = nullptr;
      b = nullptr;
      return;
    }
    if (GetSize(n->left_) < k) {
      Split(n->right_, k - GetSize(n->left_) - 1, n->right_, b);
      a = n;
    } else {
      Split(n->left_, k, a, n->left_);
      b = n;
    }
    Update(a);
    Update(b);
  }
};

std::minstd_rand Treap:: generator;

int main() {
  Treap tree;
  
  int n, m;
  std::cin >> n >> m;
  
  for (int i = 1; i <= n; ++i) {
    tree.PushBack(i);
  }
  
  for (int i = 0; i < m; ++i) {
    int l, r;
    std::cin >> l >> r;
    tree.Front(l - 1, r - 1);
  }
  
  for (int i = 0; i < n; ++i) {
    std::cout << tree.Get(i) << " ";
  }
  
  return 0;
}
