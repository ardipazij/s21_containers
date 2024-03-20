#include "list.h"

namespace s21 {

template <typename T>
list<T>::Node::Node() {
  this->data = nullptr;
  this->prev = this->next = nullptr;
}

template <typename T>
list<T>::Node::Node(T data) {
  this->data = new T;
  *this->data = data;
  this->prev = this->next = nullptr;
}
template <typename T>
list<T>::Node::Node(const Node& other) noexcept : Node(*other.data) {
  next = other.next;
  prev = other.prev;
}

template <typename T>
list<T>::Node::Node(Node&& other) {
  data = other.data;
  next = other.next;
  prev = other.prev;
  other.data = nullptr;
  other.next = nullptr;
  other.prev = nullptr;
}

template <typename T>
typename list<T>::Node::Node& list<T>::Node::operator=(Node&& other) {
  if (*this != other) {
    data = other.data;
    next = other.next;
    prev = other.prev;
  }
}

// List Functions
template <typename value_type>
s21::list<value_type>::list(size_type n) {
  if (max_size() < n)
    throw std::out_of_range("Limit of the container is exceeded");
  for (size_t i = 0; i < n; ++i) push_front(0);
}

template <typename value_type>
s21::list<value_type>::list(std::initializer_list<value_type> const& items)
    : list() {
  if (max_size() < items.size())
    throw std::out_of_range("Limit of the container is exceeded");
  for (auto iter = items.begin(); iter != items.end(); ++iter) {
    push_back(*iter);
  }
}

template <typename value_type>
s21::list<value_type>::list(const list& l) {
  if (max_size() < l.size())
    throw std::out_of_range("Limit of the container is exceeded");
  for (auto iter = l.cbegin(); iter != l.cend(); ++iter) {
    push_back(*iter);
  }
}

template <typename value_type>
s21::list<value_type>::list(list&& l) {
  clear();
  head = l.head;
  tail = l.tail;
  end_ = l.end_;
  sizeUserContainerList = l.sizeUserContainerList;
  l.head = nullptr;
  l.tail = nullptr;
  l.end_ = nullptr;
  l.sizeUserContainerList = 0;
}

template <typename value_type>
typename s21::list<value_type>::list& s21::list<value_type>::operator=(
    list<int>&& l) {
  if (this != &l) {
    clear();
    head = l.head;
    tail = l.tail;
    end_ = l.end_;
    sizeUserContainerList = l.sizeUserContainerList;
    l.head = nullptr;
    l.tail = nullptr;
    l.end_ = nullptr;
    l.sizeUserContainerList = 0;
  }
  return *this;
}

template <typename value_type>
list<value_type>::~list() {
  this->clear();
}

// List Element access
template <typename value_type>
typename list<value_type>::const_reference s21::list<value_type>::front() {
  return *(this->head->data);
}

template <typename value_type>
typename list<value_type>::const_reference s21::list<value_type>::back() {
  // const_reference value = 0;
  return *(this->tail->data);
}

// List Iterators
template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return (empty() == true) ? end() : iterator(this->head);
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(end_);
}

// List Iterators
template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::cbegin() const {
  return (empty() == true) ? cend() : iterator(this->head);
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::cend() const {
  return iterator(end_);
}

// List Capacity
template <typename value_type>
bool list<value_type>::empty() const noexcept {
  return (sizeUserContainerList == 0) ? true : false;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() const noexcept {
  return sizeUserContainerList;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size()
    const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

// List Modifiers
template <typename value_type>
void list<value_type>::clear() noexcept {
  while (!empty()) pop_back();
  sizeUserContainerList = 0;
  delete end_;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos == this->begin()) {
    this->push_front(value);
  } else if (pos == end()) {
    this->push_back(value);
  } else {
    Node* ptr = new Node(value);
    pos.iterator_pointer->prev->next = ptr;
    ptr->prev = pos.iterator_pointer->prev;
    ptr->next = pos.iterator_pointer;
    pos.iterator_pointer->prev = ptr;
    sizeUserContainerList++;
  }
  return iterator(pos.iterator_pointer->prev);
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  if (pos == end())
    throw std::out_of_range("Limit of the container is exceeded");
  else if (pos == begin())
    pop_front();
  else if (pos == end() - 1)
    pop_back();
  else {
    --sizeUserContainerList;
    pos.iterator_pointer->next->prev = pos.iterator_pointer->prev;
    pos.iterator_pointer->prev->next = pos.iterator_pointer->next;
    delete pos.iterator_pointer->data;
    delete pos.iterator_pointer;
  }
}

template <typename value_type>
void list<value_type>::push_back(value_type data) {
  Node* ptr = new Node(data);
  ptr->prev = tail;
  if (tail != nullptr) {
    ptr->next = tail->next;
    tail->next->prev = ptr;
    tail->next = ptr;
  }
  if (head == nullptr) {
    head = ptr;
    end_->prev = ptr;
    ptr->next = end_;
  }
  tail = ptr;
  sizeUserContainerList++;
}

template <typename value_type>
void list<value_type>::pop_back() noexcept {
  if (tail == nullptr) return;

  Node* ptr = tail->prev;
  if (ptr != nullptr) {
    ptr->next = end_;
    end_->prev = ptr;
  } else {
    head = nullptr;
    end_->prev = nullptr;
  }
  sizeUserContainerList--;
  delete tail->data;
  delete tail;
  tail = ptr;
}

template <typename value_type>
void list<value_type>::push_front(value_type data) {
  Node* ptr = new Node(data);
  ptr->next = head;
  if (head != nullptr) head->prev = ptr;
  if (tail == nullptr) {
    tail = ptr;
    end_->prev = ptr;
    ptr->next = end_;
  }
  head = ptr;
  sizeUserContainerList++;
}

template <typename value_type>
void list<value_type>::pop_front() noexcept {
  if (head == nullptr) return;

  Node* ptr = head->next;
  if (head->next->data != NULL)
    ptr->prev = nullptr;
  else {
    tail = nullptr;
    end_->prev = nullptr;
  }
  sizeUserContainerList--;
  delete head->data;
  delete head;
  if (tail == nullptr) {
    head = nullptr;
  } else
    head = ptr;
}

template <typename value_type>
void list<value_type>::swap(list& other) noexcept {
  list<value_type> temp;

  while (this->sizeUserContainerList > 0) {
    temp.push_back(this->front());
    this->pop_front();
  }
  while (other.sizeUserContainerList > 0) {
    this->push_back(other.front());
    other.pop_front();
  }
  while (temp.sizeUserContainerList > 0) {
    other.push_back(temp.front());
    temp.pop_front();
  }
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list& other) {
  if (this == &other || other.sizeUserContainerList == 0) return;
  if (pos == begin())
    this->spliceBegin(pos, other);
  else if (pos == end())
    this->spliceEnd(pos, other);
  else
    this->spliceBetween(pos, other);
  if (pos == end() && sizeUserContainerList == 0) {
    head = other.head;
    tail = other.tail;
  }
  sizeUserContainerList += other.sizeUserContainerList;
  other.sizeUserContainerList = 0;
  other.spliceNullOther();
}

template <typename value_type>
void list<value_type>::spliceBegin(const_iterator pos, list& other) {
  head = other.begin().iterator_pointer;
  other.end().iterator_pointer->prev->next = pos.iterator_pointer;
  pos.iterator_pointer->prev = other.end().iterator_pointer->prev;
}

template <typename value_type>
void list<value_type>::spliceBetween(const_iterator pos, list& other) {
  pos.iterator_pointer->prev->next = other.begin().iterator_pointer;
  other.begin().iterator_pointer->prev = pos.iterator_pointer->prev;

  pos.iterator_pointer->prev = other.end().iterator_pointer->prev;
  other.end().iterator_pointer->prev->next = pos.iterator_pointer;
}

template <typename value_type>
void list<value_type>::spliceEnd(const_iterator pos, list& other) {
  tail = other.end().iterator_pointer->prev;
  pos.iterator_pointer->prev->next = other.begin().iterator_pointer;
  other.begin().iterator_pointer->prev = pos.iterator_pointer->prev;

  other.end().iterator_pointer->prev->next = pos.iterator_pointer;
  pos.iterator_pointer->prev = other.end().iterator_pointer->prev;
}

template <typename value_type>
void list<value_type>::spliceNullOther() {
  sizeUserContainerList = 0;
  head = nullptr;
  tail = nullptr;
  delete end_;
  end_ = nullptr;
}

template <typename value_type>
void s21::list<value_type>::reverse() noexcept {
  if (this->size() != 0) {
    Node* current = head;
    Node* temp = nullptr;
    Node* tempEnd = end().iterator_pointer;

    while (current != end().iterator_pointer) {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev;
    }

    temp = head;
    head = tail;
    tail = temp;

    head->prev = nullptr;

    tail->next = tempEnd;
    tempEnd->prev = tail;
  }
}

template <typename value_type>
void s21::list<value_type>::unique() {
  iterator start = begin();
  while (start.iterator_pointer->next->next != nullptr) {
    iterator temp = start;
    if (*start == *(++temp))
      erase(temp);
    else
      ++start;
  }
}

template <typename value_type>
void list<value_type>::merge(list& other) {
  if (this == &other) return;
  // size_t otherLength = other.sizeUserContainerList;
  auto itThis = begin();
  while (other.sizeUserContainerList > 0 && empty() == false) {
    auto itTOther = other.begin();
    if (*itThis < *itTOther)
      ++itThis;
    else {
      ++itThis;
      insert(itThis, *itTOther);
      other.pop_front();
      --itThis;
    }
  }
  if (empty() == true) {
    while (other.sizeUserContainerList != 0) {
      push_back(other.front());
      other.pop_front();
    }
  }
}

template <typename value_type>
void list<value_type>::sort() {
  if (sizeUserContainerList < 2) return;
  this->quicksort(begin(), --end());
}

// Help
template <typename value_type>
void list<value_type>::quicksort(iterator low, iterator high) {
  if (low == high) return;
  iterator pillarElement = this->partition(low, high);
  quicksort(low, pillarElement);
  quicksort(++pillarElement, high);
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::partition(iterator low,
                                                                iterator high) {
  long unsigned int middleLength = distance(low, high) / 2;
  auto pivot = low;
  for (; middleLength != 0; ++pivot, --middleLength)
    ;
  iterator i = low;
  iterator j = high;
  while (true) {
    while (*i.iterator_pointer->data < *pivot.iterator_pointer->data) i++;
    while (*j > *pivot) j--;
    if (*i == *j) return j;
    std::swap(i.iterator_pointer->data, j.iterator_pointer->data);
  }
}

template <typename value_type>
long unsigned int list<value_type>::distance(iterator low, iterator high) {
  int LengthBetweenIterators = 0;
  for (; low != high; low++, LengthBetweenIterators++)
    ;
  return LengthBetweenIterators;
}

template <typename value_type>
void list<value_type>::printUserList() {
  if (head == nullptr) return;
  for (iterator start = begin(); start != end(); start++)
    std::cout << *start << " ";
  std::cout << std::endl;
}
// Get
template <typename value_type>
typename list<value_type>::Node* list<value_type>::Node::getPointPrev() {
  return prev;
}

template <typename value_type>
typename list<value_type>::Node* list<value_type>::Node::getPointNext() {
  return next;
}

template <typename value_type>
typename list<value_type>::Node* list<value_type>::getPointHead() {
  return head;
}

template <typename value_type>
typename list<value_type>::Node* list<value_type>::getPointTail() {
  return tail;
}

// DLC
template <typename value_type>
template <typename... Args>
typename s21::list<value_type>::iterator s21::list<value_type>::insert_many(
    const_iterator pos, Args&&... args) {
  list<value_type> temp{std::forward<Args>(args)...};
  splice(pos, temp);
  return begin() + sizeof...(args) - 1;
}

template <typename value_type>
template <typename... Args>
void s21::list<value_type>::insert_many_back(Args&&... args) {
  insert_many(this->cend(), args...);
}

template <typename value_type>
template <typename... Args>
void s21::list<value_type>::insert_many_front(Args&&... args) {
  insert_many(this->cbegin(), args...);
}
}  // namespace s21
