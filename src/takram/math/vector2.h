//
//  takram/math/vector2.h
//
//  MIT License
//
//  Copyright (C) 2015 Shota Matsuda
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//

#pragma once
#ifndef TAKRAM_MATH_VECTOR2_H_
#define TAKRAM_MATH_VECTOR2_H_

#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <ostream>
#include <tuple>

#if TAKRAM_HAS_OPENCV
#include "opencv2/core/core.hpp"
#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS
#include "ofVec2f.h"
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
#include "cinder/Vector.h"
#endif  // TAKRAM_HAS_CINDER

#include "takram/math/axis.h"
#include "takram/math/enablers.h"
#include "takram/math/promotion.h"
#include "takram/math/random.h"

namespace takram {
namespace math {

template <class T, int D>
class Vector;
template <class T, int D>
using Vec = Vector<T, D>;

template <class T>
using Vector2 = Vector<T, 2>;
template <class T>
using Vector3 = Vector<T, 3>;
template <class T>
using Vector4 = Vector<T, 4>;

template <class T>
class Vector<T, 2> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const int dimensions = 2;

 public:
  Vector();
  explicit Vector(T value);
  Vector(T x, T y);
  explicit Vector(const T *values, int size = dimensions);
  template <class... Args>
  Vector(const std::tuple<Args...>& tuple);
  Vector(std::initializer_list<T> list);

  // Implicit conversion
  template <class U>
  Vector(const Vector2<U>& other);

#if TAKRAM_HAS_OPENCV
  template <class U>
  Vector(const cv::Point_<U>& other);
  operator cv::Point_<T>() const;
#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS
  Vector(const ofVec2f& other);
  operator ofVec2f() const;
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
  template <class U>
  Vector(const ci::Vec2<U>& other);
  operator ci::Vec2<T>() const;
#endif  // TAKRAM_HAS_CINDER

  // Explicit conversion
  template <class U>
  explicit Vector(const Vector3<U>& other);
  template <class U>
  explicit Vector(const Vector4<U>& other);

  // Copy semantics
  Vector(const Vector2<T>& other) = default;
  Vector2<T>& operator=(const Vector2<T>& other) = default;

  // Factory
  static Vector2<T> min();
  static Vector2<T> max();
  template <class Random>
  static Vector2<T> random(Random *random);
  template <class Random>
  static Vector2<T> random(T max, Random *random);
  template <class Random>
  static Vector2<T> random(T min, T max, Random *random);

  // Mutators
  void set(T value);
  void set(T x, T y);
  void set(const T *values, int size = dimensions);
  template <class... Args>
  void set(const std::tuple<Args...>& tuple);
  void set(std::initializer_list<T> list);
  void reset();

  // Element access
  T& operator[](int index) { return at(index); }
  const T& operator[](int index) const { return at(index); }
  T& operator[](Axis axis) { return at(axis); }
  const T& operator[](Axis axis) const { return at(axis); }
  T& at(int index);
  const T& at(int index) const;
  T& at(Axis axis);
  const T& at(Axis axis) const;
  T& front() { return x; }
  const T& front() const { return x; }
  T& back() { return y; }
  const T& back() const { return y; }

  // Comparison
  template <class U>
  bool operator==(const Vector2<U>& other) const;
  template <class U>
  bool operator!=(const Vector2<U>& other) const;
  template <class U>
  bool operator<(const Vector2<U>& other) const;
  template <class U>
  bool operator>(const Vector2<U>& other) const;
  template <class U>
  bool operator<=(const Vector2<U>& other) const;
  template <class U>
  bool operator>=(const Vector2<U>& other) const;

  // Arithmetic
  Vector2<T>& operator+=(const Vector2<T>& other);
  Vector2<T>& operator-=(const Vector2<T>& other);
  Vector2<T>& operator*=(const Vector2<T>& other);
  Vector2<T>& operator/=(const Vector2<T>& other);
  template <class U>
  const Vector2<Promote<T, U>> operator+(const Vector2<U>& other) const;
  template <class U>
  const Vector2<Promote<T, U>> operator-(const Vector2<U>& other) const;
  template <class U>
  const Vector2<Promote<T, U>> operator*(const Vector2<U>& other) const;
  template <class U>
  const Vector2<Promote<T, U>> operator/(const Vector2<U>& other) const;
  const Vector2<Promote<T>> operator-() const;

  // Scalar arithmetic
  Vector2<T>& operator+=(T scalar);
  Vector2<T>& operator-=(T scalar);
  Vector2<T>& operator*=(T scalar);
  Vector2<T>& operator/=(T scalar);
  template <class U, EnableIfScalar<U> * = nullptr>
  const Vector2<Promote<T, U>> operator+(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  const Vector2<Promote<T, U>> operator-(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  const Vector2<Promote<T, U>> operator*(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  const Vector2<Promote<T, U>> operator/(U scalar) const;

  // Attributes
  bool empty() const { return !x && !y; }

  // Angle
  Promote<T> heading() const;
  template <class U>
  Promote<T> angle(const Vector2<U>& other) const;

  // Magnitude
  Promote<T> magnitude() const;
  Promote<T> magnitudeSquared() const;
  template <class U>
  Vector2<T>& limit(U limit);
  template <class U>
  Vector2<Promote<T>> limited(U limit) const;

  // Normalization
  bool normal() const { return magnitude() == 1; }
  Vector2<T>& normalize();
  Vector2<Promote<T>> normalized() const;

  // Inversion
  Vector2<T>& invert();
  Vector2<Promote<T>> inverted() const;

  // Distance
  template <class U>
  Promote<T> distance(const Vector2<U>& other) const;
  template <class U>
  Promote<T> distanceSquared(const Vector2<U>& other) const;

  // Products
  template <class U>
  Promote<T, U> dot(const Vector2<U>& other) const;
  template <class U>
  Promote<T, U> cross(const Vector2<U>& other) const;

  // Coordinate system conversion
  Vector2<Promote<T>> cartesian() const;
  Vector2<Promote<T>> polar() const;

  // Iterator
  Iterator begin() { return &x; }
  ConstIterator begin() const { return &x; }
  Iterator end() { return &y + 1; }
  ConstIterator end() const { return &y + 1; }
  ReverseIterator rbegin() { return ReverseIterator(begin()); }
  ConstReverseIterator rbegin() const { return ConstReverseIterator(begin()); }
  ReverseIterator rend() { return ReverseIterator(end()); }
  ConstReverseIterator rend() const { return ConstReverseIterator(end()); }

  // Pointer
  T * ptr() { return &x; }
  const T * ptr() const { return &x; }

 public:
  T x;
  T y;
};

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

template <class T>
using Vec2 = Vector2<T>;
using Vec2i = Vector2<int>;
using Vec2f = Vector2<float>;
using Vec2d = Vector2<double>;

#pragma mark -

template <class T>
inline Vector2<T>::Vector() : x(), y() {}

template <class T>
inline Vector2<T>::Vector(T value) : x(value), y(value) {}

template <class T>
inline Vector2<T>::Vector(T x, T y) : x(x), y(y) {}

template <class T>
template <class... Args>
inline Vector2<T>::Vector(const std::tuple<Args...>& tuple) {
  set(tuple);
}

template <class T>
inline Vector2<T>::Vector(const T *values, int size) {
  set(values, size);
}

template <class T>
inline Vector2<T>::Vector(std::initializer_list<T> list) {
  set(list);
}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Vector2<T>::Vector(const Vector2<U>& other) : x(other.x), y(other.y) {}

#if TAKRAM_HAS_OPENCV

template <class T>
template <class U>
inline Vector2<T>::Vector(const cv::Point_<U>& other)
    : x(other.x),
      y(other.y) {}

template <class T>
inline Vector2<T>::operator cv::Point_<T>() const {
  return cv::Point_<T>(x, y);
}

#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS

template <class T>
inline Vector2<T>::Vector(const ofVec2f& other) : x(other.x), y(other.y) {}

template <class T>
inline Vector2<T>::operator ofVec2f() const {
  return ofVec2f(x, y);
}

#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER

template <class T>
template <class U>
inline Vector2<T>::Vector(const ci::Vec2<U>& other) : x(other.x), y(other.y) {}

template <class T>
inline Vector2<T>::operator ci::Vec2<T>() const {
  return ci::Vec2<T>(x, y);
}

#endif  // TAKRAM_HAS_CINDER

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Vector2<T>::Vector(const Vector3<U>& other) : x(other.x), y(other.y) {}

template <class T>
template <class U>
inline Vector2<T>::Vector(const Vector4<U>& other) : x(other.x), y(other.y) {}

#pragma mark Factory

template <class T>
inline Vector2<T> Vector2<T>::min() {
  return Vector2<T>(std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::min());
}

template <class T>
inline Vector2<T> Vector2<T>::max() {
  return Vector2<T>(std::numeric_limits<T>::max(),
                    std::numeric_limits<T>::max());
}

template <class T>
template <class Random>
inline Vector2<T> Vector2<T>::random(Random *random) {
  return Vector2<T>::random(std::numeric_limits<T>::min(),
                            std::numeric_limits<T>::max(),
                            random);
}

template <class T>
template <class Random>
inline Vector2<T> Vector2<T>::random(T max, Random *random) {
  return Vector2<T>::random(T(), max, random);
}

template <class T>
template <class Random>
inline Vector2<T> Vector2<T>::random(T min, T max, Random *random) {
  assert(random);
  return Vector2<T>(random->template uniform<T>(min, max),
                    random->template uniform<T>(min, max));
}

#pragma mark Mutators

template <class T>
inline void Vector2<T>::set(T value) {
  x = y = value;
}

template <class T>
inline void Vector2<T>::set(T x, T y) {
  this->x = x;
  this->y = y;
}

template <class T>
inline void Vector2<T>::set(const T *values, int size) {
  reset();
  const auto end = values + size;
  if (values == end) return; x = *values;
  if (++values == end) return; y = *values;
}

template <class T>
template <class... Args>
inline void Vector2<T>::set(const std::tuple<Args...>& tuple) {
  std::tie(x, y) = tuple;
}

template <class T>
inline void Vector2<T>::set(std::initializer_list<T> list) {
  reset();
  auto itr = std::begin(list);
  if (itr == std::end(list)) return; x = *itr;
  if (++itr == std::end(list)) return; y = *itr;
}

template <class T>
inline void Vector2<T>::reset() {
  *this = Vector2<T>();
}

#pragma mark Element access

template <class T>
inline T& Vector2<T>::at(int index) {
  switch (index) {
    case 0: return x;
    case 1: return y;
    default:
      assert(false);
      break;
  }
  return x;
}

template <class T>
inline const T& Vector2<T>::at(int index) const {
  switch (index) {
    case 0: return x;
    case 1: return y;
    default:
      assert(false);
      break;
  }
  return x;
}

template <class T>
inline T& Vector2<T>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <class T>
inline const T& Vector2<T>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Vector2<T>::operator==(const Vector2<U>& other) const {
  return x == other.x && y == other.y;
}

template <class T>
template <class U>
inline bool Vector2<T>::operator!=(const Vector2<U>& other) const {
  return !operator==(other);
}

template <class T>
template <class U>
inline bool Vector2<T>::operator<(const Vector2<U>& other) const {
  return x < other.x || (x == other.x && y < other.y);
}

template <class T>
template <class U>
inline bool Vector2<T>::operator>(const Vector2<U>& other) const {
  return x > other.x || (x == other.x && y > other.y);
}

template <class T>
template <class U>
inline bool Vector2<T>::operator<=(const Vector2<U>& other) const {
  return operator<(other) || operator==(other);
}

template <class T>
template <class U>
inline bool Vector2<T>::operator>=(const Vector2<U>& other) const {
  return operator>(other) || operator==(other);
}

#pragma mark Arithmetic

template <class T>
inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other) {
  x += other.x;
  y += other.y;
  return *this;
}

template <class T>
inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

template <class T>
inline Vector2<T>& Vector2<T>::operator*=(const Vector2<T>& other) {
  x *= other.x;
  y *= other.y;
  return *this;
}

template <class T>
inline Vector2<T>& Vector2<T>::operator/=(const Vector2<T>& other) {
  assert(other.x && other.y);
  x /= other.x;
  y /= other.y;
  return *this;
}

template <class T>
template <class U>
inline const Vector2<Promote<T, U>> Vector2<T>::operator+(
    const Vector2<U>& other) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) + other.x,
                    static_cast<V>(y) + other.y);
}

template <class T>
template <class U>
inline const Vector2<Promote<T, U>> Vector2<T>::operator-(
    const Vector2<U>& other) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) - other.x,
                    static_cast<V>(y) - other.y);
}

template <class T>
template <class U>
inline const Vector2<Promote<T, U>> Vector2<T>::operator*(
    const Vector2<U>& other) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) * other.x,
                    static_cast<V>(y) * other.y);
}

template <class T>
template <class U>
inline const Vector2<Promote<T, U>> Vector2<T>::operator/(
    const Vector2<U>& other) const {
  assert(other.x && other.y);
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) / other.x,
                    static_cast<V>(y) / other.y);
}

template <class T>
inline const Vector2<Promote<T>> Vector2<T>::operator-() const {
  using V = Promote<T>;
  return Vector2<V>(-static_cast<V>(x),
                    -static_cast<V>(y));
}

#pragma mark Scalar arithmetic

template <class T>
inline Vector2<T>& Vector2<T>::operator+=(T scalar) {
  x += scalar;
  y += scalar;
  return *this;
}

template <class T>
inline Vector2<T>& Vector2<T>::operator-=(T scalar) {
  x -= scalar;
  y -= scalar;
  return *this;
}

template <class T>
inline Vector2<T>& Vector2<T>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

template <class T>
inline Vector2<T>& Vector2<T>::operator/=(T scalar) {
  assert(scalar);
  x /= scalar;
  y /= scalar;
  return *this;
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Vector2<Promote<T, U>> Vector2<T>::operator+(U scalar) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) + scalar,
                    static_cast<V>(y) + scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Vector2<Promote<T, U>> Vector2<T>::operator-(U scalar) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) - scalar,
                    static_cast<V>(y) - scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Vector2<Promote<T, U>> Vector2<T>::operator*(U scalar) const {
  using V = Promote<T, U>;
  return Vector2<V>(static_cast<V>(x) * scalar,
                    static_cast<V>(y) * scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Vector2<Promote<T, U>> Vector2<T>::operator/(U scalar) const {
  using V = Promote<T, U>;
  assert(scalar);
  return Vector2<V>(static_cast<V>(x) / scalar,
                    static_cast<V>(y) / scalar);
}

template <class T, class U, EnableIfScalar<U> * = nullptr>
inline const Vector2<Promote<T, U>> operator*(
    U scalar, const Vector2<T>& vector) {
  return vector * scalar;
}

#pragma mark Angle

template <class T>
inline Promote<T> Vector2<T>::heading() const {
  return std::atan2(y, x);
}

template <class T>
template <class U>
inline Promote<T> Vector2<T>::angle(const Vector2<U>& other) const {
  using V = Promote<T, U>;
  return std::atan2(static_cast<V>(x) * other.y - y * other.x,
                    static_cast<V>(x) * other.x + y * other.y);
}

#pragma mark Magnitude

template <class T>
inline Promote<T> Vector2<T>::magnitude() const {
  return std::sqrt(magnitudeSquared());
}

template <class T>
inline Promote<T> Vector2<T>::magnitudeSquared() const {
  return static_cast<Promote<T>>(x) * x + y * y;
}

template <class T>
template <class U>
inline Vector2<T>& Vector2<T>::limit(U limit) {
  if (magnitudeSquared() > static_cast<Promote<T>>(limit) * limit) {
    normalize();
    *this *= limit;
  }
  return *this;
}

template <class T>
template <class U>
inline Vector2<Promote<T>> Vector2<T>::limited(U limit) const {
  return Vector2<Promote<T>>(*this).limit(limit);
}

#pragma mark Normalization

template <class T>
inline Vector2<T>& Vector2<T>::normalize() {
  const auto denominator = magnitude();
  if (denominator) {
    *this /= denominator;
  }
  return *this;
}

template <class T>
inline Vector2<Promote<T>> Vector2<T>::normalized() const {
  return Vector2<Promote<T>>(*this).normalize();
}

#pragma mark Inversion

template <class T>
inline Vector2<T>& Vector2<T>::invert() {
  x *= -1;
  y *= -1;
  return *this;
}

template <class T>
inline Vector2<Promote<T>> Vector2<T>::inverted() const {
  return Vector2<Promote<T>>(*this).invert();
}

#pragma mark Distance

template <class T>
template <class U>
inline Promote<T> Vector2<T>::distance(const Vector2<U>& other) const {
  return (*this - other).magnitude();
}

template <class T>
template <class U>
inline Promote<T> Vector2<T>::distanceSquared(const Vector2<U>& other) const {
  return (*this - other).magnitudeSquared();
}

#pragma mark Products

template <class T>
template <class U>
inline Promote<T, U> Vector2<T>::dot(const Vector2<U>& other) const {
  return static_cast<Promote<T, U>>(x) * other.x + y * other.y;
}

template <class T>
template <class U>
inline Promote<T, U> Vector2<T>::cross(const Vector2<U>& other) const {
  return static_cast<Promote<T, U>>(x) * other.y - y * other.x;
}

#pragma mark Coordinate system conversion

template <class T>
inline Vector2<Promote<T>> Vector2<T>::cartesian() const {
  using V = Promote<T>;
  return Vector2<V>(static_cast<V>(x) * std::cos(y),
                    static_cast<V>(x) * std::sin(y));
}
  
template <class T>
inline Vector2<Promote<T>> Vector2<T>::polar() const {
  return Vector2<Promote<T>>(magnitude(), heading());
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Vector2<T>& other) {
  return os << "( " << other.x << ", " << other.y << " )";
}

}  // namespace math
}  // namespace takram

#endif  // TAKRAM_MATH_VECTOR2_H_
