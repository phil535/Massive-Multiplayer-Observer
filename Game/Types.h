#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <type_traits>
#include <ostream>
#include <array>
#include <cstddef>
#include <cmath>

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

#include <iostream>

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

    _Vec_(std::initializer_list<TYPE> list)
    {
      std::copy(list.begin(), list.end(), data_.begin());
    }

    template<typename... Args>
    _Vec_(Args... args)
    {
      TYPE data[SIZE] = {args...};
      for(auto it = 0; it < SIZE; it++)
        data_[it] = data[it];
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Copy-constructor
    _Vec_(const _Vec_<TYPE, SIZE> &rhs) : data_(rhs.data_){}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Assignment operator
    _Vec_ &operator=(const _Vec_ &rhs)
    {
      std::copy(rhs.data_.begin(), rhs.data_.end(), data_.begin());
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
      _Vec_<TYPE, SIZE> result;
      for(int i = 0; i < data_.size(); i++)
        result.data_[i] = data_[i] + rhs.data_[i];
      return result;
    }
    _Vec_<TYPE, SIZE> operator+(const TYPE &value) const
    {
      _Vec_<TYPE, SIZE> result;
      for(int i = 0; i < data_.size(); i++)
        result.data_[i] = data_[i] + value;
      return result;
    }
    _Vec_<TYPE, SIZE> &operator+=(const _Vec_<TYPE, SIZE> &rhs)
    {
      for(int i = 0; i < data_.size(); i++)
        data_[i] += rhs.data_[i];
      return *this;
    }
    _Vec_<TYPE, SIZE> &operator+=(const TYPE &value)
    {
      for(int i = 0; i < data_.size(); i++)
        data_[i] += value;
      return *this;
    }
    _Vec_<TYPE, SIZE> operator-(const _Vec_<TYPE, SIZE> &rhs) const
    {
      _Vec_<TYPE, SIZE> result;
      for(int i = 0; i < data_.size(); i++)
        result.data_[i] = data_[i] - rhs.data_[i];
      return result;
    }
    _Vec_<TYPE, SIZE> operator-(const TYPE &value) const
    {
      _Vec_<TYPE, SIZE> result;
      for(int i = 0; i < data_.size(); i++)
        result.data_[i] = data_[i] - value;
      return result;
    }
    _Vec_<TYPE, SIZE> &operator-=(const _Vec_<TYPE, SIZE> &rhs)
    {
      for(int i = 0; i < data_.size(); i++)
        data_[i] -= rhs.data_[i];
      return *this;
    }
    _Vec_<TYPE, SIZE> &operator-=(const TYPE &value)
    {
      _Vec_<TYPE, SIZE> sum;
      for(int i = 0; i < data_.size(); i++)
        data_[i] -= value;
      return *this;
    }
    _Vec_<TYPE, SIZE> operator*(const _Vec_<TYPE, SIZE> &rhs) const
    {
      _Vec_<TYPE, SIZE> result;
      for(int i = 0; i < data_.size(); i++)
        result.data_[i] = data_[i] * rhs.data_[i];
      return result;
    }
    _Vec_<TYPE, SIZE> operator*(const TYPE &value) const
    {
      _Vec_<TYPE, SIZE> result;
      for(int i = 0; i < data_.size(); i++)
        result.data_[i] = data_[i] * value;
      return result;
    }
    _Vec_<TYPE, SIZE> &operator*=(const _Vec_<TYPE, SIZE> &rhs)
    {
      for(int i = 0; i < data_.size(); i++)
        data_[i] *= rhs.data_[i];
      return *this;
    }
    _Vec_<TYPE, SIZE> &operator*=(const TYPE &value)
    {
      for(int i = 0; i < data_.size(); i++)
        data_[i] *= value;
      return *this;
    }
    _Vec_<TYPE, SIZE> operator/(const _Vec_<TYPE, SIZE> &rhs) const
    {
      _Vec_<TYPE, SIZE> result;
      for(int i = 0; i < data_.size(); i++)
        result.data_[i] = data_[i] / rhs.data_[i];
      return result;
    }
    _Vec_<TYPE, SIZE> operator/(const TYPE &value) const
    {
      _Vec_<TYPE, SIZE> result;
      for(int i = 0; i < data_.size(); i++)
        result.data_[i] = data_[i] / value;
      return result;
    }
    _Vec_<TYPE, SIZE> &operator/=(const _Vec_<TYPE, SIZE> &rhs)
    {
      for(int i = 0; i < data_.size(); i++)
        data_[i] /= rhs.data_[i];
      return *this;
    }
    _Vec_<TYPE, SIZE> &operator/=(const TYPE &value)
    {
      for(int i = 0; i < data_.size(); i++)
        data_[i] /= value;
      return *this;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Comparison operators
    bool operator==(const _Vec_<TYPE, SIZE> &rhs) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] != rhs.data_[i]) return false;
      return true;
    }
    bool operator==(const TYPE &value) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] != value) return false;
      return true;
    }
    bool operator!=(const _Vec_<TYPE, SIZE> &rhs) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] != rhs.data_[i]) return true;
      return false;
    }
    bool operator!=(const TYPE &value) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] != value) return true;
      return false;
    }
    bool operator<(const _Vec_<TYPE, SIZE> &rhs) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] >= rhs.data_[i]) return false;
      return true;
    }
    bool operator<(const TYPE &value) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] >= value) return false;
      return true;
    }
    bool operator<=(const _Vec_<TYPE, SIZE> &rhs) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] > rhs.data_[i]) return false;
      return true;
    }
    bool operator<=(const TYPE &value) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] > value) return false;
      return true;
    }
    bool operator>(const _Vec_<TYPE, SIZE> &rhs) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] <= rhs.data_[i]) return false;
      return true;
    }
    bool operator>(const TYPE &value) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] <= value) return false;
      return true;
    }
    bool operator>=(const _Vec_<TYPE, SIZE> &rhs) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] < rhs.data_[i]) return false;
      return true;
    }
    bool operator>=(const TYPE &value) const
    {
      for(int i = 0; i < data_.size(); i++)
        if(data_[i] < value) return false;
      return true;
    }



    _Vec_<TYPE, SIZE> &operator%=(const _Vec_<TYPE, SIZE> &rhs)
    {
      for(int i = 0; i < data_.size(); i++)
        data_[i] %= rhs.data_[i];
      return *this;
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

    inline TYPE &at(size_t iterator){return data_.at(iterator);}
    inline TYPE &at(size_t iterator)const{return data_.at(iterator);}

    inline size_t size() const{return SIZE;};

    inline double degree()const{return std::atan2(data_[1], data_[0]) * 180.0 / M_PI;};

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // methods operator
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
    double euclideanDistance(const _Vec_<TYPE, SIZE> &rhs) const
    {
      double squared_distance = 0.0;

      for(int i = 0; i < data_.size(); i++)
      {
        double delta = data_[i] - rhs.data_[i];
        squared_distance += delta * delta;
      }
      return std::sqrt(squared_distance);
    }
    size_t euclideanDistanceSquared(const _Vec_<TYPE, SIZE> &rhs) const
    {
      size_t squared_distance = 0;

      for(int i = 0; i < data_.size(); i++)
      {
        double delta = data_[i] - rhs.data_[i];
        squared_distance += delta * delta;
      }
      return squared_distance;
    }
    double dot(const _Vec_<TYPE, SIZE> &rhs)const
    {
      double dot = 0.0;
      for(int i = 0; i < data_.size(); i++)
      {
        dot += data_[i] * rhs.data_[i];
      }
      return dot;
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
typedef _Vec_<int, 2> Size;

#endif //GAME_TYPES_H
