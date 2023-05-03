#include "CCircuitalBuffer.h"
#include <memory>
#include <iostream>

// region ITERATOR

// region ITERATOR CREATE DESTROY

template<typename T>
void CCircuitalBuffer<T>::Iterator::WriteIteratorEnds(Iterator &begin, Iterator &end) {
  iterator_begin_ = &begin;
  iterator_end_ = &end;
}

template<typename T>
CCircuitalBuffer<T>::Iterator::Iterator(T *ptr) : ptr_(ptr), iterator_begin_(nullptr), iterator_end_(nullptr) {}

template<typename T>
CCircuitalBuffer<T>::Iterator::Iterator(T *ptr, Iterator *iterator_begin, Iterator *iterator_end)
    : ptr_(ptr), iterator_begin_(iterator_begin), iterator_end_(iterator_end) {}

template<typename T>
CCircuitalBuffer<T>::Iterator::Iterator() : ptr_(nullptr) {}

template<typename T>
CCircuitalBuffer<T>::Iterator::Iterator(const CCircuitalBuffer::Iterator &other) {
  *this = (Iterator(other.ptr_, other.iterator_begin_, other.iterator_end_));
}

// endregion

// region POINTERS

template<typename T>
T *CCircuitalBuffer<T>::Iterator::GetPointer() const {
  return this->ptr_;
}

template<typename T>
T &CCircuitalBuffer<T>::Iterator::operator*() const {
  return *ptr_;
}

// endregion

//region PLUS

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator+(size_t n) {
  if (!iterator_begin_ || !iterator_end_ || !iterator_begin_->ptr_ || !iterator_end_->ptr_) {
    Iterator tmp(ptr_ + n);
    return tmp;
  }
  int len = iterator_end_->ptr_ - iterator_begin_->ptr_;
  T *new_end = iterator_begin_->ptr_ + (len + n + (ptr_ - iterator_begin_->ptr_) % len) % len;

  Iterator tmp = *this;

  tmp.ptr_ = new_end;
  return tmp;
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator+=(size_t n) {
  Iterator tmp = *this + n;
  *this = tmp;
  return *this;
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator++() {
  *this += 1;
  return *this;
}

template<typename T>
const typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator++(int) {
  Iterator tmp = *this;
  *this += 1;
  return tmp;
}

//endregion

//region MINUS

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator-(size_t n) {
  Iterator tmp(*this + (-n));
  return tmp;
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator-=(size_t n) {
  *this = *this - n;
  return *this;
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator--() {
  *this -= 1;
  return *this;
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator--(int) {
  *this -= 1;
  return *this + 1;
}

template<typename T>
size_t CCircuitalBuffer<T>::Iterator::operator-(CCircuitalBuffer::Iterator other) const {
  return ptr_ - other.ptr_;
}
//endregion

//region COMPARISON

template<typename T>
typename CCircuitalBuffer<T>::Iterator &CCircuitalBuffer<T>::Iterator::operator=(const CCircuitalBuffer::Iterator &other) {
  if (this == &other) {
    return *this;
  }
  this->iterator_end_ = other.iterator_end_;
  this->iterator_begin_ = other.iterator_begin_;
  this->ptr_ = other.ptr_;
  return *this;
}

template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator==(const CCircuitalBuffer::Iterator &other) const {
  return ptr_ == other.ptr_;
}

template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator!=(const CCircuitalBuffer::Iterator &other) const {
  return !(*this == other);
}

template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator>(const CCircuitalBuffer::Iterator &other) const {
  return ptr_ > other.ptr_;
}

template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator<(const CCircuitalBuffer::Iterator &other) const {
  return ptr_ < other.ptr_;
}

template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator>=(const CCircuitalBuffer::Iterator &other) const {
  return !(*this < other);
}

template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator<=(const CCircuitalBuffer::Iterator &other) const {
  return !(*this > other);
}
//endregion

template<typename T>
void CCircuitalBuffer<T>::Iterator::swap(CCircuitalBuffer::Iterator &other) {
  Iterator *tmp_begin_ = other.iterator_begin_;
  Iterator *tmp_end_ = other.iterator_end_;
  T *tmp_ptr_ = other.ptr_;
  other.iterator_begin_ = this->iterator_begin_;
  this->iterator_begin_ = tmp_begin_;

  other.iterator_end_ = this->iterator_end_;
  this->iterator_end_ = tmp_end_;
  other.ptr_ = this->ptr_;
  this->ptr_ = tmp_ptr_;
}

// endregion

// region BUFFER

// region BUFFER CREATE DESTROY

template<typename T>
void CCircuitalBuffer<T>::BufferAllocate(size_t size) {
  std::allocator<T> alloc;
  allocated_begin_ = Iterator(alloc.allocate(size + 1));
  allocated_end_ = allocated_begin_ + size + 1;
  begin_ = allocated_begin_;
  end_ = begin_;

  for (auto it = &allocated_begin_; it != &allocated_end_; it++) {
    it->iterator_begin_ = &allocated_begin_;
    it->iterator_end_ = &allocated_end_;
  }

  allocated_begin_.WriteIteratorEnds(allocated_begin_, allocated_end_);
  allocated_end_.WriteIteratorEnds(allocated_begin_, allocated_end_);
  begin_.WriteIteratorEnds(allocated_begin_, allocated_end_);
  end_.WriteIteratorEnds(allocated_begin_, allocated_end_);
}

template<typename T>
CCircuitalBuffer<T>::CCircuitalBuffer(size_t size) {
  this->BufferAllocate(size);
}

template<typename T>
CCircuitalBuffer<T>::CCircuitalBuffer(size_t size, T x) {
  this->BufferAllocate(size);
  for (; size > 0;) {
    *end_ = x;
    end_++;
    size--;
  }
}

template<typename T>
CCircuitalBuffer<T>::CCircuitalBuffer(Iterator i, Iterator j) {
  this->BufferAllocate(j - i);
  for (; i < j;) {
    *end_ = *i;
    end_++;
    i++;
  }
}

template<typename T>
CCircuitalBuffer<T>::CCircuitalBuffer(std::initializer_list<T> init_list) {
  this->BufferAllocate(init_list.size());
  for (T el : init_list) {
    *end_ = el;
    end_++;
  }
}

template<typename T>
CCircuitalBuffer<T>::CCircuitalBuffer() : CCircuitalBuffer(0) {}

template<typename T>
CCircuitalBuffer<T>::CCircuitalBuffer(const CCircuitalBuffer &other) {
  int new_size = other.allocated_size();
  *this = *(new CCircuitalBuffer<T>(new_size));
  typename CCircuitalBuffer<T>::Iterator other_it = other.cbegin();
  for (; other_it != other.cend();) {
    *end_ = *other_it;
    other_it++;
    end_++;
  }
}

template<typename T>
CCircuitalBuffer<T> &CCircuitalBuffer<T>::operator=(const CCircuitalBuffer &other) {
  this->BufferAllocate(other.allocated_size());
  typename CCircuitalBuffer<T>::Iterator other_it = other.cbegin();
  for (; other_it != other.cend();) {
    *end_ = *other_it;
    other_it++;
    end_++;
  }
  return *this;
}

template<typename T>
CCircuitalBuffer<T>::~CCircuitalBuffer() {
  this->clear();
  std::allocator<T> alloc;
  alloc.deallocate(allocated_begin_.ptr_, allocated_end_ - allocated_begin_);
}

//endregion

// region BEGIN END

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::begin() {
  return begin_;
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::end() {
  return end_;
}

template<typename T>
const typename CCircuitalBuffer<T>::Iterator &CCircuitalBuffer<T>::cbegin() const {
  return begin_;
}

template<typename T>
const typename CCircuitalBuffer<T>::Iterator &CCircuitalBuffer<T>::cend() const {
  return end_;
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::allocated_begin() {
  return allocated_begin_;
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::allocated_end() {
  return allocated_end_;
}

template<typename T>
const typename CCircuitalBuffer<T>::Iterator &CCircuitalBuffer<T>::callocated_begin() const {
  return allocated_begin_;
}

template<typename T>
const typename CCircuitalBuffer<T>::Iterator &CCircuitalBuffer<T>::callocated_end() const {
  return allocated_end_;
}

template<typename T>
T CCircuitalBuffer<T>::front() const {
  return *cbegin();
}

template<typename T>
T CCircuitalBuffer<T>::back() const {
  T tmp = *(cend().GetPointer() - 1);
  return tmp;
}

// endregion

// region SIZE

template<typename T>
bool CCircuitalBuffer<T>::empty() const {
  return (cbegin().GetPointer() == cend().GetPointer());
}

template<typename T>
size_t CCircuitalBuffer<T>::allocated_size() const {
  return this->callocated_end() - this->callocated_begin();
}

template<typename T>
size_t CCircuitalBuffer<T>::size() const {
  if (empty()) {
    return 0;
  }
  int size_ = this->cend() - this->cbegin();
  return size_ <= 0 ? allocated_size() + size_ : size_;
}

template<typename T>
size_t CCircuitalBuffer<T>::max_size() const {
  return allocated_size() - 1;
}

// endregion

// region ADDS

template<typename T>
void CCircuitalBuffer<T>::move(Iterator p, size_t len) {
  Iterator start = end_ - 1;
  Iterator end = p - 1;
  for (; start != end; start--) {
    *(start + len) = *start;
  }
}

template<typename T>
void CCircuitalBuffer<T>::add(CCircuitalBuffer::Iterator p, size_t len, T t) {
  if (size() + len > max_size()) {
    std::cerr << "Out of size" << std::endl;
    return;
  }
  move(p, len);
  for (; len > 0; p++) {
    //    p = begin_;
    *p = t;
    len--;
    end_++;
  }
}

template<typename T>
void CCircuitalBuffer<T>::insert(CCircuitalBuffer::Iterator p, size_t len, T t) {
  add(p, len, t);
}

template<typename T>
void CCircuitalBuffer<T>::insert(CCircuitalBuffer::Iterator p, T t) {
  add(p, 1, t);
}

template<typename T>
template<class... Args>
void CCircuitalBuffer<T>::emplace(CCircuitalBuffer::Iterator p, Args &&... args) {
  add(p, 1, T(std::forward<Args>(args)...));
}

template<typename T>
void CCircuitalBuffer<T>::insert(CCircuitalBuffer::Iterator p,
                                 CCircuitalBuffer::Iterator i,
                                 CCircuitalBuffer::Iterator j) {
  if (size() + (j - i) > max_size()) {
    std::cerr << "Out of size" << std::endl;
    return;
  }
  move(p, j - i);
  for (; i != j;) {
    *p = *i;
    p++;
    i++;
    end_++;
  }
}

template<typename T>
void CCircuitalBuffer<T>::insert(CCircuitalBuffer::Iterator p, std::initializer_list<T> init_list) {
  if (size() + init_list.size() > max_size()) {
    std::cerr << "Out of size" << std::endl;
    return;
  }
  move(p, init_list.size());
  for (T el : init_list) {
    *p = el;
    p++;
    end_++;
  }
}

template<typename T>
void CCircuitalBuffer<T>::assign(CCircuitalBuffer::Iterator i, CCircuitalBuffer::Iterator j) {
  this->clear();
  this->insert(begin(), i, j);
}

template<typename T>
void CCircuitalBuffer<T>::assign(std::initializer_list<T> init_list) {
  this->clear();
  this->insert(begin(), init_list);
}

template<typename T>
void CCircuitalBuffer<T>::assign(size_t n, T t) {
  this->clear();
  this->insert(begin(), n, t);
}

template<typename T>
void CCircuitalBuffer<T>::add_back(const T &a) {
  if (size() < max_size()) {
    *end_ = a;
    end_++;

  } else {
    std::cerr << "Attempt to add amount of elements, that exceeds capacity" << std::endl;
  }
}

template<typename T>
void CCircuitalBuffer<T>::push_back(const T &a) {
  add_back(a);
}

template<typename T>
template<class... Args>
void CCircuitalBuffer<T>::emplace_back(Args &&... args) {
  add_back(T(std::forward<Args>(args)...));
}

template<typename T>
void CCircuitalBuffer<T>::add_front(const T &a) {
  if (size() < max_size()) {
    begin_--;
    *begin_ = a;

  } else {
    std::cerr << "Attempt to add amount of elements, that exceeds capacity" << std::endl;
  }
}

template<typename T>
void CCircuitalBuffer<T>::push_front(const T &a) {
  add_front(a);
}

template<typename T>
template<class... Args>
void CCircuitalBuffer<T>::emplace_front(Args &&... args) {
  add_front(T(std::forward<Args>(args)...));
}

// endregion

// region POPS

template<typename T>
void CCircuitalBuffer<T>::EraseByAmount(CCircuitalBuffer::Iterator p, size_t len) {
  len = ((len + allocated_size()) % allocated_size() + allocated_size()) % allocated_size();
  Iterator start = p + len;
  Iterator end = end_;
  for (; start != end; start++) {
    *(start - len) = *start;
  }
  for (int i = 0; i < len; i++) {
    end_--;
  }

}

template<typename T>
void CCircuitalBuffer<T>::erase(CCircuitalBuffer::Iterator p) {
  EraseByAmount(p, 1);
}

template<typename T>
void CCircuitalBuffer<T>::erase(CCircuitalBuffer::Iterator i, CCircuitalBuffer::Iterator j) {
  EraseByAmount(i, j - i);
}

template<typename T>
void CCircuitalBuffer<T>::pop_back() {
  if (!empty()) {

    end_--;

    if (begin_ == end_) {
    }
  } else {
    std::cerr << "Attempt to delete an element from an empty buffer" << std::endl;
  }
}

template<typename T>
void CCircuitalBuffer<T>::pop_front() {
  if (!empty()) {

    begin_++;

    if (begin_ == end_) {
    }
  } else {
    std::cerr << "Attempt to delete an element from an empty buffer" << std::endl;
  }
}

template<typename T>
void CCircuitalBuffer<T>::clear() {
  auto it = end_;
  while (it != begin_) {
    end_ = it - 1;
    it--;
  }
}

// endregion

// region OPERATORS

template<typename T>
T CCircuitalBuffer<T>::operator[](size_t n) {
  if (n < 0 || n >= size()) {
    throw std::out_of_range("Index out of bounds");
  }
  return *(begin_ + n);
}

template<typename T>
T CCircuitalBuffer<T>::at(size_t n) {
  return (*this)[n];
}

template<typename T>
bool CCircuitalBuffer<T>::operator==(const CCircuitalBuffer &other) const {
  if (size() != other.size()) {
    return false;
  }
  typename CCircuitalBuffer<T>::Iterator it_left = cbegin();
  typename CCircuitalBuffer<T>::Iterator it_right = other.cbegin();
  for (; it_left != cend();) {
    if (*it_left != *it_right) {
      return false;
    }
    it_left++;
    it_right++;
  }
  return true;
}

template<typename T>
bool CCircuitalBuffer<T>::operator!=(const CCircuitalBuffer &other) const {
  return !(*this == other);
}

template<typename T>
std::ostream &operator<<(std::ostream &stream, const CCircuitalBuffer<T> &buffer) {
  typename CCircuitalBuffer<T>::Iterator it = buffer.cbegin();

  for (; it != buffer.cend(); it++) {
    stream << *it << ' ';
  }
  stream << std::endl;
  return stream;
}

// endregion

// endregion

