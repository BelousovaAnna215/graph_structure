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
  
  bool HasCycle() const {
    std::vector<int> colour(num_vertex_, 0); // 0 - white, 1 - grey, 2 - black
    for (int i = 0; i < num_vertex_; ++i) {
      if (DepthFirstSearch(i, colour) == 1) {
        return true;
      }
    }
    return false;
  }
  
 private:
  bool DepthFirstSearch(int curr_vertex, std::vector<int> &colour) const {
    colour[curr_vertex] = 1;
    for (int i = 0; i < num_vertex_; ++i) {
      if (graph_[curr_vertex][i] == 1 && colour[i] == 0) {
        if (DepthFirstSearch(i, colour) == 1) {
          return true;
        }
      } else if (graph_[curr_vertex][i] == 1 && colour[i] == 1) {
        return true;
      }
    }
    colour[curr_vertex] = 2;
    return false;
  }
  
  int num_vertex_ = 0;
  std::vector<std::vector<int>> graph_; // :’-) 
};

int main() {
  int n;
  std::cin >> n;
  if (n < 0) {
    std::cout << 0;
    return 0;
  }
  
  TGraph graph{n};
  graph.ReadFromStream();
  std::cout << graph.HasCycle();
  // graph.PrintGraph();
  
  return 0;
}

