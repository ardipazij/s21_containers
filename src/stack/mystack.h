#ifndef CPP2_S21_CONTAINERS_2_MYSTACK_H__
#define CPP2_S21_CONTAINERS_2_MYSTACK_H__

namespace s21 {

template <typename T>
class myStack {
  struct StackNode_;

 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  myStack() : pnext_(nullptr), size_(0) {}

  myStack(std::initializer_list<value_type> const& items)
      : pnext_(nullptr), size_(0) {
    for (value_type item : items) {
      push_back(item);
    }
  }
  myStack(const myStack& other) : size_(0) { Copy(other); }
  myStack(myStack&& other) {
    swap(other);
    other.pnext_ = nullptr;
    other.size_ = 0;
  }
  myStack& operator=(const myStack& other) {
    if (this != &other) {
      Clear();
      Copy(other);
    }
    return *this;
  };

  myStack& operator=(myStack&& other) {
    if (this != &other && !other.empty()) {
      Clear();
      pnext_ = other.pnext_;
      size_ = other.size_;

      other.size_ = 0;
      other.pnext_ = nullptr;
    }
    return *this;
  };
  ~myStack() { Clear(); }

  inline bool empty() const noexcept { return size_ == 0 ? 1 : 0; }
  inline size_type size() const noexcept { return size_; }

  void push_back(const_reference data) noexcept {
    StackNode_* node = new StackNode_(data);
    node->pnext_ = pnext_;
    pnext_ = node;
    size_++;
  }

  template <class... Args>
  void emplace_back(Args&&... args) {  // вызывает конструктор элемента и
                                       // создает обьект внутри себя
    value_type data{std::forward<Args>(args)...};
    StackNode_* node = new StackNode_(data);
    node->pnext_ = pnext_;
    pnext_ = node;
    size_++;
  }

  inline void pop_back() noexcept {
    if (size_ != 0) {
      size_--;
      StackNode_* temp = pnext_;
      pnext_ = pnext_->pnext_;
      delete temp;
    }
  };

  inline const_reference back() noexcept { return pnext_->data_; }
  void swap(myStack& other) noexcept {
    if (this != &other) {
      std::swap(pnext_, other.pnext_);
      std::swap(size_, other.size_);
    }
  }

  bool operator==(const myStack& other) noexcept {
    return size_ == other.size_;
  };
  bool operator!=(const myStack& other) noexcept {
    return size_ != other.size_;
  };

 private:
  StackNode_* pnext_;
  size_type size_;

  struct StackNode_ {
    StackNode_* pnext_ = nullptr;
    value_type data_ = value_type();

    explicit StackNode_(value_type data = value_type(),
                        StackNode_* pnext = nullptr)
        : pnext_(pnext), data_(data) {}
  };

  void Copy(const myStack& other) {
    if (this != &other && !other.empty()) {
      myStack<value_type> reverce;
      StackNode_* temp = other.pnext_;
      while (temp) {
        reverce.push_back(temp->data_);
        temp = temp->pnext_;
      }
      while (!reverce.empty()) {
        push_back(reverce.back());
        reverce.pop_back();
      }
    }
  }

  void Clear() {
    while (!empty()) {
      pop_back();
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_MYSTACK_H__
