#ifndef __CPP2_S21_CONTAINERS_2_SRC_RB_TREE__
#define __CPP2_S21_CONTAINERS_2_SRC_RB_TREE__

#include <limits.h>
#include <math.h>
#include <stddef.h>

#include <functional>
#include <initializer_list>
#include <iostream>
#include <vector>

namespace s21 {

enum NodeColor { RedN, BlackN };

template <typename Value, typename Compare = std::less<Value>>
class RB_tree {
  struct TreeNode_;

 public:
  template <bool Const>
  class Iterator;

  using value_type = Value;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;
  using tree_node_ = TreeNode_;
  using node_pointer = tree_node_*;

  RB_tree();
  RB_tree(const RB_tree& other);
  RB_tree(RB_tree&& other) noexcept;
  ~RB_tree();

  RB_tree& operator=(RB_tree&& other);
  RB_tree operator=(const RB_tree& other);

  bool operator==(const RB_tree& other);
  bool operator!=(const RB_tree& other);

  void Merge(RB_tree& other);
  void Swap(RB_tree& other);

  std::pair<iterator, bool> InsertUniq(const value_type& key);
  iterator Insert(const value_type& key);

  std::pair<iterator, bool> InsertInMap(const value_type& key);
  std::pair<iterator, bool> InsertOrAssign(const value_type& key);

  bool Erase(const value_type& key);
  void Erase(iterator it);
  bool EraseInMap(const value_type& key);

  void CleanTree();

  bool Empty() const noexcept;
  size_type Size() const noexcept;
  size_type MaxSize() const noexcept;

  bool Contains(const value_type& key) noexcept;
  iterator Find(const value_type& key) noexcept;
  const_iterator Find(const value_type& key) const noexcept;
  std::pair<iterator, bool> FindInMap(const value_type& key) const noexcept;

  std::pair<iterator, iterator> EqualRange(const value_type& key);
  iterator LowerBound(const value_type& key);
  iterator UpperBound(const value_type& key);

  inline iterator Begin() const noexcept;
  inline const_iterator CBegin() const noexcept;
  inline iterator End() const noexcept;
  inline const_iterator CEnd() const noexcept;

  // 1 -  если дельта черной высоты между ветками = 0; 0 - если высота между
  // ветками не равна
  bool CheckBlackHeight() const noexcept;
  // 1 - если есть пара сын-отец красные, 0 - если все хорошо
  bool HasRedFamily() const;

  void PrintTree() const;
  void PrintTreeRecursive() const;
  void PrintMapRecursive() const;

 private:
  node_pointer root_;
  node_pointer n_null_;
  size_type size_;
  Compare less_compare;

  /// @brief идет на лево до конца дерева
  node_pointer GoLeft() const noexcept;
  /// @brief идет на право до конца дерева
  node_pointer GoRight() const noexcept;
  node_pointer InitNode();
  node_pointer InitNode(const value_type& key);
  void Init_n_nul();

  /// @return возвращает ноду с одинаковым Key, если не нашел - предпоследнюю, и
  /// bool = 1 если был равный key
  std::pair<node_pointer, bool> FindEqData(
      const value_type& first) const noexcept;

  /// @param  L_R 0 - left 1 - right
  void SmallRotate(node_pointer node, bool L_R) noexcept;
  /// @param  L_R 0 - left 1 - right
  void BigRotate(node_pointer node, bool L_R) noexcept;
  // Вставляет элемент(пару) в позицию за key_position
  node_pointer InsertAll(const value_type& key, node_pointer key_position);
  void FindLessPositionForDuplicate(const value_type& key, node_pointer node,
                                    node_pointer new_node) noexcept;
  void BalanceAfterInsert(node_pointer node) noexcept;
  void TranferNode(node_pointer deleted_node,
                   node_pointer inserted_node) noexcept;
  void DeleteTreeRecursive(node_pointer node);

  void DeleteNode(node_pointer node);
  node_pointer FindNodeToMove(node_pointer node) noexcept;
  void BalanceAfterDelete(node_pointer node) noexcept;
  void LeftRotate(node_pointer node);
  void RightRotate(node_pointer node);
  // Рекурсивно копирует дерево;
  void CopyTree(const RB_tree& other);
  node_pointer CopyNodeRecursive(const node_pointer& other_node,
                                 const node_pointer& other_n_null);
  node_pointer MergeTreeRecursive(const node_pointer& other_node,
                                  const node_pointer& other_n_null);

  /// @brief Сравнивает позицию checked относительно от checked.parent и на
  /// место checked ставит insert
  void LeftOrRight(node_pointer checked, node_pointer insert) noexcept;
  node_pointer GetUncle(node_pointer node) noexcept;
  node_pointer GetGrandparent(node_pointer node) noexcept;
  node_pointer GetSibling(node_pointer* node) noexcept;
  inline bool IsRed(node_pointer node) noexcept { return node->color_ == RedN; }
  inline bool IsBlack(node_pointer node) noexcept {
    return node->color_ == BlackN;
  }

  // Рекурсивная вспомогательная функция для проверки
  bool CheckRedFamily(node_pointer node, bool alert) const noexcept;

  int FindMinBlackHeight(node_pointer node, int currentHeight) const;
  int FindMaxBlackHeight(node_pointer node, int currentHeight) const;

  void PrintTreeRecursive(iterator it, int depth) const;
  void PrintMapRecursive(iterator it, int depth) const;

};  // class RB_tree

template <typename Value, typename Compare>
template <bool Const>
class RB_tree<Value, Compare>::Iterator {
  using value_type = RB_tree::value_type;
  using reference = std::conditional_t<Const, const value_type&, value_type&>;
  using pointer = std::conditional_t<Const, const value_type*, value_type*>;

 public:
  Iterator() = delete;
  explicit Iterator(node_pointer node) : node_(node) {}
  ~Iterator() = default;

  Iterator& operator++() noexcept;
  Iterator& operator--() noexcept;
  Iterator operator++(int) noexcept;
  Iterator operator--(int) noexcept;

  inline bool operator==(const Iterator& other) const;
  inline bool operator!=(const Iterator& other) const;

  reference operator*() const { return node_->data_; }

  pointer operator->() { return &node_->data_; }

  operator Iterator<true>() { return Iterator<true>(node_); }

  friend class RB_tree;

 private:
  node_pointer node_;
};  // class Iterator
}  // namespace s21

#include "RB_tree.tpp"
#include "common_func.tpp"
#include "iterator_bool.tpp"
#include "tree_node.tpp"
#endif  // __CPP2_S21_CONTAINERS_2_SRC_RB_TREE__
