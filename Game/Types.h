#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <type_traits>
#include <ostream>
#include <array>
#include <cstddef>

namespace Vec
{
  enum
  {
    X = 0,
    Y = 1,
    Z = 2,
    WIDTH = 0,
    HEIGHT = 1,
    DEPTH = 2,
    RED = 0,
    GREEN = 1,
    BLUE = 2,
    ALPHA = 3
  };
}

template<class TYPE, std::size_t SIZE>
class __attribute__((packed)) _Vec_
{
  private:
    std::array<TYPE, SIZE> data_;

  public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor
    _Vec_(){}
    _Vec_(TYPE value)
    {
      *this = value;
    }

    template<class...T2, typename std::enable_if<sizeof...(T2) == SIZE, int>::type = 0>
    _Vec_(T2... args)
    {
      data_ = {args...};
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Copy-constructor
    _Vec_(const _Vec_<TYPE, SIZE> &rhs) : data_(rhs.data_){}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Assignment operator
    _Vec_ &operator=(const _Vec_ &rhs)
    {
      data_ = rhs.data_;
    }
    _Vec_ &operator=(const TYPE &value)
    {
      for(auto &e : *this)
        e = value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Arithmetic operator
    _Vec_<TYPE, SIZE> operator+(const _Vec_<TYPE, SIZE> &rhs) const
    {
      _Vec_<TYPE, SIZE> sum;
      for(int i = 0; i < data_.size(); i++)
        sum.data_[i] = data_[i] + rhs.data_[i];
      return sum;
    }
    _Vec_<TYPE, SIZE> operator-(const _Vec_<TYPE, SIZE> &rhs) const
    {
      _Vec_<TYPE, SIZE> sum;
      for(int i = 0; i < data_.size(); i++)
        sum.data_[i] = data_[i] - rhs.data_[i];
      return sum;
    }
    _Vec_<TYPE, SIZE> operator*(const _Vec_<TYPE, SIZE> &rhs) const
    {
      _Vec_<TYPE, SIZE> sum;
      for(int i = 0; i < data_.size(); i++)
        sum.data_[i] = data_[i] * rhs.data_[i];
      return sum;
    }
    _Vec_<TYPE, SIZE> operator/(const _Vec_<TYPE, SIZE> &rhs) const
    {
      _Vec_<TYPE, SIZE> sum;
      for(int i = 0; i < data_.size(); i++)
        sum.data_[i] = data_[i] / rhs.data_[i];
      return sum;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getter / Setter
    TYPE &width(){ return data_[Vec::WIDTH];};
    TYPE &height(){ return data_[Vec::HEIGHT];};
    TYPE &depth(){ return data_[Vec::DEPTH];};
    const TYPE &width()const{ return data_[Vec::WIDTH];};
    const TYPE &height()const{ return data_[Vec::HEIGHT];};
    const TYPE &depth()const{ return data_[Vec::DEPTH];};

    TYPE &x(){ return data_[Vec::X];};
    TYPE &y(){ return data_[Vec::Y];};
    TYPE &z(){ return data_[Vec::Z];};
    const TYPE &x()const{ return data_[Vec::X];};
    const TYPE &y()const{ return data_[Vec::Y];};
    const TYPE &z()const{ return data_[Vec::Z];};

    TYPE &red(){ return data_[Vec::RED];};
    TYPE &green(){ return data_[Vec::GREEN];};
    TYPE &blue(){ return data_[Vec::BLUE];};
    TYPE &alpha(){return data_[Vec::ALPHA];};
    const TYPE &red()const{ return data_[Vec::RED];};
    const TYPE &green()const{ return data_[Vec::GREEN];};
    const TYPE &blue()const{ return data_[Vec::BLUE];};
    const TYPE &alpha()const{return data_[Vec::ALPHA];};

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ostream operator
    void print(std::ostream &stream) const
    {
      stream << '(';
      for(auto it = data_.begin(); it != data_.end(); it++)
      {
        if(it != data_.begin()) stream << ',';
        stream << *it;
      }
      stream << ')';
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // iterators
    TYPE *begin()
    {
      return data_.begin();
    }
    TYPE *end()
    {
      return data_.end();
    }
};

template<class T>
auto operator<<(std::ostream& os, const T& t) -> decltype(t.print(os), os)
{
  t.print(os);
  return os;
}

typedef _Vec_<int, 2> Vec2i;
typedef _Vec_<int, 2> Position;
typedef _Vec_<int, 2> Distance;
typedef _Vec_<int, 2> Direction;

#endif //GAME_TYPES_H
