// Google Style Guide
#include <iostream>
#include <vector>
#include <deque>
#include <utility>

const int kINF = static_cast<int>(1e9);

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::vector<std::pair<int, int>>>> edge(n, 
    std::vector<std::vector<std::pair<int, int>>>(m + 1));
  
  for (int i = 0; i < m; ++i) {
    int q;
    std::cin >> q;
    for (int j = 0; j < q; ++j) {
      int a, b;
      std::cin >> a >> b;
      --a, --b;
      edge[a][i + 1].push_back({b, i + 1});
      edge[b][i + 1].push_back({a, i + 1});
      edge[a][i + 1].push_back({a, 0});
      edge[b][i + 1].push_back({b, 0});
      edge[a][0].push_back({a, i + 1});
      edge[b][0].push_back({b, i + 1});
    }
  }

  std::vector<std::vector<int>> dist(n, std::vector<int>(m + 1, kINF));
  std::deque<std::pair<int, int>> d;
  d.push_back({0, 0});
  dist[0][0] = 0;

  while (!d.empty()) {
    auto [to, to_map] = d.front();
    d.pop_front();
    int cost = to_map == 0;

    for (auto [v, v_map] : edge[to][to_map]) {
      if (dist[v][v_map] > dist[to][to_map] + cost) {
        dist[v][v_map] = dist[to][to_map] + cost;
    
        if (cost) {
          d.push_back({v, v_map});
        } else {
          d.push_front({v, v_map});
        }
      }
    }
  }

  if (dist[n - 1][0] == kINF) {
    std::cout << -1;
  } else {
    std::cout << dist[n - 1][0];
  }

  return 0;
}

