#ifndef CPP2_S21_CONTAINERS_2_STACK_H__
#define CPP2_S21_CONTAINERS_2_STACK_H__

#include "mystack.h"

namespace s21 {

template <typename T, typename Container = s21::myStack<T>>
class stack {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  stack() : cont_() {}

  stack(std::initializer_list<value_type> const& items) : cont_{items} {}

  stack(const stack& other) : cont_(other.cont_) {}

  stack(stack&& other) : cont_(std::move(other.cont_)) {}

  stack& operator=(const stack& other) {
    cont_ = other.cont_;
    return *this;
  };

  stack& operator=(stack&& other) {
    cont_ = std::move(other.cont_);
    return *this;
  };

  ~stack() = default;

  void push(const_reference data) noexcept { cont_.push_back(data); }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    (..., cont_.push_back(args));
  }

  template <class... Args>  // вызывает конструктор элемента и создает обьект
                            // внутри себя
  void emplace(Args&&... args) {
    cont_.emplace_back(std::forward<Args>(args)...);
  }

  inline void pop() noexcept { cont_.pop_back(); };

  inline const_reference top() noexcept { return cont_.back(); }

  void swap(stack& other) noexcept { std::swap(cont_, other.cont_); }

  inline bool empty() noexcept { return cont_.empty(); }

  inline size_type size() noexcept { return cont_.size(); }

 private:
  Container cont_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_STACK_H__
