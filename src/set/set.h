#ifndef CPP2_S21_CONTAINERS_S21_SET_H_
#define CPP2_S21_CONTAINERS_S21_SET_H_

#include "../RB_tree/RB_tree.h"

namespace s21 {
template <typename Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, char>>>
class set {
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using tree_type = RB_tree<value_type>;
  using iterator = typename tree_type::template Iterator<false>;
  using const_iterator = typename tree_type::template Iterator<true>;

 public:
  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &other);
  set(set &&other);
  ~set();

  set &operator=(set &&other);
  set operator=(const set &other);

  bool operator==(const set &other);
  bool operator!=(const set &other);

  bool empty();
  size_type size();
  size_type max_size();

  std::pair<iterator, bool> insert(const value_type &value);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...items);

  void erase(iterator pos);
  bool erase(const value_type &key);
  void clear();

  void swap(set &other);
  void merge(set &other);

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  iterator find(const Key &key);
  bool contains(const Key &key);

  bool RedAlert();  // проверка красных пар child-parent
  bool BLM();  // проверка одинаковости черных высот
  void PrintTree() { tree_->PrintTree(); }
  void PrintTreeRecursive() { tree_->PrintTreeRecursive(); }
  void FullNodeInfo(const Key &key) { tree_->FullNodeInfo(tree_->Find(key)); }

 private:
  tree_type *tree_;
  size_type size_;
};  // class set
}  // namespace s21

#include "set.tpp"
#endif  // CPP2_S21_CONTAINERS_S21_SET_H_
