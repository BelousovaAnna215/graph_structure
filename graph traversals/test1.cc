// Google Style Guide
#include <iostream>
#include <vector>

class TGraph {
 public:
  TGraph(int n, int s)
      : vertex_(s),
        num_vertex_(n),
        draph_(n, std::vector<int>(n))
        {}
 
  void ReadFromStream() {
    for (int i = 0; i < num_vertex_; ++i) {
      for (int j = 0; j < num_vertex_; ++j) {
        std::cin >> draph_[i][j];
      }
    }
  }
  
  void PrintGraph() const {
    std::cout << "num_vertex = " << num_vertex_ << " vertex = " << vertex_ << std::endl;
    for (int i = 0; i < num_vertex_; ++i) {
      for (int j = 0; j < num_vertex_; ++j) {
        std::cout << draph_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
  
  std::vector<int> GetConnectedComponent() const {
    std::vector<int> v;
    std::vector<int> colour_(num_vertex_, 0); // 0 - white, 1 - grey, 2 - black
    DepthFirstSearch(vertex_, colour_);
    for (int i = 0; i < num_vertex_; ++i) {
      if (colour_[i] == 2) {
        v.push_back(i);
      }
    }
    return v;
  }
  
 private:
  int vertex_;
  int num_vertex_;
  std::vector<std::vector<int>> draph_;
  
  void DepthFirstSearch(int curr_vertex, std::vector<int> &colour_) const {
    colour_[curr_vertex] = 1;
    for (int i = 0; i < num_vertex_; ++i) {
      if (draph_[curr_vertex][i] == 1 && colour_[i] == 0) {
        DepthFirstSearch(i, colour_);
      }
    }
    colour_[curr_vertex] = 2;
    return;
  }
};

int main() {
  int n, s;
  std::cin >> n >> s;
  s--;
  TGraph graph{n, s};
  graph.ReadFromStream();
  // graph.PrintGraph();
  
  std::vector<int> connect_component = graph.GetConnectedComponent();
  std::cout << connect_component.size();
  
  return 0;
}
