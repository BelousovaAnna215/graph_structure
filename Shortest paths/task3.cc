// Google Style Guide
#include <cmath>
#include <iostream>
#include <optional>
#include <vector>

class Graph {
 public:
  Graph(int n)
      : num_n_(n),
        set_of_points_(n),
        special_roads_(n) {}
        
  void ReadFromStream() {
    for (auto& point : set_of_points_) {
      std::cin >> point.x >> point.y;
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
      int u, v;
      long double w;
      std::cin >> u >> v >> w;
      --u;
      --v;
      special_roads_[u].emplace_back(v, w);
      special_roads_[v].emplace_back(u, w);
    }
  }
  
  long double DijkstraAlgorithm(int begin, int end) const {
    std::vector<long double> min_dist(num_n_, kDoubleInf);
    std::vector<int> vertex(num_n_, 1);
    min_dist[begin] = 0;
    
    long int min_index = kDoubleInf;
    long double min = kDoubleInf;
    do {
      min_index = kDoubleInf;
      min = kDoubleInf;
      for (int i = 0; i < num_n_; ++i) { 
        if ((vertex[i] == 1) && (min_dist[i] < min)) {
          min = min_dist[i];
          min_index = i;
        }
      }
      
      if (min_index != lround(kDoubleInf)) {
        for (int i = 0; i < num_n_; ++i) {
          std::optional<long double> dist;
          for (auto elem : special_roads_[min_index]) {
            if (elem.first == i) {
              dist = elem.second;
              break;
            }
          }
          if (!dist) {
            dist = sqrtl(pow(set_of_points_[min_index].x - set_of_points_[i].x, 2) + 
                         pow(set_of_points_[min_index].y - set_of_points_[i].y, 2));
          }
          long double temp = kDoubleInf;
          if (dist.value() > 0) {
            temp = min + dist.value();
            if (temp < min_dist[i]) {
              min_dist[i] = temp;
            }
          }
        }
        vertex[min_index] = 0;
      }
    } while (min_index < kDoubleInf);
    return min_dist[end];
  }
  
 private:
  const long double kDoubleInf = 1e13;
  
  struct Point {
    long double x, y;
  };
  
  int num_n_; 
  std::vector<Point> set_of_points_;
  std::vector<std::vector<std::pair<int, long double>>> special_roads_;
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
