#pragma once
#include <cstddef>
#include <ostream>

template<typename T>
class CCircuitalBuffer {
 public:

  class Iterator : public std::iterator<std::random_access_iterator_tag, T>{
   public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef T* pointer;
    typedef std::forward_iterator_tag iterator_category;
    Iterator(T *ptr);
    Iterator(T *ptr, Iterator *iterator_begin, Iterator *iterator_end);
    Iterator(const Iterator &other);
    Iterator();
    T *GetPointer() const;
    T &operator*() const;

    //region PLUS
    Iterator operator++();
    const Iterator operator++(int);
    Iterator operator+(size_t n);
    Iterator operator+=(size_t n);
    //endregion

    //region MINUS
    Iterator operator--();
    Iterator operator--(int);
    Iterator operator-(size_t n);
    Iterator operator-=(size_t n);
    size_t operator-(Iterator rhs) const;
    //endregion

    //region COMPARISON
    Iterator &operator=(const Iterator &other);
    bool operator==(const Iterator &other) const;
    bool operator!=(const Iterator &other) const;
    bool operator>(const Iterator &other) const;
    bool operator<(const Iterator &other) const;
    bool operator>=(const Iterator &other) const;
    bool operator<=(const Iterator &other) const;
    //endregion

    void swap(Iterator &other);

    value_type *ptr_;
    Iterator *iterator_begin_;
    Iterator *iterator_end_;

//    void WriteIteratorEnds(T *&begin, T *&end);
    void WriteIteratorEnds(Iterator &begin, Iterator &end);
  };

//  void swap(Iterator &lhs, Iterator &rhs);

  Iterator allocated_begin_;
  Iterator allocated_end_;
  Iterator begin_;
  Iterator end_;

  Iterator begin();
  Iterator end();
  const Iterator &cbegin() const;
  const Iterator &cend() const;
  Iterator allocated_begin();
  Iterator allocated_end();
  const Iterator &callocated_begin() const;
  const Iterator &callocated_end() const;

  bool empty() const;
  size_t allocated_size() const;
  size_t size() const;
  size_t max_size() const;

  T front() const;
  T back() const;

  virtual void move(Iterator p, size_t len);
  virtual void add(Iterator p, size_t len, T t);
  virtual void insert(Iterator p, size_t len, T t);
  virtual void insert(Iterator p, T t);
  virtual void insert(Iterator p, Iterator i, Iterator j);
  virtual void insert(Iterator p, std::initializer_list<T> init_list);
  template<class... Args>
  void emplace(Iterator p, Args &&... args);

  void assign(Iterator i, Iterator j);
  void assign(std::initializer_list<T> init_list);
  void assign(size_t n, T t);

  virtual void add_back(const T &a);
  void push_back(const T &a);

  template<class... Args>
  void emplace_back(Args &&... args);

  virtual void add_front(const T &a);
  void push_front(const T &a);

  template<class... Args>
  void emplace_front(Args &&... args);

  void pop_back();
  void pop_front();
  void EraseByAmount(CCircuitalBuffer::Iterator p, size_t len);
  void erase(Iterator p);
  void erase(Iterator i, Iterator j);
  void clear();

  explicit CCircuitalBuffer(size_t size);
  explicit CCircuitalBuffer(size_t size, T x);
  explicit CCircuitalBuffer(Iterator i, Iterator j);
  CCircuitalBuffer(std::initializer_list<T> init_list);
  CCircuitalBuffer();
  CCircuitalBuffer(const CCircuitalBuffer &other);
  void BufferAllocate(size_t size);
  ~CCircuitalBuffer();

  CCircuitalBuffer &operator=(const CCircuitalBuffer &other);
  bool operator==(const CCircuitalBuffer &other) const;
  bool operator!=(const CCircuitalBuffer &other) const;
  T operator[](size_t n);
  T at(size_t n);

};

template<typename T>
std::ostream &operator<<(std::ostream &stream, const CCircuitalBuffer<T> &buffer);



