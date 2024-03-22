// Google Style Guide
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>

class Treap {
 public:
  bool Contains(int key) {
    std::shared_ptr<Node> less;
    std::shared_ptr<Node> greater;
    std::shared_ptr<Node> equal;
    Split(root_, key, less, greater);
    Split(greater, key + 1, equal, greater);
    bool result = false;
    if (equal != nullptr){
      result = true;
    }
    less = Merge(less, equal);
    root_ = Merge(less, greater);
    return result;
  }
 
  void Add(int key) {
    std::shared_ptr<Node> less;
    std::shared_ptr<Node> greater;
    Split(root_, key, less, greater);
    std::shared_ptr<Node> elem(new Node(key));
    less = Merge(less, elem);
    root_ = Merge(less, greater);
  }
  
  int Next(int key) {
    std::shared_ptr<Node> less; 
    std::shared_ptr<Node> greater; 
    Split(root_, key, less, greater);
    int result = Min(greater);
    root_ = Merge(less, greater);
    return result;
  }
  
 private:
  static std::minstd_rand generator;
  
  struct Node {
    Node(int k) 
        : key_(k),
          priority_(generator()) {}
          
    int key_;
    int priority_;
    std::shared_ptr<Node> left_ = nullptr;
    std::shared_ptr<Node> right_ = nullptr;
  };
  
  std::shared_ptr<Node> root_ = nullptr;
  
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
      return a;
    } else {
      b->left_ = Merge(a, b->left_);
      return b;
    }
  }
  
  static void Split(std::shared_ptr<Node> n, int key, std::shared_ptr<Node>& a, std::shared_ptr<Node>& b) {
    if (!n) {
      a = nullptr;
      b = nullptr;
      return;
    }
    if (n->key_ < key) {
      Split(n->right_, key, n->right_, b);
      a = n;
    } else {
      Split(n->left_, key, a, n->left_);
      b = n;
    }
  }
  
  int Min(std::shared_ptr<Node> n) const {
    if (!n) {
      return -1;
    }
    while (n->left_) {
      n  = n->left_;
    }
    return n->key_;
  }
};

std::minstd_rand Treap:: generator;

int main() {
  Treap tree;
  
  int n;
  std::cin >> n;
  
  int prev = 0;
  for (int i = 0; i < n; ++i) {
    char s;
    int x;
    std::cin >> s >> x;
    
    if (s == '+') {
      x = (x + prev) % static_cast<int>(1e9);
      if (!tree.Contains(x)) {
        tree.Add(x);
      }
      prev = 0;
    } else if (s == '?') {
      prev = tree.Next(x);
      std::cout << prev <<std::endl;
    }
  }
  
  return 0;
}
