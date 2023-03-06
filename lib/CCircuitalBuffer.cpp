#include "CCircuitalBuffer.h"
#include "CIterator.h"
#include <memory>

template<typename T>
CCircuitalBuffer<T>::CCircuitalBuffer(int size) {
  std::allocator<T> alloc;
  Iterator allocated_begin = Iterator(alloc.allocate(size));
  allocated_begin_ = &allocated_begin;
  allocated_end_ = allocated_begin_ + size;
  begin_ = allocated_begin_;
  end_ = begin_;
}

template<typename T>
CCircuitalBuffer<T>::~CCircuitalBuffer() {
  std::allocator<T> alloc;
  alloc.deallocate(allocated_begin_->GetPointer(), allocated_end_ - allocated_begin_);
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::begin() {
  return Iterator(begin_);
}

template<typename T>
typename CCircuitalBuffer<T>::Iterator CCircuitalBuffer<T>::end() {
  return Iterator(end_);
}
