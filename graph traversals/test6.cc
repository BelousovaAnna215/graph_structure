// Google Style Guide
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

class TGraph {
 public:
  TGraph()
      : graph_(){}
  
  void ReadFromStream() { 
    int routes;
    std::cin >> routes;
    int vertex;
    std::cin >> vertex;
    graph_.resize(vertex);
    for (int k = 0; k < routes; ++k) {
      int curr_route, a;
      std::cin >> curr_route;
      std::cin >> a;
      int b;
      for (int i = 0; i < curr_route; ++i) {
        std::cin >> b;
        graph_[a - 1].push_back(b - 1);
        a = b;
      }
    }
  }
  
  std::vector<int> FindEulerCycle() const {
    std::vector<std::vector<int>> tmp_graph = graph_;
    if (!CheckEuler()) {
      return std::vector<int>();
    }
    size_t vertex = 0;
    for (; vertex < tmp_graph.size(); ++vertex) {
      if (tmp_graph[vertex].size() != 0) {
        break;
      }
    }
    if (vertex == tmp_graph.size()) {
      return std::vector<int>();
    }
    std::stack<int> connected;
    connected.push(vertex);
    std::vector<int> answer;
    while (!connected.empty()) {
      vertex = connected.top();
      if (!tmp_graph[vertex].empty()) {
        connected.push(tmp_graph[vertex].back());
        tmp_graph[vertex].pop_back();
      } else {
        answer.push_back(vertex + 1);
        connected.pop();
      }
    }
    return answer;
  }
  
 private:
  int DFS() const { 
    int componentsCount = 0;
    std::vector<bool> gray(graph_.size(), false);
    std::stack<int> dfs;
    for (size_t i = 0; i < graph_.size(); ++i) {
      if (gray[i]) {
        continue;
      }
      gray[i] = true;
      if (!graph_[i].empty()) {
        componentsCount++;
      }
      dfs.push(i);
      while (!dfs.empty()) {
        int current = dfs.top();
        dfs.pop();
        for (auto j : graph_[current]) {
          if (gray[j]) {
            continue;
          }
          gray[j] = true;
          dfs.push(j);
        }
      }
    }
    return componentsCount;
  }
 
  bool CheckEuler() const {
    if (DFS() > 1) {
      return false;
    }
    return true;
  }
 
  std::vector<std::vector<int>> graph_;
};

int main() {
  TGraph graph;
  
  graph.ReadFromStream();;
  
  std::vector<int> answer = graph.FindEulerCycle();
  std::cout << answer.size()  << ' ';
  for (auto i = answer.rbegin(); i != answer.rend(); ++i) {
    std::cout << *i << ' ';
  }
  std::cout << std::endl;
  
  return 0;
}
