#pragma once
#include "CCircuitalBuffer.h"

template<typename T>
class CCircuitalBufferExt : public CCircuitalBuffer<T> {
 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;
  using Base = CCircuitalBuffer<T>;
  using Iterator = typename Base::Iterator;

  explicit CCircuitalBufferExt(size_t size) : CCircuitalBuffer<T>(size) {};
  explicit CCircuitalBufferExt(size_t size, T x)  : CCircuitalBuffer<T>(size, x) {};
  explicit CCircuitalBufferExt(Iterator i, Iterator j) : CCircuitalBuffer<T>(i, j) {};
  CCircuitalBufferExt(std::initializer_list<T> init_list) : CCircuitalBuffer<T>(init_list) {}
  CCircuitalBufferExt() : CCircuitalBuffer<T>() {};
  CCircuitalBufferExt(const CCircuitalBufferExt<T> &other) : CCircuitalBuffer<T>(other) {};
  ~CCircuitalBufferExt() {};
  void move(Iterator p, size_t len);


  void resize(size_t new_size);
  void add_back(const T &a) override;
  void add_front(const T &a) override;
  void add(Iterator p, size_t len, T t) override;
  void insert(Iterator p, size_t len, T t);
  void insert(Iterator p, T t);
  void insert(Iterator p, Iterator i, Iterator j) override;
  void insert(Iterator p, std::initializer_list<T> init_list) override;
};











