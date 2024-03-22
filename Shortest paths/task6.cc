// Google Style Guide
#include <iostream>
#include <set>
#include <vector>

class Graph {
 public:
  Graph(int n)
      : num_n_(n),
        graph_(n) {}
        
  void ReadFromStream() {
    int k;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
      int a, b, len;
      std::cin >> a >> b >> len;
      --a;
      --b;
      graph_[a].emplace_back(b, len);
      graph_[b].emplace_back(a, len);
    }
  }
  
  long int DijkstraAlgorithm(int begin, int end) const {
    std::vector<long int> min_dist(num_n_, kInf);
    min_dist[begin] = 0;
    
    std::set<std::pair<int,int>> vertex;
    vertex.emplace(min_dist[begin], begin);
    
    while (!vertex.empty()) {
      int curr_vertex = vertex.begin()->second;
      vertex.erase(vertex.begin());
      
      for (auto [to, dist] : graph_[curr_vertex]) {
        if (min_dist[curr_vertex] + dist < min_dist[to]) {
          vertex.erase(std::make_pair(min_dist[to], to));
          min_dist[to] = min_dist[curr_vertex] + dist;
          vertex.emplace(min_dist[to], to);
        }
      }
    }
    if (min_dist[end] != kInf) {
      return min_dist[end];
    } else {
      return -1;
    }
  }
  
 private:
  const long int kInf = 1e13;
  int num_n_; 
  std::vector<std::vector<std::pair<int, int>>> graph_;
};

int main() {
  int n;
  std::cin >> n;
  Graph graph{n};
  graph.ReadFromStream();
  
  
  int begin, end;
  std::cin >> begin >> end;
  --begin;
  --end;
  
  std::cout << graph.DijkstraAlgorithm(begin, end);
  
  return 0;
}
