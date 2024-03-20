#ifndef CPP2_S21_CONTAINERS_ARRAY_ARRAY_H
#define CPP2_S21_CONTAINERS_ARRAY_ARRAY_H

namespace s21 {
template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;

  using iterator = T *;
  using const_iterator = const T *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const iterator>;

 public:
  array() : size_(N){};

  array(const std::initializer_list<value_type> &items) {
    std::copy(items.begin(), items.end(), data_);
  };

  array(const array &other) : size_(other.size_) {
    std::copy(other.data_, other.data_ + N, data_);
  };

  array(array &&other) { std::move(other.data_, other.data_ + N, data_); };

  array &operator=(const array &other) {
    size_ = other.size_;
    std::copy(other.data_, other.data_ + N, data_);
    return *this;
  };

  array &operator=(array &&other) {
    size_ = other.size_;
    std::move(other.data_, other.data_ + N, data_);
    return *this;
  };

  array &operator=(std::initializer_list<value_type> const &items) {
    std::copy(items.data_, items.data_ + N, data_);
    return *this;
  };

  reference at(size_type index) {
    if (index >= size_) {
      throw std::out_of_range(
          "s21:array: reference at(index): array index out of range");
    }
    return (*this)[index];
  };
  constexpr const_reference at(size_type index) const {
    if (index >= size_) {
      throw std::out_of_range(
          "s21:array: reference at(index): array index out of range");
    }
    return (*this)[index];
  };

  reference operator[](size_type index) {
    if (index >= size_) {
      throw std::out_of_range(
          "s21:array: operator[index]: array index out of range");
    }
    return data_[index];
  };

  const_reference operator[](size_type index) const {
    if (index >= size_) {
      throw std::out_of_range(
          "s21:array: const operator[index]: array index out of range");
    }
    return data_[index];
  };

  constexpr bool operator==(const array &other) {
    if (cbegin() == other.cbegin()) {
      return true;
    }
    bool result = true;
    for (size_t i = 0; i < size_; i++) {
      if (data_[i] != other.data_[i]) {
        result = false;
        break;
      }
    }
    return result;
  };

  constexpr bool operator!=(const array &other) const {
    return !(this == &other);
  };
  constexpr const_reference front() const {
    if (empty()) {
      throw std::logic_error("s21:array: front(): array is empty");
    }
    return data_[0];
  };
  constexpr const_reference back() const {
    if (empty()) {
      throw std::logic_error("s21:array: back(): array is empty");
    }
    return data_[size_ - 1];
  };

  pointer data() { return data_; };
  const_pointer data() const { return data_; };

  iterator begin() noexcept { return &data_[0]; };
  iterator end() { return &(data_[size_]); };

  const_iterator cbegin() const { return &data_[0]; };
  const_iterator cend() const { return &(data_[size_]); };

  constexpr bool empty() const noexcept { return size_ == 0; };
  size_type size() const { return size_; };
  constexpr size_type max_size() const { return size_; };

  void swap(array &other) noexcept {
    if (this != &other) {
      std::swap_ranges(data_, data_ + size_, other.data_);
    }
  };

  void fill(const_reference value) { std::fill_n(data_, N, value); };

 private:
  size_type size_ = N ? N : 1;
  value_type data_[N] = {};
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_ARRAY_ARRAY_H