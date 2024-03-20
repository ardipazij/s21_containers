#ifndef CPP2_S21_CONTAINERS_2_VECTOR_H
#define CPP2_S21_CONTAINERS_2_VECTOR_H

namespace s21 {
template <typename T>
class vector {
 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;

  // Vector Member functions
  vector()
      : array(nullptr), sizeUserContainerVector(0), sizeAllocatedMemory(0){};
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v) noexcept;
  vector(vector&& v) noexcept;
  ~vector() { delete[] array; };
  vector& operator=(vector&& v);

  // Iterator
  template <bool Const>
  class Iterator {
   public:
    friend class vector;
    friend class Iterator<!Const>;

    Iterator() noexcept : iterator_pointer(nullptr) {}
    explicit Iterator(value_type* ptr) noexcept : iterator_pointer(ptr) {}
    Iterator(const Iterator& other_iterator) noexcept {
      iterator_pointer = other_iterator.iterator_pointer;
    }
    Iterator(const Iterator&& other_iterator) noexcept {
      if (this != &other_iterator) {
        iterator_pointer = std::move(other_iterator.iterator_pointer);
        this->iterator_pointer = nullptr;
      }
    }

    ~Iterator() = default;

    Iterator& operator=(const Iterator& other_iterator) noexcept {
      if (&other_iterator != this)
        iterator_pointer = other_iterator.iterator_pointer;
      return *this;
    }

    Iterator& operator++() {
      ++iterator_pointer;
      return *this;
    }

    Iterator& operator--() {
      --iterator_pointer;
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      (++this->iterator_pointer);
      return temp;
    }

    Iterator operator--(int) {
      Iterator temp = *this;
      (--this->iterator_pointer);
      return temp;
    }

    Iterator operator+(long unsigned int value) {
      iterator_pointer = iterator_pointer + value;
      return *this;
    }

    Iterator operator-(const size_type value) {
      iterator_pointer = iterator_pointer - value;
      return *this;
    }

    value_type& operator*() const { return *iterator_pointer; }
    value_type* operator->() const { return iterator_pointer; }

    // Поддержка сравнения типов iterator и const_iterator
    template <bool R>
    bool operator==(const Iterator<R>& other) const {
      return this->iterator_pointer == other.iterator_pointer;
    }

    template <bool R>
    bool operator!=(const Iterator<R>& other) const {
      return this->iterator_pointer != other.iterator_pointer;
    }

    template <bool R>
    bool operator<(const Iterator<R>& other) const {
      return this->iterator_pointer < other.iterator_pointer;
    }

    template <bool R>
    bool operator>(const Iterator<R>& other) const {
      return this->iterator_pointer > other.iterator_pointer;
    }

    template <bool R>
    bool operator<=(const Iterator<R>& other) const {
      return this->iterator_pointer <= other.iterator_pointer;
    }

    template <bool R>
    bool operator>=(const Iterator<R>& other) const {
      return this->iterator_pointer >= other.iterator_pointer;
    }

    // Поддержка неявного преобразования iterator в const_iterator
    operator Iterator<true>() const { return Iterator<true>{iterator_pointer}; }

   private:
    friend class vector;
    value_type* iterator_pointer = nullptr;
  };

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;

  // Vector Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T* data() noexcept;

  // Vector Iterators
  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

  // Vector Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  // Vector Modifiers
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  iterator insertConst(const_iterator pos, const_reference value);

  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  // Help
  void printUserVector() noexcept;
  void printUserVectorValueAndAddress() noexcept;
  value_type* getPointerBegin() noexcept;
  void ShiftLeft(size_t pos, const_reference value) noexcept;

  // DLC
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  value_type* array{nullptr};
  size_t sizeUserContainerVector{0};
  size_t sizeAllocatedMemory{0};
};
}  // namespace s21

#include "vector.tpp"
#endif  // CPP2_S21_CONTAINERS_2_VECTOR_H
