// Google Style Guide
#include <iostream>
#include <vector>

class TDisjointSetUnion {
 public:
  TDisjointSetUnion(int n)
      : unions_(n),
        rank_(n, 1),
        num_set_(n) {
          for (int i = 0; i < n; ++i) {
            unions_[i] = i;
          }
  }
  
  int FindSet(int x) const {
    if (unions_[x] == x) {
      return x;
    }
    unions_[x] = FindSet(unions_[x]);
    return unions_[x];
  }

  void UnionSets(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);
    if (x == y) {
      return;
    }
    --num_set_;
    if (rank_[x] < rank_[y]) {
      unions_[x] = y;
    } else {
      unions_[y] = x;
    }
    if (rank_[x] == rank_[y]) {
      ++rank_[y];
    }
  }
  
  bool OneComponent() const {
    return num_set_ == 1;
  }
  
 private:
  mutable std::vector<int> unions_;
  std::vector<int> rank_;
  int num_set_;
};

int main() {
  int n, m;
  std::cin >> n >> m;
  TDisjointSetUnion myunion{n};
  
  int answer = 0;
  if (n == 1) {
    int u, v;
    for (int j = 0; j < m; ++j) {
      std::cin >> u >> v;
    }
    answer = 0;
  } else {
    for (int i = 0; i < m; ++i) {
      int a, b;
      std::cin >> a >> b;
      myunion.UnionSets(a, b);
      if (myunion.OneComponent()) {
        answer = i + 1;
        ++i;
        for (int j = i; j < m; ++j) {
          int u, v;
          std::cin >> u >> v;
        }
        break;
      }
    }
  }
  std::cout << answer;
  
  return 0;
}
