// Google Style Guide
#include <iostream>
#include <vector>

class TGraph {
 public:
  TGraph(int n)
      : num_vertex_(n),
        graph_(n, std::vector<int>(n))
        {}
 
  void ReadFromStream() {
    for (int i = 0; i < num_vertex_; ++i) {
      for (int j = 0; j < num_vertex_; ++j) {
        std::cin >> graph_[i][j];
      }
    }
  }
  
  void PrintGraph() const {
    std::cout << "num_vertex = " << num_vertex_ << std::endl;
    for (int i = 0; i < num_vertex_; ++i) {
      for (int j = 0; j < num_vertex_; ++j) {
        std::cout << graph_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
  
  std::vector<std::vector<int>> ShortPathMatrix() const {
    auto dist = graph_;
    for (int i = 0; i < num_vertex_; ++i){
      for (int u = 0; u < num_vertex_; ++u){
        for (int v = 0; v < num_vertex_; ++v){
          if (dist[u][v] > dist[u][i] + dist[i][v]) {
            dist[u][v] = dist[u][i] + dist[i][v];
          }
        }
      }
    }
    return dist;
  }
  
 private:
  int num_vertex_;
  std::vector<std::vector<int>> graph_;
};

int main() {
  int n;
  std::cin >> n;
  TGraph graph{n};
  graph.ReadFromStream();
  // graph.PrintGraph();
  
  std::vector<std::vector<int>> answer = graph.ShortPathMatrix();
  for (int i = 0; i < n; ++i) {
    std::cout << answer[i][0];
    for (int j = 1; j < n; ++j) {
      std::cout << " " << answer[i][j];
    }
    std::cout << std::endl;
  }
  
  return 0;
}

