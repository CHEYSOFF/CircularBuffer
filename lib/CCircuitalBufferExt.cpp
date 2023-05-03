#include "CCircuitalBufferExt.h"
#include <iostream>

template<typename T>
void CCircuitalBufferExt<T>::resize(size_t tmp_size) {

    int new_size = this->size();
    while(new_size < tmp_size) {
      new_size = new_size == 0 ? 1 : new_size * 2;
    }


  int old_size = this->size();

  std::allocator<T> alloc;
  Iterator new_allocated_begin = Iterator(alloc.allocate(new_size + 1));

  Iterator it = new_allocated_begin;
  for (size_t i = 0; i < old_size; ++i) {
    *it = (this->at(i));
    it++;
  }

  for (auto it2 = &this->allocated_begin_; it2 != &this->allocated_end_; it2++) {
    it2->iterator_begin_ = &this->allocated_begin_;
    it2->iterator_end_ = &this->allocated_end_;
  }
  this->allocated_begin_ = new_allocated_begin;
  this->allocated_end_ = this->allocated_begin_ + new_size + 1;
  this->begin_ = this->allocated_begin_;
  this->end_ = this->begin_ + old_size;

  this->allocated_begin_.WriteIteratorEnds(this->allocated_begin_, this->allocated_end_);
  this->allocated_end_.WriteIteratorEnds(this->allocated_begin_, this->allocated_end_);
  this->begin_.WriteIteratorEnds(this->allocated_begin_, this->allocated_end_);
  this->end_.WriteIteratorEnds(this->allocated_begin_, this->allocated_end_);
}

template<typename T>
void CCircuitalBufferExt<T>::add_back(const T &a) {
  if(this->size() >= this->max_size()) {
    resize(this->size() + 1);
  }

  *(this->end_) = a;
  this->end_++;

}

template<typename T>
void CCircuitalBufferExt<T>::add_front(const T &a) {
  if (this->size() >= this->max_size()) {
    resize(this->size() + 1);
  }

  this->begin_--;
  *(this->begin_) = a;
}

template<typename T>
void CCircuitalBufferExt<T>::move(CCircuitalBufferExt::Iterator p, size_t len) {
  Base::move(p, len);
}

template<typename T>
void CCircuitalBufferExt<T>::add(CCircuitalBufferExt::Iterator p, size_t len, T t) {
  if (this->size() + len > this->max_size()) {
    resize(this->size() + len);
  }
  move(p, len);
  for (; len > 0; p++) {
    //    p = begin_;
    *p = t;
    len--;
    this->end_++;
  }
}

template<typename T>
void CCircuitalBufferExt<T>::insert(CCircuitalBufferExt::Iterator p, T t) {
  Base::insert(p, t);
}

template<typename T>
void CCircuitalBufferExt<T>::insert(CCircuitalBufferExt::Iterator p, size_t len, T t) {
  Base::insert(p, len, t);
}

template<typename T>
void CCircuitalBufferExt<T>::insert(CCircuitalBufferExt::Iterator p,
                                 CCircuitalBufferExt::Iterator i,
                                 CCircuitalBufferExt::Iterator j) {
  if (this->size() + (j - i) > this->max_size()) {
    resize(this->size() + (j - i));
  }
  move(p, j - i);
  for (; i != j;) {
    *p = *i;
    p++;
    i++;
    this->end_++;
  }
}

template<typename T>
void CCircuitalBufferExt<T>::insert(CCircuitalBufferExt::Iterator p, std::initializer_list<T> init_list) {
  if (this->size() + init_list.size() > this->max_size()) {
    resize(this->size() + init_list.size());
  }
  move(p, init_list.size());
  for (T el : init_list) {
    *p = el;
    p++;
    this->end_++;
  }
}
