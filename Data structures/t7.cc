// Google Style Guide
#include <iostream>
#include <vector>
#include <stack>
#include <utility>

int Rotate(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c) {
  return (b.first - a.first) * (c.second - b.second) - (b.second - a.second) * (c.first - b.first);
}
class Shell {
 public:
  Shell(int n)
      : num_(n),
        points_(n) {}
        
  void ReadPoint() {
    for (auto& elem : points_) {
      std::cin >> elem.first >> elem.second;
    }
  }
  
  void WritePoint() {
    for (auto elem : points_) {
      std::cout << elem.first << " " << elem.second << std::endl;
    }
  }
  
  void Write(std::vector<int> a) {
    std::cout << "Write" << std::endl;
    for (auto elem : a) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }
  
  std::stack<std::pair<int, int>> ConvexHull() {
    std::cout << "here" << std::endl;
    std::vector<int> point_list(num_);
    for (int i = 0; i < num_; ++i) {
      point_list[i] = i;
    }
    Write(point_list);
    for (int i = 1; i < num_; ++i) {
      if (points_[point_list[i]].first < points_[point_list[0]].first) {
        std::swap(point_list[0], point_list[i]);
      }
    }
    Write(point_list);
    
    for (int i = 2; i < num_; ++i) {
      int j = i;
      while ((j > 1) && (Rotate(points_[point_list[0]], points_[point_list[j-1]], points_[point_list[j]]) < 0)) { 
        std::swap(point_list[j], point_list[j - 1]);
        --j;
      }
    }
    std::cout << "here2" << std::endl;
    Write(point_list);
    
    
    std::stack<std::pair<int, int>> st;
    st.push(points_[0]);
    st.push(points_[1]);
    std::cout << "here3" << std::endl;
    for (int i = 2; i < num_; ++i) {
      auto a = st.top();
      std::cout << "b = " << a.first << a.second << std::endl;
      st.pop();
      auto b = st.top();
      std::cout << "a = " << b.first << b.second << std::endl;
      std::cout << "c = " << points_[point_list[i]].first << points_[point_list[i]].second << std::endl;
      while (Rotate(b, a, points_[point_list[i]]) < 0) {
        st.pop(); // убираем b
        if (st.size() < 2) {
          break;
        } else {
          auto a = st.top();
          std::cout << "b = " << a.first << a.second << std::endl;
          st.pop();
          auto b = st.top();
          std::cout << "a = " << b.first << b.second << std::endl;
          std::cout << "c = " << points_[point_list[i]].first << points_[point_list[i]].second << std::endl;
        }
      }
      //st.push(b);
      st.push(a);
      st.push(points_[i]);
    }
    return st;
  }
  
 private:
  int Rotate(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c) {
    int k = (b.first - a.first) * (c.second - b.second) - (b.second - a.second) * (c.first - b.first);
    std::cout << "k = " << k << std::endl;
    return k;
  }
  
  int num_;
  std::vector<std::pair<int, int>> points_;
};

int main() {
  int n;
  std::cin >> n;
  Shell point{n};
  point.ReadPoint();
  point.WritePoint();
  
  std::stack<std::pair<int, int>> answer = point.ConvexHull();
  std::cout << "answer" << std::endl;
  while (!answer.empty()) {
    auto a = answer.top();
    std::cout << a.first << " " << a.second << std::endl;
    answer.pop();
  }
    
  return 0;
}

