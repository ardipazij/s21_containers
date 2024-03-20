#include "RB_tree.h"

namespace s21 {

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::PrintTree() const {
  int i = 1;
  for (auto it = Begin(); it != End(); it++, i++) {
    std::cout << (*it) << ' ';
  }
  std::cout << '\n';
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::PrintTreeRecursive() const {
  PrintTreeRecursive(iterator(root_), 0);
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::PrintTreeRecursive(iterator it, int depth) const {
  node_pointer node = it.node_;
  if (node == n_null_) return;

  PrintTreeRecursive(iterator(node->right_), depth + 1);

  std::cout << " d:" << depth;
  std::cout << " ";
  std::cout << std::string(depth, ' ') << node->data_ << " ";
  std::cout << " c:" << (node->color_ == 0 ? "red" : "black");
  std::cout << " ";
  std::cout << std::endl;

  PrintTreeRecursive(iterator(node->left_), depth + 1);
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::PrintMapRecursive() const {
  PrintMapRecursive(iterator(root_), 0);
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::PrintMapRecursive(iterator it, int depth) const {
  node_pointer node = it.node_;
  if (node == n_null_) return;

  PrintMapRecursive(iterator(node->right_), depth + 1);

  std::cout << " d:" << depth;
  std::cout << " ";
  std::cout << std::string(depth, ' ') << node->data_.first << " ";
  std::cout << node->data_.second << " ";
  std::cout << " c:" << (node->color_ == 0 ? "red" : "black");
  std::cout << " ";
  std::cout << std::endl;

  PrintMapRecursive(iterator(node->left_), depth + 1);
}

template <typename Value, typename Compare>
bool RB_tree<Value, Compare>::CheckBlackHeight() const noexcept {
  if (root_ == nullptr || root_ == n_null_) {
    return true;
  }
  int minBlackHeight = 0;
  int maxBlackHeight = 0;
  minBlackHeight = FindMinBlackHeight(root_, minBlackHeight);
  maxBlackHeight = FindMaxBlackHeight(root_, maxBlackHeight);

  return abs(maxBlackHeight - minBlackHeight) <= 0;
}

template <typename Value, typename Compare>
int RB_tree<Value, Compare>::FindMinBlackHeight(node_pointer node,
                                                int currentHeight) const {
  if (node == n_null_) return currentHeight;
  if (node->color_) currentHeight++;
  int leftHeight = FindMinBlackHeight(node->left_, currentHeight);
  int rightHeight = FindMinBlackHeight(node->right_, currentHeight);
  return std::min(leftHeight, rightHeight);
}

template <typename Value, typename Compare>
int RB_tree<Value, Compare>::FindMaxBlackHeight(node_pointer node,
                                                int currentHeight) const {
  if (node == n_null_) return currentHeight;
  if (node->color_) currentHeight++;
  int leftHeight = FindMinBlackHeight(node->left_, currentHeight);
  int rightHeight = FindMinBlackHeight(node->right_, currentHeight);
  return std::max(leftHeight, rightHeight);
}

template <typename Value, typename Compare>
bool RB_tree<Value, Compare>::HasRedFamily() const {
  bool alert = false;
  return CheckRedFamily(root_, alert);
}

template <typename Value, typename Compare>
bool RB_tree<Value, Compare>::CheckRedFamily(node_pointer node,
                                             bool alert) const noexcept {
  if (alert) return true;
  if (node == n_null_) return (alert = false);

  if (node->parent_ != n_null_ && node->color_ == RedN &&
      node->parent_->color_ == RedN) {
    return (alert = true);
  }

  return CheckRedFamily(node->left_, alert) ||
         CheckRedFamily(node->right_, alert);
}

}  // namespace s21