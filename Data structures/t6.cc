// Google Style Guide
#include <algorithm>
#include <iostream>
#include <vector>
  
int LevenshteinDistance(const std::string& first, const std::string& second) {
  int len1 = first.size();
  int len2 = second.size();
  if (len1 == 0) {
    return len2;
  } else if (len2 == 0) {
    return len1;
  }
  std::vector<std::vector<int>> dist(len1 + 1, std::vector<int>(len2 + 1, 0));
  for (int i = 0; i < len1 + 1; ++i) {
    dist[i][0] = i;
  }

  for (int j = 0; j < len2 + 1; ++j) {
    dist[0][j] = j;
  }
  
  
  for (int i = 1; i < len1 + 1; ++i) {
    for (int j = 1; j < len2 + 1; ++j) {
      dist[i][j] = std::min(dist[i - 1][j], dist[i][j - 1]) + 1;
      dist[i][j] = std::min(dist[i][j], dist[i - 1][j - 1] + (first[i - 1] != second[j - 1]));

      if (i >= 2 && j >= 2 && (first[i - 2] == second[j - 2]) && (first[i - 1] == (second[j - 1]))) {
        dist[i][j] = std::min(dist[i][j], dist[i - 2][j - 2] + 1);
      }
    }
  }
  return dist[len1][len2];
}

int main() {
  std::string str1, str2;
  std::cin >> str1 >> str2;
  std::cout << LevenshteinDistance(str1, str2);
  
  return 0;
}
