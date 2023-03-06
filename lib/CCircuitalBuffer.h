#pragma once

template<typename T>
class CCircuitalBuffer {
 public:

  class Iterator {
   public:
    explicit Iterator(T *ptr);
    T *GetPointer();
    T &operator*();

    //region PLUS
    Iterator operator++();
    Iterator operator+(int n);
    Iterator operator+=(int n);
    //endregion

    //region MINUS
    Iterator operator--();
    Iterator operator-(int n);
    Iterator operator-=(int n);
    int operator-(Iterator rhs);
    //endregion

    //region COMPARISON
    bool operator==(const Iterator &other);
    bool operator!=(const Iterator &other);
    bool operator>(const Iterator &other);
    bool operator<(const Iterator &other);
    bool operator>=(const Iterator &other);
    bool operator<=(const Iterator &other);
    //endregion
   private:
    T *ptr_;
  };

  Iterator *allocated_begin_;
  Iterator *allocated_end_;
  Iterator *begin_;
  Iterator *end_;
  Iterator begin();
  Iterator end();
  explicit CCircuitalBuffer(int size);
  ~CCircuitalBuffer();
};





