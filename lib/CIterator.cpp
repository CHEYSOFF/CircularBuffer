#include "CCircuitalBuffer.h"

template<typename T>
CCircuitalBuffer<T>::Iterator::Iterator(T *ptr) : ptr_(ptr) {}

template<typename T>
T *CCircuitalBuffer<T>::Iterator::GetPointer() {
  return this->ptr_;
}

template<typename T>
T &CCircuitalBuffer<T>::Iterator::operator*() {
  return *ptr_;
}

//region PLUS
template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator++() {
  ptr_++;
  return *this;
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator+(int n) {
  Iterator tmp = this + n;
  return tmp;
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator+=(int n) {
  ptr_ += n;
  return ptr_;
}
//endregion

//region MINUS
template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator--() {
  ptr_--;
  return *this;
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator-(int n) {
  return this + (-n);
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::Iterator::operator-=(int n) {
  return this -= n;
}

template<typename T>
int CCircuitalBuffer<T>::Iterator::operator-(CCircuitalBuffer::Iterator other) {
  return ptr_ - other->GetPointer();
}
//endregion

//region COMPARISON
template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator==(const CCircuitalBuffer::Iterator &other) {
  return ptr_ == other.ptr_;
}

template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator!=(const CCircuitalBuffer::Iterator &other) {
  return !(*this == other);
}

template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator>(const CCircuitalBuffer::Iterator &other) {
  return ptr_ > other.ptr_;
}

template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator<(const CCircuitalBuffer::Iterator &other) {
  return ptr_ < other.ptr_;
}

template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator>=(const CCircuitalBuffer::Iterator &other) {
  return !(this < other);
}

template<typename T>
bool CCircuitalBuffer<T>::Iterator::operator<=(const CCircuitalBuffer::Iterator &other) {
  return !(this > other);
}
//endregion

