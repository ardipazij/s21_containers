#ifndef CPP2_S21_CONTAINERS_QUEUE_QUEUE_H_
#define CPP2_S21_CONTAINERS_QUEUE_QUEUE_H_

#include "../list/list.h"
namespace s21 {
template <typename T, class Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  queue() = default;

  queue(std::initializer_list<value_type> const &items) : cont_{items} {}

  queue(const queue &other) : cont_(other.cont_) {}

  queue(queue &&other) : cont_{std::move(other.cont_)} {}

  ~queue() = default;

  queue &operator=(const queue &other) {
    cont_ = other.cont_;
    return *this;
  }

  queue &operator=(queue &&other) {
    cont_ = std::move(other.cont_);
    return *this;
  }

  reference front() { return *cont_.begin(); }

  const_reference front() const { return *cont_.cbegin(); }

  reference back() { return *(--cont_.end()); }

  const_reference back() const { return *(--cont_.cend()); }

  void push(const_reference value) { cont_.push_back(value); }

  void pop() { cont_.pop_front(); }

  void swap(queue &other) { cont_.swap(other.cont_); }

  [[nodiscard]] bool empty() const { return cont_.empty(); }

  [[nodiscard]] size_type size() const { return cont_.size(); }

  template <typename... Args>
  void insert_many_back(Args &&...arguments) {
    cont_.insert_many_back(arguments...);
  }

 private:
  Container cont_{};
};
}  // namespace s21
#endif