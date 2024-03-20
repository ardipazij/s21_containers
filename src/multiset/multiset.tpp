#include "multiset.h"

namespace s21 {
template <typename Key, class Compare, class Allocator>
multiset<Key, Compare, Allocator>::multiset()
    : tree_(new tree_type()), size_(0) {}

template <typename Key, class Compare, class Allocator>
multiset<Key, Compare, Allocator>::multiset(
    std::initializer_list<value_type> const& items)
    : tree_(new tree_type()) {
  for (auto&& item : items) insert(item);
  size_ = tree_->Size();
}

template <typename Key, class Compare, class Allocator>
multiset<Key, Compare, Allocator>::multiset(const multiset& other)
    : tree_(new tree_type(*other.tree_)), size_(other.size_) {}

template <typename Key, class Compare, class Allocator>
multiset<Key, Compare, Allocator>::multiset(multiset&& other)
    : tree_(other.tree_), size_(other.size_) {
  other.tree_ = nullptr;
  other.size_ = 0;
}

template <typename Key, class Compare, class Allocator>
multiset<Key, Compare, Allocator>::~multiset() {
  delete tree_;
  size_ = 0;
}

template <typename Key, class Compare, class Allocator>
multiset<Key, Compare, Allocator>& multiset<Key, Compare, Allocator>::operator=(
    multiset&& other) {
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
multiset<Key, Compare, Allocator> multiset<Key, Compare, Allocator>::operator=(
    const multiset& other) {
  if (this != &other) {
    tree_->CleanTree();
    *tree_ = *(other.tree_);
    size_ = other.size_;
  }
  return *this;
}

template <typename Key, class Compare, class Allocator>
bool multiset<Key, Compare, Allocator>::empty() {
  return size_ == 0;
}

template <typename Key, class Compare, class Allocator>
std::size_t multiset<Key, Compare, Allocator>::size() {
  return size_;
}

template <typename Key, class Compare, class Allocator>
std::size_t multiset<Key, Compare, Allocator>::max_size() {
  return tree_->MaxSize();
}

template <typename Key, class Compare, class Allocator>
typename multiset<Key, Compare, Allocator>::iterator
multiset<Key, Compare, Allocator>::insert(const Key& value) {
  iterator it = tree_->Insert(value);
  size_ = tree_->Size();
  return it;
}

template <typename Key, class Compare, class Allocator>
template <typename... Args>
std::vector<
    std::pair<typename multiset<Key, Compare, Allocator>::iterator, bool>>
multiset<Key, Compare, Allocator>::insert_many(Args&&... items) {
  std::vector<std::pair<iterator, bool>> vec;
  (..., vec.push_back({this->insert(std::forward<Args>(items)), true}));
  size_ = tree_->Size();
  return vec;
}

template <typename Key, class Compare, class Allocator>
void multiset<Key, Compare, Allocator>::erase(iterator pos) {
  tree_->Erase(pos);
  size_--;
}

template <typename Key, class Compare, class Allocator>
void multiset<Key, Compare, Allocator>::erase(const value_type& key) {
  size_t count_in = count(key);
  while (count_in != 0) {
    tree_->Erase(key);
    size_--;
    count_in--;
  }
};

template <typename Key, class Compare, class Allocator>
void multiset<Key, Compare, Allocator>::merge(multiset& other) {
  if (this != &other) {
    for (auto other_it = other.begin(); other_it != other.end(); ++other_it) {
      insert(*other_it);
    }
    size_ = tree_->Size();
  }
}

template <typename Key, class Compare, class Allocator>
void multiset<Key, Compare, Allocator>::swap(multiset& other) {
  if (this != &other) {
    std::swap(tree_, other.tree_);
    std::swap(size_, other.size_);
  }
}

template <typename Key, class Compare, class Allocator>
void multiset<Key, Compare, Allocator>::clear() {
  tree_->CleanTree();
  size_ = 0;
}

template <typename Key, class Compare, class Allocator>
typename multiset<Key, Compare, Allocator>::iterator
multiset<Key, Compare, Allocator>::begin() {
  return tree_->Begin();
}
template <typename Key, class Compare, class Allocator>
typename multiset<Key, Compare, Allocator>::iterator
multiset<Key, Compare, Allocator>::end() {
  return tree_->End();
}
template <typename Key, class Compare, class Allocator>
typename multiset<Key, Compare, Allocator>::iterator
multiset<Key, Compare, Allocator>::find(const Key& key) {
  return tree_->Find(key);
}

template <typename Key, class Compare, class Allocator>
typename multiset<Key, Compare, Allocator>::const_iterator
multiset<Key, Compare, Allocator>::cbegin() const {
  return tree_->CBegin();
}
template <typename Key, class Compare, class Allocator>
typename multiset<Key, Compare, Allocator>::const_iterator
multiset<Key, Compare, Allocator>::cend() const {
  return tree_->CEnd();
}

template <typename Key, class Compare, class Allocator>
bool multiset<Key, Compare, Allocator>::contains(const Key& key) {
  return tree_->Contains(key);
}

template <typename Key, class Compare, class Allocator>
typename multiset<Key, Compare, Allocator>::iterator
multiset<Key, Compare, Allocator>::lower_bound(const Key& key) noexcept {
  return tree_->LowerBound(key);
}

template <typename Key, class Compare, class Allocator>
typename multiset<Key, Compare, Allocator>::const_iterator
multiset<Key, Compare, Allocator>::lower_bound(const Key& key) const noexcept {
  return tree_->LowerBound(key);
}

template <typename Key, class Compare, class Allocator>
typename multiset<Key, Compare, Allocator>::iterator
multiset<Key, Compare, Allocator>::upper_bound(const Key& key) noexcept {
  return tree_->UpperBound(key);
}

template <typename Key, class Compare, class Allocator>
typename multiset<Key, Compare, Allocator>::const_iterator
multiset<Key, Compare, Allocator>::upper_bound(const Key& key) const noexcept {
  return tree_->UpperBound(key);
}

template <typename Key, class Compare, class Allocator>
std::pair<typename multiset<Key, Compare, Allocator>::iterator,
          typename multiset<Key, Compare, Allocator>::iterator>
multiset<Key, Compare, Allocator>::equal_range(const Key& key) const noexcept {
  return tree_->EqualRange(key);
}

template <typename Key, class Compare, class Allocator>
size_t multiset<Key, Compare, Allocator>::count(const Key& key) const noexcept {
  size_t count_eq = 0;
  auto lower_b = lower_bound(key);
  while (*lower_b == key && lower_b != cend()) {
    count_eq++;
    ++lower_b;
  }
  return count_eq;
}

template <typename Key, class Compare, class Allocator>
bool multiset<Key, Compare, Allocator>::RedAlert() {
  return tree_->HasRedFamily();
}  // проверка красных пар child-parent

template <typename Key, class Compare, class Allocator>
bool multiset<Key, Compare, Allocator>::BLM() {
  return tree_->CheckBlackHeight();
}  // проверка одинаковости черных высот

}  // namespace s21