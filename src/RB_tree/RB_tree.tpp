#include "RB_tree.h"

namespace s21 {

struct TreeNode_;
template <bool Const>
class Iterator;

// using mapped_type = Value;
using node_pointer = TreeNode_*;
using iterator = Iterator<false>;
using const_iterator = Iterator<true>;

template <typename Value, typename Compare>
RB_tree<Value, Compare>::RB_tree() : root_(nullptr), size_(0) {
  Init_n_nul();
}
template <typename Value, typename Compare>
RB_tree<Value, Compare>::RB_tree(const RB_tree& other)
    : root_(nullptr), size_(other.size_) {
  Init_n_nul();
  CopyTree(other);
}
template <typename Value, typename Compare>
RB_tree<Value, Compare>::RB_tree(RB_tree&& other) noexcept
    : root_(nullptr), size_(other.size_) {
  this->DeleteTreeRecursive(root_);
  delete n_null_;
  root_ = other.root_;
  n_null_ = other.n_null_;
  other.root_ = nullptr;
  other.n_null_ = nullptr;
  other.size_ = 0;
}
template <typename Value, typename Compare>
RB_tree<Value, Compare>::~RB_tree() {
  DeleteTreeRecursive(root_);
  size_ = 0;
  delete n_null_;
}

template <typename Value, typename Compare>
RB_tree<Value, Compare>& RB_tree<Value, Compare>::operator=(RB_tree&& other) {
  if (this != &other) {
    DeleteTreeRecursive(root_);
    delete n_null_;
    root_ = other.root_;
    n_null_ = other.n_null_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.n_null_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename Value, typename Compare>
RB_tree<Value, Compare> RB_tree<Value, Compare>::operator=(
    const RB_tree& other) {
  if (this != &other) {
    CleanTree();
    CopyTree(other);
    size_ = other.size_;
  }
  return *this;
}

template <typename Value, typename Compare>
bool RB_tree<Value, Compare>::operator==(const RB_tree& other) {
  if (size_ != other.size_) return false;

  auto other_it = other.Begin();
  bool eq = true;
  for (auto it = Begin(); it != End() && eq; ++other_it, ++it) {
    eq = (*it == *other_it);
  }

  return eq;
}

template <typename Value, typename Compare>
bool RB_tree<Value, Compare>::operator!=(const RB_tree& other) {
  return !(*this == other);
}

template <typename Value, typename Compare>
size_t RB_tree<Value, Compare>::Size() const noexcept {
  return size_;
}

template <typename Value, typename Compare>
bool RB_tree<Value, Compare>::Empty() const noexcept {
  return size_ == 0;
}

template <typename Value, typename Compare>
size_t RB_tree<Value, Compare>::MaxSize() const noexcept {
  return ((std::numeric_limits<size_type>::max() / 2)) / sizeof(tree_node_);
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::node_pointer
RB_tree<Value, Compare>::CopyNodeRecursive(const node_pointer& other_node,
                                           const node_pointer& other_n_null) {
  if (other_node == other_n_null) return n_null_;

  node_pointer new_node = InitNode(other_node->data_);
  new_node->color_ = other_node->color_;
  new_node->left_ = CopyNodeRecursive(other_node->left_, other_n_null);
  if (new_node->left_ != n_null_) new_node->left_->parent_ = new_node;
  new_node->right_ = CopyNodeRecursive(other_node->right_, other_n_null);
  if (new_node->right_ != n_null_) new_node->right_->parent_ = new_node;

  return new_node;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::Merge(RB_tree& other_tree) {
  MergeTreeRecursive(other_tree.root_, other_tree.n_null_);
  other_tree.CleanTree();
  delete other_tree.n_null_;
  other_tree.root_ = nullptr;
  other_tree.n_null_ = nullptr;
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::node_pointer
RB_tree<Value, Compare>::MergeTreeRecursive(const node_pointer& other_node,
                                            const node_pointer& other_n_null) {
  if (other_node == other_n_null) return n_null_;

  node_pointer copy_node;
  copy_node = MergeTreeRecursive(other_node->left_, other_n_null);
  Insert(copy_node->data_);
  copy_node = MergeTreeRecursive(other_node->right_, other_n_null);

  return copy_node;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::CopyTree(const RB_tree& other) {
  DeleteTreeRecursive(root_);
  root_ = CopyNodeRecursive(other.root_, other.n_null_);
  if (root_ != n_null_) root_->parent_ = n_null_;
  n_null_->parent_ = GoRight();
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::Swap(RB_tree& other) {
  if (this != &other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    // node_pointer temp_root = root_;
    // size_type temp_size = size_;
    // root_ = other.root_;
    // size_ = other.size_;
    // other.root_ = temp_root;
    // other.size_ = temp_size;
  }
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::node_pointer RB_tree<Value, Compare>::GoLeft()
    const noexcept {
  node_pointer temp = const_cast<node_pointer>(root_);
  while (temp->left_ && temp->left_ != n_null_) {
    temp = temp->left_;
  }
  return temp;
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::node_pointer
RB_tree<Value, Compare>::GoRight() const noexcept {
  node_pointer temp = const_cast<node_pointer>(root_);
  while (temp->right_ && temp->right_ != n_null_) {
    temp = temp->right_;
  }
  return temp;
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::node_pointer
RB_tree<Value, Compare>::InitNode() {
  node_pointer new_node = new TreeNode_();
  new_node->left_ = n_null_;
  new_node->right_ = n_null_;
  new_node->parent_ = n_null_;
  return new_node;
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::node_pointer
RB_tree<Value, Compare>::InitNode(const value_type& key) {
  node_pointer new_node = new TreeNode_(key);
  new_node->left_ = n_null_;
  new_node->right_ = n_null_;
  new_node->parent_ = n_null_;

  return new_node;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::Init_n_nul() {
  n_null_ = InitNode();
  n_null_->color_ = BlackN;
  n_null_->left_ = n_null_;
  n_null_->right_ = n_null_;
}

template <typename Value, typename Compare>
std::pair<typename RB_tree<Value, Compare>::iterator, bool>
RB_tree<Value, Compare>::FindInMap(const value_type& key) const noexcept {
  node_pointer eq_node = root_;
  std::pair<iterator, bool> exit = {iterator(eq_node), true};
  if (!eq_node || eq_node == n_null_) {
    exit = {iterator(n_null_), false};
    // return iterator(n_null_);
  } else {
    while (eq_node->data_.first != key.first) {
      bool key_less = less_compare(key, eq_node->data_);
      if (!key_less && eq_node->right_ != n_null_) {
        eq_node = eq_node->right_;
      } else if (key_less && eq_node->left_ != n_null_) {
        eq_node = eq_node->left_;
      } else if ((!key_less && eq_node->right_ == n_null_) ||
                 (key_less && eq_node->left_ == n_null_) ||
                 (eq_node->right_ == n_null_ && eq_node->left_ == n_null_)) {
        exit = {iterator(eq_node), false};
        break;
      }
    }
    if (exit.second) exit.first = iterator(eq_node);
  }
  return exit;
}

// template <typename Value, typename Compare>
// std::pair<typename RB_tree<Value, Compare>::node_pointer, bool>
// RB_tree<Value, Compare>::FindEqData(const value_type& key) const noexcept {
//   node_pointer eq_node = root_;
//   std::pair<node_pointer, bool> exit = {eq_node, true};
//   if(!eq_node || eq_node == n_null_){
//     exit = std::make_pair(n_null_, false);
//   } else {
//     while (eq_node->data_ != key) {
//       bool key_less = less_compare(key, eq_node->data_);
//       if(!key_less && eq_node->right_ != n_null_) {
//         eq_node = eq_node->right_;
//       } else if(key_less && eq_node->left_!= n_null_) {
//         eq_node = eq_node->left_;
//       } else if ((!key_less && eq_node->right_ == n_null_) || (key_less &&
//       eq_node->left_ == n_null_)
//         || (eq_node->right_ == n_null_ && eq_node->left_ == n_null_)){
//         exit = {eq_node, false};
//         break;
//       }
//     }
//     if (exit.second) exit.first = eq_node;
//   }
//   return exit;
// }
template <typename Value, typename Compare>
std::pair<typename RB_tree<Value, Compare>::node_pointer, bool>
RB_tree<Value, Compare>::FindEqData(const value_type& key) const noexcept {
  node_pointer eq_node = root_;
  std::pair<node_pointer, bool> exit = {eq_node, true};
  if (!eq_node || eq_node == n_null_) {
    exit = std::make_pair(n_null_, false);
  } else {
    while (eq_node->data_ != key) {
      bool key_less = less_compare(key, eq_node->data_);
      if (!key_less && eq_node->right_ != n_null_) {
        eq_node = eq_node->right_;
      } else if (key_less && eq_node->left_ != n_null_) {
        eq_node = eq_node->left_;
      } else if ((!key_less && eq_node->right_ == n_null_) ||
                 (key_less && eq_node->left_ == n_null_) ||
                 (eq_node->right_ == n_null_ && eq_node->left_ == n_null_)) {
        exit = {eq_node, false};
        break;
      }
    }
    if (exit.second) exit.first = eq_node;
  }
  return exit;
}

// while (eq_node != n_null_) {
//   bool key_less = less_compare(key, eq_node->data_);
//   if (eq_node->left_ == n_null_ && eq_node->right_ == n_null_) {
//     exit = {temp, false};
//     break;
//   } else if(key_less){
//     temp = eq_node;
//     eq_node = eq_node->left_;
//   } else if (!key_less) {
//     temp = eq_node;
//     eq_node = eq_node->right_;
//   }
// }

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::node_pointer
RB_tree<Value, Compare>::InsertAll(const value_type& key,
                                   node_pointer key_position) {
  node_pointer new_node = InitNode(key);
  if (!root_ || root_ == n_null_) {
    root_ = new_node;
    root_->color_ = BlackN;
  } else {
    node_pointer temp = key_position;
    if (less_compare(key, temp->data_)) {
      temp->left_ = new_node;
      new_node->parent_ = temp;
    } else {
      FindLessPositionForDuplicate(key, temp, new_node);
    }
    BalanceAfterInsert(new_node);
    root_->color_ = BlackN;
  }
  size_++;
  n_null_->parent_ = GoRight();
  return new_node;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::FindLessPositionForDuplicate(
    const value_type& key, node_pointer node, node_pointer new_node) noexcept {
  node_pointer eq_node = node;

  if (!eq_node || eq_node == n_null_) {
    eq_node = n_null_;
  } else {
    while (true) {
      if (less_compare(key, eq_node->data_)) {
        if (eq_node->left_ != n_null_) {
          eq_node = eq_node->left_;
        } else {
          eq_node->left_ = new_node;
          break;
        }
      } else {
        if (eq_node->right_ != n_null_) {
          eq_node = eq_node->right_;
        } else {
          eq_node->right_ = new_node;
          break;
        }
      }
    }
    new_node->parent_ = eq_node;
  }
}

template <typename Value, typename Compare>
std::pair<typename RB_tree<Value, Compare>::iterator, bool>
RB_tree<Value, Compare>::InsertInMap(const value_type& key) {
  auto pair_it_bool = FindInMap(key);
  if (pair_it_bool.second == false)
    pair_it_bool.first = iterator(InsertAll(key, pair_it_bool.first.node_));
  return pair_it_bool;
}

template <typename Value, typename Compare>
std::pair<typename RB_tree<Value, Compare>::iterator, bool>
RB_tree<Value, Compare>::InsertOrAssign(const value_type& key) {
  auto pair_it_bool = FindInMap(key);
  if (pair_it_bool.second == false) {
    pair_it_bool.first = iterator(InsertAll(key, pair_it_bool.first.node_));
  } else {
    (pair_it_bool.first)->second = key.second;
  }
  return pair_it_bool;
}

template <typename Value, typename Compare>
std::pair<typename RB_tree<Value, Compare>::iterator, bool>
RB_tree<Value, Compare>::InsertUniq(const value_type& key) {
  std::pair<node_pointer, bool> pair = FindEqData(key);
  node_pointer node = pair.first;
  if (pair.second == false) node = InsertAll(key, pair.first);
  return {iterator(node), pair.second};
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::iterator RB_tree<Value, Compare>::Insert(
    const value_type& key) {
  node_pointer node = InsertAll(key, FindEqData(key).first);
  return iterator(node);
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::BalanceAfterInsert(node_pointer node) noexcept {
  if (IsRed(node->parent_)) {
    node_pointer parent = node->parent_;
    if (IsBlack(GetGrandparent(node))) {
      if (IsRed(GetUncle(node))) {
        GetGrandparent(node)->SwitchNodeColor();
        GetUncle(node)->SwitchNodeColor();
        parent->SwitchNodeColor();
        BalanceAfterInsert(GetGrandparent(node));
      } else {
        if (GetGrandparent(node)->left_ == parent && parent->right_ == node) {
          SmallRotate(node, 1);
          if (parent != n_null_) BalanceAfterInsert(parent);
        } else if (GetGrandparent(node)->right_ == parent &&
                   parent->left_ == node) {
          SmallRotate(node, 0);
          if (parent != n_null_) BalanceAfterInsert(parent);
        } else if (GetGrandparent(node)->left_ == parent &&
                   parent->left_ == node) {
          BigRotate(node, 1);
        } else if (GetGrandparent(node)->right_ == parent &&
                   parent->right_ == node) {
          BigRotate(node, 0);
        }
      }
    }
  }
}

template <typename Value, typename Compare>
bool RB_tree<Value, Compare>::EraseInMap(const value_type& key) {
  auto pair_it_bool = FindInMap(key);
  if (pair_it_bool.second) DeleteNode(pair_it_bool.first.node_);
  return pair_it_bool.second;
}

template <typename Value, typename Compare>
bool RB_tree<Value, Compare>::Erase(const value_type& key) {
  auto pair_node = FindEqData(key);

  if (pair_node.second) DeleteNode(pair_node.first);
  return pair_node.second;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::Erase(iterator it) {
  DeleteNode(it.node_);
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::DeleteNode(node_pointer node) {
  node = FindNodeToMove(node);

  delete node;
  node = nullptr;
  size_--;
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::node_pointer
RB_tree<Value, Compare>::FindNodeToMove(node_pointer node) noexcept {
  node_pointer prev = node->NextNode();
  // если оба листа n_null
  if (node->left_ == n_null_ && node->right_ == n_null_) {
    if (IsBlack(node)) BalanceAfterDelete(node);
    LeftOrRight(node, n_null_);
  }
  // если только один ил листов n_null
  if ((node->left_ != n_null_ && node->right_ == n_null_) ||
      (node->left_ == n_null_ && node->right_ != n_null_)) {
    if (node->left_ != n_null_) {
      LeftOrRight(node, node->left_);
      node->left_->color_ = node->color_;
    } else {
      LeftOrRight(node, node->right_);
      node->right_->color_ = node->color_;
    }
  }
  // если нода - с левым и правым сыном не n_null
  if (node->left_ != n_null_ && node->right_ != n_null_) {
    FindNodeToMove(prev);
    TranferNode(node, prev);
  }
  return node;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::TranferNode(node_pointer deleted_node,
                                          node_pointer inserted_node) noexcept {
  inserted_node->parent_ = deleted_node->parent_;
  inserted_node->right_ = deleted_node->right_;
  inserted_node->left_ = deleted_node->left_;

  inserted_node->left_->parent_ = inserted_node;
  inserted_node->right_->parent_ = inserted_node;
  LeftOrRight(deleted_node, inserted_node);
  inserted_node->color_ = deleted_node->color_;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::BalanceAfterDelete(node_pointer node) noexcept {
  node_pointer cp_node = node;
  while (cp_node != root_ && IsBlack(cp_node)) {
    bool isLeftChild = (cp_node == cp_node->parent_->left_);
    node_pointer sibling = GetSibling(&cp_node);

    if (IsRed(sibling)) {
      sibling->color_ = BlackN;
      cp_node->parent_->color_ = RedN;
      if (isLeftChild) {
        LeftRotate(cp_node->parent_);
      } else {
        RightRotate(cp_node->parent_);
      }
      sibling = GetSibling(&cp_node);
    }

    if (IsBlack(sibling->left_) && IsBlack(sibling->right_)) {
      sibling->color_ = RedN;
      cp_node = cp_node->parent_;
    } else {
      if (isLeftChild && IsBlack(sibling->right_)) {
        sibling->left_->color_ = BlackN;
        sibling->color_ = RedN;
        RightRotate(sibling);
        sibling = cp_node->parent_->right_;
      } else if (!isLeftChild && IsBlack(sibling->left_)) {
        sibling->right_->color_ = BlackN;
        sibling->color_ = RedN;
        LeftRotate(sibling);
        sibling = cp_node->parent_->left_;
      }

      sibling->color_ = cp_node->parent_->color_;
      cp_node->parent_->color_ = BlackN;
      if (isLeftChild) {
        sibling->right_->color_ = BlackN;
        LeftRotate(cp_node->parent_);
      } else {
        sibling->left_->color_ = BlackN;
        RightRotate(cp_node->parent_);
      }
      cp_node = root_;
    }
  }
  cp_node->color_ = BlackN;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::CleanTree() {
  DeleteTreeRecursive(root_);
  root_ = n_null_;
  size_ = 0;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::DeleteTreeRecursive(node_pointer node) {
  if (node && node != n_null_) {
    DeleteTreeRecursive(node->left_);
    DeleteTreeRecursive(node->right_);
    if (node->parent_ != n_null_) {
      // Если у узла есть родитель, обнуляем ссылку на этот узел у родителя
      if (node->parent_->left_ == node)
        node->parent_->left_ = n_null_;
      else if (node->parent_->right_ == node)
        node->parent_->right_ = n_null_;
    }
    delete node;
  }
}

template <typename Value, typename Compare>
bool RB_tree<Value, Compare>::Contains(const value_type& key) noexcept {
  return FindEqData(key).second;
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::iterator RB_tree<Value, Compare>::Find(
    const value_type& key) noexcept {
  std::pair<node_pointer, bool> pair = FindEqData(key);
  return (pair.second ? iterator(pair.first) : iterator(n_null_));
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::const_iterator RB_tree<Value, Compare>::Find(
    const value_type& key) const noexcept {
  std::pair<node_pointer, bool> pair = FindEqData(key);
  return (pair.second ? const_iterator(pair.first) : const_iterator(n_null_));
}

template <typename Value, typename Compare>
std::pair<typename RB_tree<Value, Compare>::iterator,
          typename RB_tree<Value, Compare>::iterator>
RB_tree<Value, Compare>::EqualRange(const value_type& key) {
  return {LowerBound(key), UpperBound(key)};
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::iterator RB_tree<Value, Compare>::LowerBound(
    const value_type& key) {
  iterator temp(FindEqData(key).first);
  iterator lower = temp;
  while ((*temp) == key) {
    lower = temp;
    --temp;
  }
  return lower;
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::iterator RB_tree<Value, Compare>::UpperBound(
    const value_type& key) {
  iterator temp(FindEqData(key).first);
  while ((*temp) == key && temp.node_ != n_null_) {
    ++temp;
  }
  return temp;
}

template <typename Value, typename Compare>
inline typename RB_tree<Value, Compare>::iterator RB_tree<Value, Compare>::End()
    const noexcept {
  return iterator(n_null_);
}

template <typename Value, typename Compare>
inline typename RB_tree<Value, Compare>::iterator
RB_tree<Value, Compare>::Begin() const noexcept {
  return iterator(GoLeft());
}

template <typename Value, typename Compare>
inline typename RB_tree<Value, Compare>::const_iterator
RB_tree<Value, Compare>::CEnd() const noexcept {
  return const_iterator(n_null_);
}

template <typename Value, typename Compare>
inline typename RB_tree<Value, Compare>::const_iterator
RB_tree<Value, Compare>::CBegin() const noexcept {
  return const_iterator(GoLeft());
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::LeftOrRight(node_pointer checked,
                                          node_pointer insert) noexcept {
  node_pointer parent = checked->parent_;
  if (checked == parent->left_) {
    parent->left_ = insert;
    insert->parent_ = parent;
  } else if (checked == parent->right_) {
    parent->right_ = insert;
    insert->parent_ = parent;
  } else if (checked == root_) {
    root_ = insert;
    insert->parent_ = n_null_;
  }
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::LeftRotate(node_pointer node) {
  node_pointer child = node->right_;
  node->right_ = child->left_;
  if (child->left_ != n_null_) {
    child->left_->parent_ = node;
  }
  child->parent_ = node->parent_;

  if (node->parent_ == n_null_) {
    root_ = child;
  } else if (node == node->parent_->left_) {
    node->parent_->left_ = child;
  } else {
    node->parent_->right_ = child;
  }
  child->left_ = node;
  node->parent_ = child;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::RightRotate(node_pointer node) {
  node_pointer child = node->left_;
  node->left_ = child->right_;
  if (child->right_ != n_null_) {
    child->right_->parent_ = node;
  }
  child->parent_ = node->parent_;

  if (node->parent_ == n_null_) {
    root_ = child;
  } else if (node == node->parent_->right_) {
    node->parent_->right_ = child;
  } else {
    node->parent_->left_ = child;
  }
  child->right_ = node;
  node->parent_ = child;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::SmallRotate(node_pointer node,
                                          bool L_R) noexcept {
  node_pointer grandparent = GetGrandparent(node);
  node_pointer parent = node->parent_;
  node_pointer n_child = L_R ? node->left_ : node->right_;
  if (grandparent != n_null_) LeftOrRight(parent, node);
  node->parent_ = grandparent;
  parent->parent_ = node;
  if (L_R) {
    parent->right_ = n_child;
    node->left_ = parent;
  } else {
    parent->left_ = n_child;
    node->right_ = parent;
  }
  if (n_child != n_null_) n_child->parent_ = parent;
  if (parent == root_) root_ = node;
}

template <typename Value, typename Compare>
void RB_tree<Value, Compare>::BigRotate(node_pointer node, bool L_R) noexcept {
  node_pointer grandparent = GetGrandparent(node);
  node_pointer parent = node->parent_;
  node_pointer grandgrandparent = grandparent->parent_;
  if (grandgrandparent != n_null_) LeftOrRight(grandparent, parent);
  parent->parent_ = grandgrandparent;
  grandparent->parent_ = parent;

  node_pointer p_child = L_R ? parent->right_ : parent->left_;
  if (p_child != n_null_) p_child->parent_ = grandparent;
  if (L_R) {
    parent->right_ = grandparent;
    grandparent->left_ = p_child;
  } else {
    parent->left_ = grandparent;
    grandparent->right_ = p_child;
  }

  if (grandparent == root_) {
    root_ = parent;
  }

  if (parent != root_) parent->SwitchNodeColor();
  if (grandparent != root_) grandparent->SwitchNodeColor();
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::node_pointer
RB_tree<Value, Compare>::GetUncle(node_pointer node) noexcept {
  if (node->parent_ == n_null_ || node->parent_->parent_ == n_null_) {
    return n_null_;  // The node does not have an uncle
  }
  if (node->parent_ == node->parent_->parent_->left_) {
    return node->parent_->parent_->right_;
  } else {
    return node->parent_->parent_->left_;
  }
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::node_pointer
RB_tree<Value, Compare>::GetGrandparent(node_pointer node) noexcept {
  if (node->parent_ == n_null_) {
    return n_null_;
  }
  return node->parent_->parent_;
}

template <typename Value, typename Compare>
typename RB_tree<Value, Compare>::node_pointer
RB_tree<Value, Compare>::GetSibling(node_pointer* node) noexcept {
  if (*node == (*node)->parent_->left_) {
    return (*node)->parent_->right_;
  } else {
    return (*node)->parent_->left_;
  }
}

}  // namespace s21
