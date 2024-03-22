// Google Style Guide
#include <iostream>
#include <vector>

class TGraph {
 public:
  TGraph(uint64_t n, uint64_t m) 
      : num_vertex_(n),
        num_edge_(m),
        graph_(n),
        rev_graph_(n) {}
  
  void ReadFromStream() { 
    for (uint64_t i = 0; i < num_edge_; ++i) {
      uint64_t a, b;
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
      if (!is_same) {
        graph_[a].push_back(b);
        rev_graph_[b].push_back(a);
      }
    }
  }
  
  void PrintGraph() const {
    std::cout << "num_vertex = " << num_vertex_ << " num_edge = " << num_edge_<< std::endl;
    for (uint64_t i = 0; i < num_vertex_; ++i) {
      std::cout << i << ": ";
      for (auto elem : graph_[i]) {
        std::cout << elem << " ";
      }
      std::cout << std::endl;
    }
  }
  
  std::pair<uint64_t, std::vector<uint64_t>> StrongConnectAndSort() const {
    std::vector<bool> colour(num_vertex_, false);
    std::vector<uint64_t> order;
    for (uint64_t i = 0; i < num_vertex_; ++i) {
      if (!colour[i]) {
        DepthFirstSearchFirst(i, colour, order);
      }
    }
    
    colour.assign(num_vertex_, false);
    uint64_t connected_components = 0;
    std::vector<uint64_t> answer(num_vertex_, 0);
    for (uint64_t i = 0; i < num_vertex_; ++i) {
      std::vector<uint64_t> component;
      int v = order[num_vertex_ - 1 - i];
      if (!colour[v]) {
        connected_components++;
        DepthFirstSearchSecond(v, colour, component);
        for (auto elem : component) {
          answer[elem] = connected_components;
        }
      }
    }
    return std::pair<uint64_t, std::vector<uint64_t>>(connected_components, answer);
  }
  
 private:
  void DepthFirstSearchFirst(uint64_t curr_vertex, std::vector<bool>& colour, 
                             std::vector<uint64_t>& order) const {                 
    colour[curr_vertex] = true;
    for (auto elem : graph_[curr_vertex]) {
      if (!colour[elem]) {
        DepthFirstSearchFirst(elem, colour, order);
      }
    }
    order.push_back(curr_vertex);
  }
  
  void DepthFirstSearchSecond(uint64_t curr_vertex, std::vector<bool>& colour,
                              std::vector<uint64_t>& component) const {
    colour[curr_vertex] = true;
    component.push_back(curr_vertex);
    for (auto elem : rev_graph_[curr_vertex]) {
      if (!colour[elem]) {
        DepthFirstSearchSecond(elem, colour, component);
      }
    }
  }
 
  uint64_t num_vertex_ = 0;
  uint64_t num_edge_ = 0;  
  std::vector<std::vector<uint64_t>> graph_, rev_graph_;
};

int main() {
  uint64_t n, m;
  std::cin >> n >> m;
  TGraph graph{n, m};
  
  graph.ReadFromStream();
  // graph.PrintGraph();
  auto [connected_components, answer] = graph.StrongConnectAndSort();
  std::cout << connected_components << std::endl;
  std::cout << answer[0];
  for (size_t i = 1; i < answer.size(); ++i) {
    std::cout << " " << answer[i];
  }
  
  return 0;
}
