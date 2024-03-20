#ifndef CPP2_S21_CONTAINERS_MAP_MAP_H_
#define CPP2_S21_CONTAINERS_MAP_MAP_H_

#include "../RB_tree/RB_tree.h"

namespace s21 {

template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<std::pair<const Key, T>>>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  template <typename C>
  class CustomComparator {
   public:
    bool operator()(const C &lhs, const C &rhs) const noexcept {
      return lhs.first < rhs.first;
    }
  };

  using compare = CustomComparator<value_type>;
  using tree_type = RB_tree<value_type, CustomComparator<value_type>>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

 public:
  map();
  map(const map &other);
  map(map &&other) noexcept;
  map(std::initializer_list<value_type> const &items);
  ~map();

  map &operator=(const map &other);
  map &operator=(map &&other) noexcept;
  map &operator=(std::initializer_list<value_type> const &items);
  bool operator==(const map &other);
  bool operator!=(const map &other);

  T &at(const key_type &key);
  const T &at(const key_type &key) const noexcept;
  T &operator[](const key_type &key);
  bool contains(const key_type &key) const;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  size_type count(const key_type &key) const noexcept;

  void clear();
  std::pair<iterator, bool> insert(const_reference value);
  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &value);
  std::pair<iterator, bool> insert_or_assign(const_reference value);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &value);
  void erase(iterator pos);
  bool erase(const key_type &key);
  void swap(map &other) noexcept;
  void merge(map &other);

  iterator find(const key_type &key);
  const_iterator find(const key_type &key) const;

  // bonus part
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  void Print() { tree_->PrintMapRecursive(); }

 private:
  tree_type *tree_;
  size_type size_;
};
}  // namespace s21

#include "map.tpp"

#endif  // CPP2_S21_CONTAINERS_MAP_MAP_H_