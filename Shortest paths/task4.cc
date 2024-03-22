// Google Style Guide
#include <algorithm>
#include <iostream>
#include <vector>

class DisjointSetUnion {
 public:
  DisjointSetUnion(int n, int m)
      : unions_(n, std::vector<std::pair<int, int>>(m)),
        rank_(n, std::vector<int>(m)) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        unions_[i][j].first = i;
        unions_[i][j].second = j;
        rank_[i][j] = 1;
      }
    }
  }
  
  std::pair<int, int> FindSet(std::pair<int, int> elem) const {
    if (unions_[elem.first][elem.second] == elem) {
      return elem;
    }
    unions_[elem.first][elem.second] = FindSet(unions_[elem.first][elem.second]);
    return unions_[elem.first][elem.second];
  }
  
   bool UnionSets(std::pair<int, int> x, std::pair<int, int> y) {
    x = FindSet(x);
    y = FindSet(y);
    if (x == y) {
      return false;
    }
    if (rank_[x.first][x.second] < rank_[y.first][y.second]) {
      unions_[x.first][x.second] = y;
    } else {
      unions_[y.first][y.second] = x;
    }
    if (rank_[x.first][x.second] == rank_[y.first][y.second]) {
      ++rank_[y.first][y.second];
    }
    return true;
  }
  
 private:
  mutable std::vector<std::vector<std::pair<int, int>>> unions_;
  std::vector<std::vector<int>> rank_;
};

class Graph {
 public:
  Graph(int n, int m)
      : union_{n, m},
        num_n_(n),
        num_m_(m),
        edges_() {}
 
  void ReadFromStream() {
    int vertex;
    for (int i = 0; i < num_n_ ; ++i) {
      for (int j = 0; j < num_m_ ; ++j) {
        std::cin >> vertex;
        std::pair<int, int> a, b;
        if (vertex == 0) {
          if (i != num_n_ - 1) {
            edges_.emplace_back(Edge{i, j, i + 1, j, 1});
          }
          if (j != num_m_ - 1) {
            edges_.emplace_back(Edge{i, j, i, j + 1, 2});
          }
        } else if (vertex == 1) {
          if (j != num_m_ - 1) {
            edges_.emplace_back(Edge{i, j, i, j + 1, 2});
          }
          if (i != num_n_ - 1) {
            a = { i, j };
            b = { i + 1, j };
            union_.UnionSets(a, b);
          }
        } else if (vertex == 2) {
          if (i != num_n_ - 1) {
            edges_.emplace_back(Edge{i, j, i + 1, j, 1});
          }
          if (j != num_m_ - 1) {
            a = { i, j };
            b = { i, j + 1 };
            union_.UnionSets(a, b);
          }
        } else if (vertex == 3) {
          if (j != num_m_ - 1) {
            a = { i, j };
            b = { i, j + 1 };
            union_.UnionSets(a, b);
          }
          if (i != num_n_ - 1) {
            a = { i, j };
            b = { i + 1, j };
            union_.UnionSets(a, b);
          }
        }
      }
    }
  }
  
  void PrintEdges() const {
    for (const auto& edge : edges_) {
      std::cout << edge.x1 << edge.y1 << edge.x2 << edge.y2 << edge.len << std::endl;
    }
  }
  
  std::vector<std::pair<std::pair<int, int>, int>> MinSpanningTree(int& weight, int& count) {
    std::vector<std::pair<std::pair<int, int>, int>> res(num_n_ * num_m_);
    sort(edges_.begin(), edges_.end()); 
    for (auto& elem : edges_) {
      std::pair<int, int> a = { elem.x1, elem.y1 };
      std::pair<int, int> b = { elem.x2, elem.y2 };
      if (union_.UnionSets(a, b)) {  
        weight += elem.len;
        res[count].first.first = elem.x1 + 1;
        res[count].first.second = elem.y1 + 1;
        res[count].second = elem.len;
        ++count;
      }
    }
    return res;
  }
  
 private:
  DisjointSetUnion union_;
  struct Edge {
    int x1, y1, x2, y2, len;
    
    bool operator<(const Edge& other) const {
        return len < other.len;
    }
  };
  
  int num_n_, num_m_;
  std::vector<Edge> edges_;
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph{n, m};
  int weight = 0;
  int count = 0;

  graph.ReadFromStream();
  // graph.PrintEdges();
  
  auto answer = graph.MinSpanningTree(weight, count);
  std::cout << count << " " << weight << std::endl;
  for (auto elem : answer) {
    if (elem.second) {
      std::cout << elem.first.first << " " << elem.first.second << " "
                << elem.second << std::endl;
    }
  }
  
  return 0;
}
