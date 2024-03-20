#include "map.h"

namespace s21 {

template <class Key, class T, class Compare, class Alloc>
map<Key, T, Compare, Alloc>::map() : tree_(new tree_type{}), size_(0) {}

template <class Key, class T, class Compare, class Alloc>
map<Key, T, Compare, Alloc>::map(const map& other)
    : tree_(new tree_type(*other.tree_)), size_(other.size_) {}

template <class Key, class T, class Compare, class Alloc>
map<Key, T, Compare, Alloc>::map(map&& other) noexcept
    : tree_(other.tree_), size_(other.size_) {
  other.tree_ = nullptr;
  other.size_ = 0;
}

template <class Key, class T, class Compare, class Alloc>
map<Key, T, Compare, Alloc>::map(
    std::initializer_list<
        typename map<Key, T, Compare, Alloc>::value_type> const& items)
    : tree_(new tree_type) {
  for (const auto& item : items) {
    insert(item);
  }
  size_ = tree_->Size();
}

template <class Key, class T, class Compare, class Alloc>
map<Key, T, Compare, Alloc>::~map() {
  delete tree_;
  size_ = 0;
}

template <class Key, class T, class Compare, class Alloc>
map<Key, T, Compare, Alloc>& map<Key, T, Compare, Alloc>::operator=(
    const map& other) {
  if (this != &other) {
    tree_->CleanTree();
    *tree_ = *(other.tree_);
    size_ = other.size_;
  }
  return *this;
}

template <class Key, class T, class Compare, class Alloc>
map<Key, T, Compare, Alloc>& map<Key, T, Compare, Alloc>::operator=(
    map&& other) noexcept {
  if (this != &other) {
    delete tree_;
    tree_ = other.tree_;
    size_ = other.size_;
    other.tree_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <class Key, class T, class Compare, class Alloc>
map<Key, T, Compare, Alloc>& map<Key, T, Compare, Alloc>::operator=(
    std::initializer_list<
        typename map<Key, T, Compare, Alloc>::value_type> const& items) {
  for (const auto& item : items) {
    insert(item);
  }
  size_ = tree_->Size();
  return *this;
}

template <class Key, class T, class Compare, class Alloc>
bool map<Key, T, Compare, Alloc>::operator==(const map& other) {
  if (this == &other) return true;
  return *tree_ == *other.tree_;
}

template <class Key, class T, class Compare, class Alloc>
bool map<Key, T, Compare, Alloc>::operator!=(const map& other) {
  return !(*this == other);
}

template <class Key, class T, class Compare, class Alloc>
std::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>
map<Key, T, Compare, Alloc>::insert(const_reference value) {
  auto it_bool = tree_->InsertInMap(value);
  if (!it_bool.second) size_++;
  return it_bool;
}

template <class Key, class T, class Compare, class Alloc>
std::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>
map<Key, T, Compare, Alloc>::insert(const key_type& key,
                                    const mapped_type& value) {
  auto it_bool = tree_->InsertInMap({key, value});
  if (!it_bool.second) size_++;
  return it_bool;
}

template <class Key, class T, class Compare, class Alloc>
std::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>
map<Key, T, Compare, Alloc>::insert_or_assign(const_reference value) {
  auto res_it_bool = tree_->InsertOrAssign(value);
  if (!res_it_bool.second) size_++;
  return res_it_bool;
}

template <class Key, class T, class Compare, class Alloc>
std::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>
map<Key, T, Compare, Alloc>::insert_or_assign(const key_type& key,
                                              const mapped_type& value) {
  auto res_it_bool = tree_->InsertOrAssign({key, value});
  if (!res_it_bool.second) size_++;
  return res_it_bool;
}

template <class Key, class T, class Compare, class Alloc>
T& map<Key, T, Compare, Alloc>::at(const key_type& key) {
  return find(key)->second;
}

template <class Key, class T, class Compare, class Alloc>
const T& map<Key, T, Compare, Alloc>::at(const key_type& key) const noexcept {
  iterator found_values = find(key);
  return found_values->second;
}

template <class Key, class T, class Compare, class Alloc>
T& map<Key, T, Compare, Alloc>::operator[](const key_type& key) {
  return at(key);
}

template <class Key, class T, class Compare, class Alloc>
typename map<Key, T, Compare, Alloc>::iterator
map<Key, T, Compare, Alloc>::find(const key_type& key) {
  return tree_->FindInMap({key, mapped_type{}}).first;
}

template <class Key, class T, class Compare, class Alloc>
typename map<Key, T, Compare, Alloc>::const_iterator
map<Key, T, Compare, Alloc>::find(const key_type& key) const {
  return tree_->FindInMap({key, mapped_type{}}).first;
}

template <class Key, class T, class Compare, class Alloc>
typename map<Key, T, Compare, Alloc>::iterator
map<Key, T, Compare, Alloc>::begin() {
  return tree_->Begin();
}

template <class Key, class T, class Compare, class Alloc>
typename map<Key, T, Compare, Alloc>::iterator
map<Key, T, Compare, Alloc>::end() {
  return tree_->End();
}

template <class Key, class T, class Compare, class Alloc>
typename map<Key, T, Compare, Alloc>::const_iterator
map<Key, T, Compare, Alloc>::cbegin() const {
  return tree_->CBegin();
}

template <class Key, class T, class Compare, class Alloc>
typename map<Key, T, Compare, Alloc>::const_iterator
map<Key, T, Compare, Alloc>::cend() const {
  return tree_->CEnd();
}

template <class Key, class T, class Compare, class Alloc>
bool map<Key, T, Compare, Alloc>::empty() const noexcept {
  return tree_->Empty();
}

template <class Key, class T, class Compare, class Alloc>
std::size_t map<Key, T, Compare, Alloc>::size() const noexcept {
  return size_;
}

template <class Key, class T, class Compare, class Alloc>
std::size_t map<Key, T, Compare, Alloc>::max_size() const noexcept {
  return tree_->MaxSize();
}

template <class Key, class T, class Compare, class Alloc>
std::size_t map<Key, T, Compare, Alloc>::count(
    const key_type& key) const noexcept {
  return find(key) != cend();
}

template <class Key, class T, class Compare, class Alloc>
void map<Key, T, Compare, Alloc>::clear() {
  tree_->CleanTree();
}

template <class Key, class T, class Compare, class Alloc>
void map<Key, T, Compare, Alloc>::merge(map<Key, T, Compare, Alloc>& other) {
  tree_->Merge(*other.tree_);
  size_ = tree_->Size();
}

template <class Key, class T, class Compare, class Alloc>
void map<Key, T, Compare, Alloc>::swap(map& other) noexcept {
  if (this != &other) {
    std::swap(tree_, other.tree_);
    std::swap(size_, other.size_);
  }
}

template <class Key, class T, class Compare, class Alloc>
void map<Key, T, Compare, Alloc>::erase(iterator pos) {
  tree_->Erase(pos);
  size_--;
}

template <class Key, class T, class Compare, class Alloc>
bool map<Key, T, Compare, Alloc>::erase(const key_type& key) {
  bool result = tree_->EraseInMap({key, mapped_type{}});
  if (result) size_--;
  return result;
}

template <class Key, class T, class Compare, class Alloc>
bool map<Key, T, Compare, Alloc>::contains(const key_type& key) const {
  return (find(key) != cend());
}

template <class Key, class T, class Compare, class Alloc>
template <class... Args>
std::vector<std::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>>
map<Key, T, Compare, Alloc>::insert_many(Args&&... args) {
  std::vector<std::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>>
      result;
  for (const auto& arg : {args...}) {
    result.push_back(insert(arg));
  }
  return result;
}

}  // namespace s21