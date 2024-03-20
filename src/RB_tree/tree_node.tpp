#include "RB_tree.h"

namespace s21 {
template <typename Value, typename Compare>
struct RB_tree<Value, Compare>::TreeNode_ {
  using value_type = Value;
  using node_pointer = TreeNode_*;
  value_type data_;
  node_pointer parent_;
  node_pointer left_;
  node_pointer right_;
  // Red - 0 Black - 1
  bool color_;

  TreeNode_()
      : data_(value_type()),
        parent_(nullptr),
        left_(nullptr),
        right_(nullptr),
        color_(RedN) {}

  TreeNode_(const value_type& data)
      : data_(data),
        parent_(nullptr),
        left_(nullptr),
        right_(nullptr),
        color_(RedN) {}
  explicit TreeNode_(const TreeNode_& other)
      : data_(other.data_),
        parent_(other.parent_),
        left_(other.left_),
        right_(other.right_),
        color_(other.color_) {}

  explicit TreeNode_(TreeNode_&& other)
      : data_(std::move(other.data_)),
        parent_(std::move(other.parent_)),
        left_(std::move(other.left_)),
        right_(std::move(other.right_)),
        color_(std::move(other.color_)) {}

  node_pointer NextNode() const noexcept {
    node_pointer next = const_cast<node_pointer>(this);
    if (!next->NextIsN_null(2)) {
      next = next->right_;
      while (!next->NextIsN_null(1)) next = next->left_;
    } else if (next->NextIsN_null(2) && !next->NextIsN_null(0)) {
      while (!next->NextIsN_null(0) && next != next->parent_->left_) {
        next = next->parent_;
      }
      next = next->parent_;
    } else {
      next = next->parent_;
    }
    return next;
  }

  node_pointer PrevNode() const noexcept {
    node_pointer prev = const_cast<node_pointer>(this);
    if (!prev->NextIsN_null(1)) {
      prev = prev->left_;
      while (!prev->NextIsN_null(2)) prev = prev->right_;
    } else if (prev->NextIsN_null(1) && !prev->NextIsN_null(0)) {
      while (!prev->NextIsN_null(0) && prev != prev->parent_->right_) {
        prev = prev->parent_;
      }
      prev = prev->parent_;
    } else {
      prev = prev->parent_;
    }
    return prev;
  }

  // изменить цвет определенной ноды
  void SwitchNodeColor() noexcept { color_ = !color_; }
  /// int next 0 - parent; 1 - left; 2 - right;
  /// @return 0 - следущая нода не n_null; 1 - следущая нода n_null;
  bool NextIsN_null(int next) noexcept {
    if (!next) {
      return this->parent_ == this->parent_->right_;
    } else if (next == 1) {
      return this->left_ == this->left_->right_;
    } else if (next == 2) {
      return this->right_ == this->right_->right_;
    }
    return false;
  }
};
}  // namespace s21