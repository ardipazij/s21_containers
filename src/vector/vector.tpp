#include "vector.h"

namespace s21 {
template <typename value_type>
s21::vector<value_type>::vector(size_type n) {
  if (n > max_size())
    throw std::length_error("cannot create s21::vector larger than max_size()");
  array = new value_type[n];
  sizeAllocatedMemory = n;
  sizeUserContainerVector = n;
}

template <typename value_type>
s21::vector<value_type>::vector(std::initializer_list<value_type> const &items)
    : vector() {
  array = new value_type[items.size()];
  sizeAllocatedMemory = items.size();

  for (auto iterItems = items.begin(); iterItems < items.end(); iterItems++)
    push_back(*iterItems);
}

template <typename value_type>
s21::vector<value_type>::vector(const vector &v) noexcept
    : array(new value_type[v.sizeAllocatedMemory]),
      sizeUserContainerVector(v.sizeUserContainerVector),
      sizeAllocatedMemory(v.sizeAllocatedMemory) {
  std::copy(v.array, v.array + sizeAllocatedMemory, array);
}

template <typename value_type>
s21::vector<value_type>::vector(vector &&v) noexcept {
  if (&v != this) {
    this->sizeUserContainerVector = std::move(v.sizeUserContainerVector);
    this->sizeAllocatedMemory = std::move(v.sizeAllocatedMemory);
    this->array = std::move(v.array);
    v.array = nullptr;
  }
}

template <typename value_type>
typename s21::vector<value_type>::vector &s21::vector<value_type>::operator=(
    vector &&v) {
  if (&v != this) {
    delete array;
    array = v.array;
    sizeUserContainerVector = v.sizeUserContainerVector;
    sizeAllocatedMemory = v.sizeAllocatedMemory;
    v.array = nullptr;
    v.sizeUserContainerVector = 0;
    v.sizeAllocatedMemory = 0;
  }
  return *this;
}

// Vector Element access
template <typename value_type>
typename s21::vector<value_type>::reference s21::vector<value_type>::at(
    size_type pos) {
  if (pos >= sizeAllocatedMemory) {
    throw std::out_of_range("Limit of the container is exceeded");
  }
  return *(begin().iterator_pointer + pos);
}

template <typename value_type>
typename s21::vector<value_type>::reference s21::vector<value_type>::operator[](
    size_type pos) {
  value_type &value = *(begin().iterator_pointer + pos);
  return value;
}

template <typename value_type>
typename s21::vector<value_type>::const_reference
s21::vector<value_type>::front() {
  if (sizeAllocatedMemory == 0)
    throw std::out_of_range("Limit of the container is exceeded");
  const value_type &value = *begin().iterator_pointer;
  return value;
}

template <typename value_type>
typename s21::vector<value_type>::const_reference
s21::vector<value_type>::back() {
  if (sizeAllocatedMemory == 0)
    throw std::out_of_range("Limit of the container is exceeded");
  const value_type &value =
      *(end().iterator_pointer -
        (sizeAllocatedMemory - sizeUserContainerVector + 1));
  return value;
}

template <typename value_type>
typename s21::vector<value_type>::value_type *
s21::vector<value_type>::data() noexcept {
  return array;
}

// Vector Iterators
template <typename value_type>
typename s21::vector<value_type>::iterator s21::vector<value_type>::begin() {
  return iterator(array);
}

template <typename value_type>
typename s21::vector<value_type>::iterator s21::vector<value_type>::end() {
  return begin() + sizeUserContainerVector;
}

template <typename value_type>
typename s21::vector<value_type>::const_iterator
s21::vector<value_type>::cbegin() const {
  return iterator(array);
}

template <typename value_type>
typename s21::vector<value_type>::const_iterator s21::vector<value_type>::cend()
    const {
  return iterator(array + sizeUserContainerVector);
}

// Vector Capacity
template <typename value_type>
bool s21::vector<value_type>::empty() const noexcept {
  return (sizeUserContainerVector == 0);
}

template <typename value_type>
typename s21::vector<value_type>::size_type s21::vector<value_type>::size()
    const noexcept {
  return sizeUserContainerVector;
}

template <typename value_type>
typename s21::vector<value_type>::size_type s21::vector<value_type>::max_size()
    const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(array);
}

template <typename value_type>
void s21::vector<value_type>::reserve(size_type size) {
  if (size > max_size())
    throw std::length_error("Container size exceeds free memory");
  if (size < sizeAllocatedMemory) return;
  sizeAllocatedMemory = size;
  auto *temp = new value_type[size];
  std::copy(array, array + sizeUserContainerVector, temp);
  delete[] array;
  array = std::move(temp);
}

template <typename value_type>
typename s21::vector<value_type>::size_type s21::vector<value_type>::capacity()
    const noexcept {
  return sizeAllocatedMemory;
}

template <typename value_type>
void s21::vector<value_type>::shrink_to_fit() {
  if (sizeUserContainerVector == sizeAllocatedMemory) return;
  if (sizeUserContainerVector == 0) {
    sizeAllocatedMemory = 0;
  } else {
    sizeAllocatedMemory = sizeUserContainerVector;
    value_type *temp = new value_type[sizeUserContainerVector];
    delete[] array;
    array = temp;
  }
}

// Vector Modifiers
template <typename value_type>
void s21::vector<value_type>::clear() noexcept {
  sizeUserContainerVector = 0;
}

template <typename value_type>
typename s21::vector<value_type>::iterator s21::vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_t position = pos.iterator_pointer - begin().iterator_pointer;
  if (pos == end() - 1 || (sizeUserContainerVector + 1 > sizeAllocatedMemory))
    reserve(sizeAllocatedMemory * 2);
  if (empty() == false) {
    sizeUserContainerVector++;
    ShiftLeft(position, value);
  } else
    push_back(value);
  return begin() + position;
}

template <typename value_type>
typename s21::vector<value_type>::iterator s21::vector<value_type>::insertConst(
    const_iterator pos, const_reference value) {
  size_t position = pos.iterator_pointer - begin().iterator_pointer;
  if (empty() == false) {
    sizeUserContainerVector++;
    ShiftLeft(position, value);
  } else
    push_back(value);
  return begin() + position;
}

template <typename value_type>
void s21::vector<value_type>::ShiftLeft(size_t pos,
                                        const_reference value) noexcept {
  iterator flag = begin() + pos;
  iterator ierEnd = end() - 1;
  iterator ierPrevEnd = end() - 2;
  while (ierEnd != flag) {
    *ierEnd.iterator_pointer = *ierPrevEnd.iterator_pointer;
    --ierEnd;
    --ierPrevEnd;
  }
  *ierEnd.iterator_pointer = value;
}

template <typename value_type>
void s21::vector<value_type>::erase(iterator pos) {
  while (pos < end() - 1) {
    *pos.iterator_pointer = *(pos.iterator_pointer + 1);
    pos++;
  }
  sizeUserContainerVector--;
}

template <typename value_type>
void s21::vector<value_type>::push_back(const_reference value) {
  if (sizeAllocatedMemory == 0) {
    array = new value_type[1];
    sizeAllocatedMemory++;
  }
  if (sizeUserContainerVector == sizeAllocatedMemory)
    reserve(sizeAllocatedMemory * 2);
  *(array + sizeUserContainerVector++) = value;
}

template <typename value_type>
void s21::vector<value_type>::pop_back() {
  sizeUserContainerVector--;
}

// Help
template <typename value_type>
void s21::vector<value_type>::printUserVector() noexcept {
  std::cout << "vector { ";
  for (auto iterStart = begin(); iterStart < end(); iterStart++) {
    if (iterStart != end() - 1)
      std::cout << *iterStart << ","
                << " ";
    else
      std::cout << *iterStart << " ";
  }
  std::cout << "}" << std::endl;
}

template <typename value_type>
void s21::vector<value_type>::swap(vector &other) {
  std::swap(array, other.array);
  std::swap(sizeAllocatedMemory, other.sizeAllocatedMemory);
  std::swap(sizeUserContainerVector, other.sizeUserContainerVector);
}

template <typename value_type>
void s21::vector<value_type>::printUserVectorValueAndAddress() noexcept {
  std::cout << "vector { ";
  for (auto iterStart = begin(); iterStart < end(); iterStart++) {
    if (iterStart != (end() - 1))
      std::cout << iterStart.iterator_pointer << " = "
                << *iterStart.iterator_pointer << ","
                << " ";
    else
      std::cout << iterStart.iterator_pointer << " = "
                << *iterStart.iterator_pointer << " ";
  }
  std::cout << "}" << std::endl;
}

template <typename value_type>
value_type *s21::vector<value_type>::getPointerBegin() noexcept {
  return begin().iterator_pointer;
}

// DLC
template <typename value_type>
template <typename... Args>
typename s21::vector<value_type>::iterator s21::vector<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  if (sizeUserContainerVector + sizeof...(args) > sizeAllocatedMemory)
    throw std::out_of_range("Limit of the container is exceeded");
  vector<value_type> temp{std::forward<Args>(args)...};
  auto temp_iterator = --temp.end();

  for (int i = sizeof...(args); i != 0; --i) {
    pos = insertConst(pos, *temp_iterator);
    --temp_iterator;
  }
  return begin() + sizeof...(args) - 1;
}

template <typename value_type>
template <typename... Args>
void s21::vector<value_type>::insert_many_back(Args &&...args) {
  if (sizeUserContainerVector + sizeof...(args) > sizeAllocatedMemory)
    throw std::out_of_range("Limit of the container is exceeded");
  vector<value_type> temp{std::forward<Args>(args)...};
  auto temp_iterator = temp.begin();

  for (int i = sizeof...(args); i != 0; --i) {
    push_back(*temp_iterator);
    ++temp_iterator;
  }
}
};  // namespace s21
