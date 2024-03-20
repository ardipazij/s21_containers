#include "set.h"

namespace s21 {
template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::set() : tree_(new tree_type()), size_(0) {}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::set(
    std::initializer_list<value_type> const &items)
    : tree_(new tree_type()) {
  for (auto &&item : items) insert(item);
  size_ = tree_->Size();
}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::set(const set &other)
    : tree_(new tree_type(*other.tree_)), size_(other.size_) {}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::set(set &&other)
    : tree_(other.tree_), size_(other.size_) {
  other.tree_ = nullptr;
  other.size_ = 0;
}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::~set() {
  delete tree_;
  size_ = 0;
}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator> &set<Key, Compare, Allocator>::operator=(
    set &&other) {
  if (this != &other) {
    delete tree_;
    tree_ = other.tree_;
    size_ = other.size_;
    other.tree_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator> set<Key, Compare, Allocator>::operator=(
    const set &other) {
  if (this != &other) {
    tree_->CleanTree();
    *tree_ = *(other.tree_);
    size_ = other.size_;
  }
  return *this;
}

template <typename Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::operator==(const set &other) {
  if (this == &other) return true;
  return *tree_ == *other.tree_;
}

template <typename Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::operator!=(const set &other) {
  return !(*this == other);
}

template <typename Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::empty() {
  return size_ == 0;
}

template <typename Key, class Compare, class Allocator>
std::size_t set<Key, Compare, Allocator>::size() {
  return size_;
}

template <typename Key, class Compare, class Allocator>
std::size_t set<Key, Compare, Allocator>::max_size() {
  return tree_->MaxSize();
}

template <typename Key, class Compare, class Allocator>
std::pair<typename set<Key, Compare, Allocator>::iterator, bool>
set<Key, Compare, Allocator>::insert(const Key &value) {
  std::pair<iterator, bool> pair = tree_->InsertUniq(value);
  size_ = tree_->Size();
  return {pair.first, !pair.second};
}

template <typename Key, class Compare, class Allocator>
template <typename... Args>
std::vector<std::pair<typename set<Key, Compare, Allocator>::iterator, bool>>
set<Key, Compare, Allocator>::insert_many(Args &&...items) {
  std::vector<std::pair<iterator, bool>> vec;
  (..., vec.push_back(this->insert(std::forward<Args>(items))));
  size_ = tree_->Size();
  return vec;
}

template <typename Key, class Compare, class Allocator>
void set<Key, Compare, Allocator>::erase(iterator pos) {
  tree_->Erase(pos);
  size_--;
}

template <typename Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::erase(const value_type &key) {
  bool result = tree_->Erase(key);
  if (result) size_--;
  return result;
};

template <typename Key, class Compare, class Allocator>
void set<Key, Compare, Allocator>::merge(set &other) {
  if (this != &other) {
    for (auto other_it = other.begin(); other_it != other.end(); ++other_it) {
      insert(*other_it);
    }
    size_ = tree_->Size();
  }
}

template <typename Key, class Compare, class Allocator>
void set<Key, Compare, Allocator>::swap(set &other) {
  if (this != &other) {
    std::swap(tree_, other.tree_);
    std::swap(size_, other.size_);
  }
}

template <typename Key, class Compare, class Allocator>
void set<Key, Compare, Allocator>::clear() {
  tree_->CleanTree();
  size_ = 0;
}

template <typename Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator
set<Key, Compare, Allocator>::begin() {
  return tree_->Begin();
}
template <typename Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator
set<Key, Compare, Allocator>::end() {
  return tree_->End();
}
template <typename Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator
set<Key, Compare, Allocator>::find(const Key &key) {
  return tree_->Find(key);
}

template <typename Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::const_iterator
set<Key, Compare, Allocator>::cbegin() const {
  return tree_->CBegin();
}
template <typename Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::const_iterator
set<Key, Compare, Allocator>::cend() const {
  return tree_->CEnd();
}

template <typename Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::contains(const Key &key) {
  return tree_->Contains(key);
}

template <typename Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::RedAlert() {
  return tree_->HasRedFamily();
}  // проверка красных пар child-parent

template <typename Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::BLM() {
  return tree_->CheckBlackHeight();
}  // проверка одинаковости черных высот

}  // namespace s21