// Google Style Guide
#include <iostream>
#include <memory>
#include <vector>

template <class TData>
class TVertex {
 public:
  TVertex(const TData& data = 0)
      : data_(data),
        l_child_(),
        r_child_(),
        forward_() {}

  TData data_;
  std::unique_ptr<TVertex> l_child_;
  std::unique_ptr<TVertex> r_child_;
  TData forward_;
};

template <class TData>
class TTree {
 public:
  TTree(const std::vector<TData>& data)
      : root_(),
        size_(data.size()) {
    if (data.size() == 0) {
      return;
    }
    root_ = Construct(0, data.size(), data);
  }

  TData Meaning(size_t begin, size_t end) const {
    if (size_ == 0) {
      return TData();
    }
    return Find(begin, end + 1, 0, size_, root_.get());
  }

  void Add(size_t begin, size_t end, TData value) {
    if (size_ == 0) {
      return;
    }
    Increase(begin, end + 1, 0, size_, root_.get(), value);
  }

 private:
  std::unique_ptr<TVertex<TData>> Construct(size_t begin, size_t end, const std::vector<TData>& data) {
    std::unique_ptr<TVertex<TData>> new_vertex(new TVertex<TData>(data[begin]));
    if (begin == end - 1) {
      return new_vertex;
    }
    new_vertex->l_child_ = Construct(begin, begin + (end - begin) / 2, data);
    new_vertex->r_child_ = Construct(begin + (end - begin) / 2, end, data);
    new_vertex->data_ = std::max(new_vertex->l_child_->data_, new_vertex->r_child_->data_);
    return new_vertex;
  }

  TData Find(size_t begin, size_t end, size_t left, size_t right,
             TVertex<TData>* vertex) const {
    Push(vertex);
    if ((begin <= left) && (right <= end)) {
      return vertex->data_;
    }
    if ((right <= begin) || (end <= left)) {
      return TData();
    }
    size_t position = left + (right - left) / 2;
    TData l_val = Find(begin, end, left, position, vertex->l_child_.get());
    TData r_val = Find(begin, end, position, right, vertex->r_child_.get());
    return std::max(l_val, r_val);
  }

  void Increase(size_t begin, size_t end, size_t left, size_t right,
                TVertex<TData>* vertex, TData value) {
    Push(vertex);
    if ((begin <= left) && (right <= end)) {
      vertex->forward_ = value;
      return;
    }
    if ((right <= begin) || (end <= left)) {
      return;
    }
    size_t position = left + (right - left) / 2;
    Increase(begin, end, left, position, vertex->l_child_.get(), value);
    Increase(begin, end, position, right, vertex->r_child_.get(), value);
    Push(vertex->l_child_.get());
    Push(vertex->r_child_.get());
    vertex->data_ = std::max(vertex->l_child_->data_, vertex->r_child_->data_);
  }

  void Push(TVertex<TData>* vertex) const {
    if (vertex == nullptr) {
      return;
    }
    if (vertex->forward_ == 0) {
      return;
    }
    vertex->data_ += vertex->forward_;
    if (vertex->l_child_ != nullptr) {
      vertex->l_child_->forward_ += vertex->forward_;
    }
    if (vertex->r_child_ != nullptr) {
      vertex->r_child_->forward_ += vertex->forward_;
    }
    vertex->forward_ = 0;
  }

  std::unique_ptr<TVertex<TData>> root_;
  size_t size_;
};

int main() {
  size_t size;
  std::cin >> size;

  std::vector<int32_t> data(size);
  for (auto& i : data) {
    std::cin >> i;
  }

  TTree<int32_t> tree(data);

  int32_t questions;
  std::cin >> questions;

  for (int32_t i = 0; i < questions; ++i) {
    char request;
    std::cin >> request;
    if (request == 'm') {
      size_t begin;
      std::cin >> begin;
      size_t end;
      std::cin >> end;
      std::cout << tree.Meaning(begin - 1, end - 1) << ' ';
    }
    if (request == 'a') {
      size_t begin;
      std::cin >> begin;
      size_t end;
      std::cin >> end;
      int32_t val;
      std::cin >> val;
      tree.Add(begin - 1, end - 1, val);
    }
  }

  std::cout << std::endl;
  return 0;
}
