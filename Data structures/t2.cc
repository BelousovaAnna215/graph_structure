// Google Style Guide
#include <iostream>
#include <vector>

class Array {
 public:
  Array(int n)
      : num_(n),
        array_(n) {}
  
  void ReadFromStream() {
    for (auto& elem : array_) {
      std::cin >> elem;
    }
  }
  
  void HeapSort() {
    for (int i = num_ / 2 - 1; i >= 0; --i) {
      Heapify(num_, i);
    }
    for (int i = num_ - 1; i >= 0; --i) {
      std::swap(array_[0], array_[i]);
      Heapify(i, 0);
    }
  }
  
  void PrintAnswer() const {
    std::cout << array_[0];
    for (int i = 1; i < num_; ++i) {
      std::cout << " " << array_[i];
    }
  }

 private:
  void Heapify(int n, int i) {
    int largest = i;   
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && array_[left] > array_[largest]) {
      largest = left;
    }
    if (right < n && array_[right] > array_[largest]) {
      largest = right;
    }
    if (largest != i) {
      std::swap(array_[i], array_[largest]);
      Heapify(n, largest);
    }
  }
  
  int num_;
  std::vector<int> array_;
};

int main() {
    int n;
    std::cin >> n;
    Array arr(n);
    
    arr.ReadFromStream();
    arr.HeapSort();
    arr.PrintAnswer();
    
    return 0;
}
