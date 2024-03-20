#ifndef CPP2_S21_CONTAINERS_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_S21_MULTISET_H_

#include "../RB_tree/RB_tree.h"

namespace s21 {
template <typename Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, char>>>
class multiset {
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using tree_type = RB_tree<value_type>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using iterator = typename tree_type::template Iterator<false>;
  using const_iterator = typename tree_type::template Iterator<true>;

 public:
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& other);
  multiset(multiset&& other);
  ~multiset();

  multiset& operator=(multiset&& other);
  multiset operator=(const multiset& other);

  bool empty();
  size_type size();
  size_type max_size();

  iterator insert(const value_type& value);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... items);

  void erase(iterator pos);
  void erase(const value_type& key);
  void clear();

  void swap(multiset& other);
  void merge(multiset& other);

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  iterator find(const Key& key);
  bool contains(const Key& key);

  iterator lower_bound(const Key& key) noexcept;
  const_iterator lower_bound(const Key& key) const noexcept;
  iterator upper_bound(const Key& key) noexcept;
  const_iterator upper_bound(const Key& key) const noexcept;
  std::pair<iterator, iterator> equal_range(const Key& key) const noexcept;
  size_t count(const Key& key) const noexcept;

  bool RedAlert();  // проверка красных пар child-parent
  bool BLM();  // проверка одинаковости черных высот
  void PrintTree() { tree_->PrintTree(); }
  void PrintTreeRecursive() { tree_->PrintTreeRecursive(); }
  void FullNodeInfo(const Key& key) { tree_->FullNodeInfo(tree_->Find(key)); }

 private:
  tree_type* tree_;
  size_type size_;
};  // class multiset
}  // namespace s21

#include "multiset.tpp"
#endif  // CPP2_S21_CONTAINERS_S21_MULTISET_H_
