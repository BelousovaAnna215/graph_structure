// Google Style Guide
#include <algorithm>
#include <iostream>
#include <vector>

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
  
  bool IsHappy(std::vector<int> &formation) {
    std::vector<int> colour(num_vertex_, 0); // 0 - white, 1 - grey, 2 - black
    for (int i = 0; i < num_vertex_; ++i) {
      if (colour[i] == 0) {
        if (DepthFirstSearch(i, colour, formation)) {;
          return false;
        } 
      }
    }
    return true;
  }
  
 private:
  bool DepthFirstSearch(int curr_vertex, std::vector<int> &colour,
                        std::vector<int> &formation) {
    colour[curr_vertex] = 1;
    for (auto elem : graph_[curr_vertex]) {
      if ((colour[elem] == 0 && DepthFirstSearch(elem, colour, formation)) || colour[elem] == 1) {
        return true;
      }
    }
    formation.push_back(curr_vertex);
    colour[curr_vertex] = 2;
    return false;
  }
  
  int num_vertex_ = 0;
  int num_edge_ = 0;
  std::vector<std::vector<int>> graph_;
};

int main() {
  int n, m;
  std::cin >> n >> m;
  TGraph graph{n, m};
  
  graph.ReadFromStream();
  // graph.PrintGraph();
  std::vector<int> answer; 
  if (graph.IsHappy(answer)) {
    std::cout << "Yes" << std::endl;
    reverse(answer.begin(), answer.end());
    std::cout << ++answer[0];
    for (size_t j = 1; j < answer.size(); ++j) {
      std::cout << " " << ++answer[j];
    }
  } else {
    std::cout << "No" << std::endl;
  }
  
  return 0;
}

