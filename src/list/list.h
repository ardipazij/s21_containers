#ifndef CPP2_S21_CONTAINERS_1_S21_LIST_H
#define CPP2_S21_CONTAINERS_1_S21_LIST_H

namespace s21 {
template <typename T>
class list {
 private:
  class Node;

 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;

  // List Functions
  list(){};
  explicit list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  list& operator=(list<int>&& l);
  ~list();

  template <bool Const>
  class Iterator {
   public:
    friend class list;
    friend class Iterator<!Const>;

    Iterator() : iterator_pointer(nullptr) {}
    explicit Iterator(Node* ptr) : iterator_pointer(ptr) {}
    Iterator(const Iterator& other_iterator) {
      this->iterator_pointer = other_iterator.iterator_pointer;
    }
    Iterator(const Iterator&& other_iterator) : Iterator{other_iterator} {
      this->iterator_pointer = nullptr;
    }
    Iterator& operator=(const Iterator& other_iterator) {
      if (&other_iterator != this)
        iterator_pointer = other_iterator.iterator_pointer;
      return *this;
    }
    ~Iterator() = default;

    Iterator& operator++() {
      iterator_pointer = iterator_pointer->next;
      return *this;
    }

    Iterator& operator--() {
      iterator_pointer = iterator_pointer->prev;
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      iterator_pointer = iterator_pointer->next;
      return temp;
    }

    Iterator operator--(int) {
      Iterator temp = *this;
      iterator_pointer = iterator_pointer->prev;
      return temp;
    }

    Iterator& operator+(size_type value) {
      while (value > 0) {
        this->iterator_pointer = this->iterator_pointer->next;
        value--;
      }
      return *this;
    }

    Iterator& operator-(size_type value) {
      while (value > 0) {
        this->iterator_pointer = iterator_pointer->prev;
        value--;
      }
      return *this;
    }

    value_type& operator*() const { return *iterator_pointer->data; }
    value_type* operator->() const { return iterator_pointer->data; }

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

    // Поддержка неявного преобразования iterator в const_iterator
    operator Iterator<true>() const { return Iterator<true>{iterator_pointer}; }

   private:
    Node* iterator_pointer = nullptr;
  };

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;

  // List Element access
  const_reference front();
  const_reference back();

  // List Iterators
  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

  // List Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // List Modifiers
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(value_type data);
  void pop_back() noexcept;
  void push_front(value_type data);
  void pop_front() noexcept;
  void swap(list& other) noexcept;
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void spliceBegin(const_iterator pos, list& other);
  void spliceBetween(const_iterator pos, list& other);
  void spliceEnd(const_iterator pos, list& other);
  void spliceNullOther();
  void reverse() noexcept;
  void unique();
  void sort();

  // Help
  void quicksort(iterator low, iterator high);
  iterator partition(iterator low, iterator high);
  long unsigned int distance(iterator low, iterator high);
  void printUserList();

  // Get
  Node* getPointHead();
  Node* getPointTail();

  // DLC
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);

 private:
  class Node {
   public:
    friend class list;

    Node();
    Node(T data);
    Node(const Node& other) noexcept;
    Node(Node&& other);
    Node& operator=(Node&& other);

    // Get
    Node* getPointPrev();
    Node* getPointNext();

   private:
    T* data;
    Node *prev{nullptr}, *next{nullptr};
  };

  Node *head{nullptr}, *tail{nullptr}, *end_{new Node};
  size_type sizeUserContainerList{0};
};
}  // namespace s21
#include "list.tpp"
#endif  // CPP2_S21_CONTAINERS_1_S21_LIST_H