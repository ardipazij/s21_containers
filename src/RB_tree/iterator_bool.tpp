#include "RB_tree.h"

namespace s21 {
template <typename Value, typename Compare>
template <bool Const>
typename RB_tree<Value, Compare>::template Iterator<Const>&
RB_tree<Value, Compare>::Iterator<Const>::operator++() noexcept {
  node_ = node_->NextNode();
  return *this;
}

template <typename Value, typename Compare>
template <bool Const>
typename RB_tree<Value, Compare>::template Iterator<Const>&
RB_tree<Value, Compare>::Iterator<Const>::operator--() noexcept {
  node_ = node_->PrevNode();
  return *this;
}

template <typename Value, typename Compare>
template <bool Const>
typename RB_tree<Value, Compare>::template Iterator<Const>
RB_tree<Value, Compare>::Iterator<Const>::operator++(int) noexcept {
  Iterator temp = (*this);
  ++(*this);
  return temp;
}

template <typename Value, typename Compare>
template <bool Const>
typename RB_tree<Value, Compare>::template Iterator<Const>
RB_tree<Value, Compare>::Iterator<Const>::operator--(int) noexcept {
  Iterator temp = (*this);
  --(*this);
  return temp;
}

template <typename Value, typename Compare>
template <bool Const>
inline bool RB_tree<Value, Compare>::template Iterator<Const>::operator==(
    const Iterator& other) const {
  return node_ == other.node_;
}

template <typename Value, typename Compare>
template <bool Const>
inline bool RB_tree<Value, Compare>::template Iterator<Const>::operator!=(
    const Iterator& other) const {
  return node_ != other.node_;
}
}  // namespace s21