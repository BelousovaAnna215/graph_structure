// Google Style Guide
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

class TGraph {
 public:
  TGraph(int n) 
      : num_vertex_(n),
        //num_edge_(m),
        graph_(n, std::vector<int>(n, 0)) {}
  
  void ReadFromStream() { 
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
      int num;
      std::cin >> num;
      for (int j = 0; j < num; ++j) {
        int a, b;
        std::cin >> a >> b;
        --a;
        --b;
        graph_[a][b] = m + 1;
      }
    }
  }
  
  /*void PrintGraph() const {
    std::cout << "num_vertex = " << num_vertex_ << " num_edge = " << num_edge_<< std::endl;
    for (int i = 0; i < num_vertex_; ++i) {
      std::cout << i << ": ";
      for (auto elem : graph_[i]) {
        std::cout << elem << " ";
      }
      std::cout << std::endl;
    }
  }*/
  
  int BreadthFirstSearch() {
    std::vector<int> dist(num_vertex_, -1);
    std::queue<int> q;
    
    q.push(0);
    dist[0] = 0;
      
    while (!q.empty()) {
      int curr_vertex = q.front();
      q.pop();
      
      // проверяем всех соседей
      for (auto elem : graph_[curr_vertex]) { 
        if (dist[elem] == -1) {
          if (graph[curr_vertex][i] != graph_[i][curr_vertex]) {
            dist[elem] = dist[curr_vertex] + 1;
            q.push(elem);
          }
        }
      }
      
      
      
    }
    return dist[num_vertex_ - 1];
  }
  
 private:
  int num_vertex_ = 0;
  //int num_edge_ = 0;  
  std::vector<std::vector<int>> graph_;
};

int main() {
  int n;
  std::cin >> n;
  TGraph graph{n};
  
  graph.ReadFromStream();
  // graph.PrintGraph();
  std::cout << graph.BreadthFirstSearch();
  
  return 0;
}
