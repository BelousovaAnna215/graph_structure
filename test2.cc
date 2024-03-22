// Google Style Guide
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

class TGraph {
 public:
  TGraph(int n, int m) 
      : num_vertex_(n),
        num_edge_(m),
        graph_(n) {}
  
  void ReadFromStream() { 
    for (int i = 0; i < num_edge_; ++i) {
      int a, b;
      std::cin >> a >> b;
      --a;
      --b;
      bool is_same = false;
      for (auto elem : graph_[a]) {
        if (elem == b) {
          is_same = true;
          break;
        }
      }
      if (is_same == false) {
        graph_[a].push_back(b);
        graph_[b].push_back(a);
      }
    }
  }
  
  void PrintGraph() const {
    std::cout << "num_vertex = " << num_vertex_ << " num_edge = " << num_edge_<< std::endl;
    for (int i = 0; i < num_vertex_; ++i) {
      std::cout << i << ": ";
      for (auto elem : graph_[i]) {
        std::cout << elem << " ";
      }
      std::cout << std::endl;
    }
  }
  
  std::vector<int> BreadthFirstSearch(const std::vector<int> &startVertices) const {
    std::vector<int> dist(num_vertex_, -1);
    std::queue<int> q;
    
    for (auto elem : startVertices) {
      q.push(elem);
      dist[elem] = 0;
    }
      
    while (!q.empty()) {
      int curr_vertex = q.front();
      q.pop();
      
      for (auto elem : graph_[curr_vertex]) {
        if (dist[elem] == -1) {
          dist[elem] = dist[curr_vertex] + 1;
          q.push(elem);
        }
      }
    }
    return dist;
  }
  
 private:
  int num_vertex_ = 0;
  int num_edge_ = 0;  
  std::vector<std::vector<int>> graph_;
};

void ReadExits(std::vector<int> &v, int k) {
  for (int i = 0; i < k; ++i){
    int curr_ex;
    std::cin >> curr_ex;
    v.push_back(--curr_ex);
  }
}

int main() {
  int n, m, k;
  std::cin >> n >> k;
  std::vector<int> exits;
  ReadExits(exits, k);
  std::cin >> m;
  TGraph graph{n, m};
  
  graph.ReadFromStream();
  // graph.PrintGraph();
  const std::vector<int> answer = graph.BreadthFirstSearch(exits);
  std::cout << answer[0];
  for (size_t i = 1; i < answer.size(); ++i) {
    std::cout << " " << answer[i];
  }
  
  return 0;
}

