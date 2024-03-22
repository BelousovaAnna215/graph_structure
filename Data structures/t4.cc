// Google Style Guide
#include <iostream>
#include <string>
#include <vector>

int arr[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683};
 
class HashTable {
 public:
  HashTable()
      : table_(kHashTableSize) {}
  
  int HashFunction(const std::string& s) {
    int hash = 0;
    for (size_t i = 0; i < s.size(); ++i) {
      hash = (hash + s[i] * arr[i]) % kHashTableSize;
    }
    return hash;
  }
  
  void Insert(const std::string& key) {
    if (!Has(key)) {
      table_[HashFunction(key)].push_back(key);
    }
  }
  
  void Remove(const std::string& key) {
    if (Has(key)) {
      int hash = HashFunction(key);
      for (auto elem = table_[hash].begin(); elem < table_[hash].end(); ++elem) {
        if (*elem == key) {
          table_[hash].erase(elem);
        }
      }
    }
  }
  
  bool Has(const std::string& key) {
    int hash = HashFunction(key);
    for (auto &elem : table_[hash]) {
        if (elem == key) {
            return true;
        }
    }
    return false;
  }
  
  std::vector<std::string> ReadFromStream() {
    std::string s;
    std::vector<std::string> result;
    std::cin >> s;
    while (s != "#") {
      if (s == "+") {
          std::cin >> s;
          Insert(s);
      } else if (s == "-") {
          std::cin >> s;
          Remove(s);
      } else if (s == "?") {
          std::cin >> s;
          if (!Has(s)) {
              result.emplace_back("NO");
          } else {
              result.emplace_back("YES");
          }
      }
      std::cin >> s;
    }
    return result;
  }
 
 private:
  const int kHashTableSize = 1000001;
  
  std::vector<std::vector<std::string>> table_;
};
 
int main() {
  HashTable table;
  std::vector<std::string> answer = table.ReadFromStream();
  for (auto elem : answer) {
    std::cout << elem << std::endl;
  }
    
  return 0;
}
