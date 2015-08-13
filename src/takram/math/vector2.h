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

#if TAKRAM_HAS_COREGRAPHICS
#include <CoreGraphics/CoreGraphics.h>
#endif  // TAKRAM_HAS_COREGRAPHICS

#include "takram/math/axis.h"
#include "takram/math/enablers.h"
#include "takram/math/promotion.h"
#include "takram/math/random.h"

namespace takram {
namespace math {

template <class T, int D>
class Vec;

template <class T>
using Vec2 = Vec<T, 2>;
template <class T>
using Vec3 = Vec<T, 3>;
template <class T>
using Vec4 = Vec<T, 4>;

template <class T>
class Vec<T, 2> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const int dimensions = 2;

 public:
  Vec();
  explicit Vec(T value);
  Vec(T x, T y);
  explicit Vec(const T *values, int size = dimensions);
  template <class... Args>
  Vec(const std::tuple<Args...>& tuple);
  Vec(std::initializer_list<T> list);

  // Implicit conversion
  template <class U>
  Vec(const Vec2<U>& other);

#if TAKRAM_HAS_OPENCV
  template <class U>
  Vec(const cv::Point_<U>& other);
  operator cv::Point_<T>() const;
#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS
  Vec(const ofVec2f& other);
  operator ofVec2f() const;
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
  template <class U>
  Vec(const ci::Vec2<U>& other);
  operator ci::Vec2<T>() const;
#endif  // TAKRAM_HAS_CINDER

#if TAKRAM_HAS_COREGRAPHICS
  Vec(const CGPoint& other);
  operator CGPoint() const;
#endif  // TAKRAM_HAS_COREGRAPHICS

  // Explicit conversion
  template <class U>
  explicit Vec(const Vec3<U>& other);
  template <class U>
  explicit Vec(const Vec4<U>& other);

#if TAKRAM_HAS_OPENCV
  template <class U>
  explicit Vec(const cv::Vec<U, dimensions>& other);
  explicit operator cv::Vec<T, dimensions>() const;
#endif  // TAKRAM_HAS_OPENCV

  // Copy semantics
  Vec(const Vec&) = default;
  Vec& operator=(const Vec&) = default;

  // Factory
  static Vec min();
  static Vec max();
  static Vec heading(Promote<T> angle);
  static Vec random();
  static Vec random(T max);
  static Vec random(T min, T max);
  template <class Random>
  static Vec random(Random *random);
  template <class Random>
  static Vec random(T max, Random *random);
  template <class Random>
  static Vec random(T min, T max, Random *random);

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
  bool operator==(const Vec2<U>& other) const;
  template <class U>
  bool operator!=(const Vec2<U>& other) const;
  template <class U>
  bool operator<(const Vec2<U>& other) const;
  template <class U>
  bool operator>(const Vec2<U>& other) const;
  template <class U>
  bool operator<=(const Vec2<U>& other) const;
  template <class U>
  bool operator>=(const Vec2<U>& other) const;

  // Arithmetic
  Vec& operator+=(const Vec& other);
  Vec& operator-=(const Vec& other);
  Vec& operator*=(const Vec& other);
  Vec& operator/=(const Vec& other);
  template <class U>
  Vec2<Promote<T, U>> operator+(const Vec2<U>& other) const;
  template <class U>
  Vec2<Promote<T, U>> operator-(const Vec2<U>& other) const;
  template <class U>
  Vec2<Promote<T, U>> operator*(const Vec2<U>& other) const;
  template <class U>
  Vec2<Promote<T, U>> operator/(const Vec2<U>& other) const;
  Vec2<Promote<T>> operator-() const;

  // Scalar arithmetic
  Vec& operator+=(T scalar);
  Vec& operator-=(T scalar);
  Vec& operator*=(T scalar);
  Vec& operator/=(T scalar);
  template <class U, EnableIfScalar<U> * = nullptr>
  Vec2<Promote<T, U>> operator+(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Vec2<Promote<T, U>> operator-(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Vec2<Promote<T, U>> operator*(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Vec2<Promote<T, U>> operator/(U scalar) const;

  // Attributes
  bool empty() const { return !x && !y; }

  // Angle
  Promote<T> heading() const;
  template <class U>
  Promote<T, U> angle(const Vec2<U>& other) const;

  // Magnitude
  Promote<T> magnitude() const;
  Promote<T> magnitudeSquared() const;
  template <class U>
  Vec& limit(U limit);
  template <class U>
  Vec2<Promote<T>> limited(U limit) const;

  // Normalization
  bool normal() const { return magnitude() == 1; }
  Vec& normalize();
  Vec2<Promote<T>> normalized() const;

  // Inversion
  Vec& invert();
  Vec2<Promote<T>> inverted() const;

  // Distance
  template <class U>
  Promote<T, U> distance(const Vec2<U>& other) const;
  template <class U>
  Promote<T, U> distanceSquared(const Vec2<U>& other) const;

  // Products
  template <class U>
  Promote<T, U> dot(const Vec2<U>& other) const;
  template <class U>
  Promote<T, U> cross(const Vec2<U>& other) const;

  // Interpolation
  template <class U, class V>
  Vec& lerp(const Vec2<U>& other, V factor);
  template <class U, class V>
  Vec2<Promote<T, U>> lerp(const Vec2<U>& other, V factor) const;

  // Coordinate system conversion
  Vec2<Promote<T>> cartesian() const;
  Vec2<Promote<T>> polar() const;

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

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;

template <class T, int D>
using Vector = Vec<T, D>;
template <class T>
using Vector2 = Vec2<T>;
using Vector2i = Vec2i;
using Vector2f = Vec2f;
using Vector2d = Vec2d;

#pragma mark -

template <class T>
inline Vec2<T>::Vec() : x(), y() {}

template <class T>
inline Vec2<T>::Vec(T value) : x(value), y(value) {}

template <class T>
inline Vec2<T>::Vec(T x, T y) : x(x), y(y) {}

template <class T>
template <class... Args>
inline Vec2<T>::Vec(const std::tuple<Args...>& tuple) {
  set(tuple);
}

template <class T>
inline Vec2<T>::Vec(const T *values, int size) {
  set(values, size);
}

template <class T>
inline Vec2<T>::Vec(std::initializer_list<T> list) {
  set(list);
}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Vec2<T>::Vec(const Vec2<U>& other) : x(other.x), y(other.y) {}

#if TAKRAM_HAS_OPENCV

template <class T>
template <class U>
inline Vec2<T>::Vec(const cv::Point_<U>& other) : x(other.x), y(other.y) {}

template <class T>
inline Vec2<T>::operator cv::Point_<T>() const {
  return cv::Point_<T>(x, y);
}

#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS

template <class T>
inline Vec2<T>::Vec(const ofVec2f& other) : x(other.x), y(other.y) {}

template <class T>
inline Vec2<T>::operator ofVec2f() const {
  return ofVec2f(x, y);
}

#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER

template <class T>
template <class U>
inline Vec2<T>::Vec(const ci::Vec2<U>& other) : x(other.x), y(other.y) {}

template <class T>
inline Vec2<T>::operator ci::Vec2<T>() const {
  return ci::Vec2<T>(x, y);
}

#endif  // TAKRAM_HAS_CINDER

#if TAKRAM_HAS_COREGRAPHICS

template <class T>
inline Vec2<T>::Vec(const CGPoint& other) : x(other.x), y(other.y) {}

template <class T>
inline Vec2<T>::operator CGPoint() const {
  return CGPointMake(x, y);
}

#endif  // TAKRAM_HAS_COREGRAPHICS

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Vec2<T>::Vec(const Vec3<U>& other) : x(other.x), y(other.y) {}

template <class T>
template <class U>
inline Vec2<T>::Vec(const Vec4<U>& other) : x(other.x), y(other.y) {}

#if TAKRAM_HAS_OPENCV

template <class T>
template <class U>
inline Vec2<T>::Vec(const cv::Vec<U, dimensions>& other)
    : Vec(other.val, dimensions) {}

template <class T>
inline Vec2<T>::operator cv::Vec<T, dimensions>() const {
  return cv::Vec<T, dimensions>(x, y);
}

#endif  // TAKRAM_HAS_OPENCV

#pragma mark Factory

template <class T>
inline Vec2<T> Vec2<T>::min() {
  return Vec(std::numeric_limits<T>::min(), std::numeric_limits<T>::min());
}

template <class T>
inline Vec2<T> Vec2<T>::max() {
  return Vec(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
}

template <class T>
inline Vec2<T> Vec2<T>::heading(Promote<T> angle) {
  return Vec(std::cos(angle), std::sin(angle));
}

template <class T>
inline Vec2<T> Vec2<T>::random() {
  return random(&Random<>::shared());
}

template <class T>
inline Vec2<T> Vec2<T>::random(T max) {
  return random(max, &Random<>::shared());
}

template <class T>
inline Vec2<T> Vec2<T>::random(T min, T max) {
  return random(min, max, &Random<>::shared());
}

template <class T>
template <class Random>
inline Vec2<T> Vec2<T>::random(Random *random) {
  return Vec::random(std::numeric_limits<T>::min(),
                     std::numeric_limits<T>::max(),
                     random);
}

template <class T>
template <class Random>
inline Vec2<T> Vec2<T>::random(T max, Random *random) {
  return Vec::random(T(), max, random);
}

template <class T>
template <class Random>
inline Vec2<T> Vec2<T>::random(T min, T max, Random *random) {
  assert(random);
  return Vec(random->template uniform<T>(min, max),
             random->template uniform<T>(min, max));
}

#pragma mark Mutators

template <class T>
inline void Vec2<T>::set(T value) {
  x = y = value;
}

template <class T>
inline void Vec2<T>::set(T x, T y) {
  this->x = x;
  this->y = y;
}

template <class T>
inline void Vec2<T>::set(const T *values, int size) {
  reset();
  const auto end = values + size;
  if (values == end) return;
  x = *values;
  if (++values == end) return;
  y = *values;
}

template <class T>
template <class... Args>
inline void Vec2<T>::set(const std::tuple<Args...>& tuple) {
  std::tie(x, y) = tuple;
}

template <class T>
inline void Vec2<T>::set(std::initializer_list<T> list) {
  reset();
  auto itr = std::begin(list);
  if (itr == std::end(list)) return;
  x = *itr;
  if (++itr == std::end(list)) return;
  y = *itr;
}

template <class T>
inline void Vec2<T>::reset() {
  *this = Vec();
}

#pragma mark Element access

template <class T>
inline T& Vec2<T>::at(int index) {
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
inline const T& Vec2<T>::at(int index) const {
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
inline T& Vec2<T>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <class T>
inline const T& Vec2<T>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Vec2<T>::operator==(const Vec2<U>& other) const {
  return x == other.x && y == other.y;
}

template <class T>
template <class U>
inline bool Vec2<T>::operator!=(const Vec2<U>& other) const {
  return !operator==(other);
}

template <class T>
template <class U>
inline bool Vec2<T>::operator<(const Vec2<U>& other) const {
  return x < other.x || (x == other.x && y < other.y);
}

template <class T>
template <class U>
inline bool Vec2<T>::operator>(const Vec2<U>& other) const {
  return x > other.x || (x == other.x && y > other.y);
}

template <class T>
template <class U>
inline bool Vec2<T>::operator<=(const Vec2<U>& other) const {
  return operator<(other) || operator==(other);
}

template <class T>
template <class U>
inline bool Vec2<T>::operator>=(const Vec2<U>& other) const {
  return operator>(other) || operator==(other);
}

#pragma mark Arithmetic

template <class T>
inline Vec2<T>& Vec2<T>::operator+=(const Vec& other) {
  x += other.x;
  y += other.y;
  return *this;
}

template <class T>
inline Vec2<T>& Vec2<T>::operator-=(const Vec& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

template <class T>
inline Vec2<T>& Vec2<T>::operator*=(const Vec& other) {
  x *= other.x;
  y *= other.y;
  return *this;
}

template <class T>
inline Vec2<T>& Vec2<T>::operator/=(const Vec& other) {
  assert(other.x && other.y);
  x /= other.x;
  y /= other.y;
  return *this;
}

template <class T>
template <class U>
inline Vec2<Promote<T, U>> Vec2<T>::operator+(const Vec2<U>& other) const {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(x) + other.x, static_cast<V>(y) + other.y);
}

template <class T>
template <class U>
inline Vec2<Promote<T, U>> Vec2<T>::operator-(const Vec2<U>& other) const {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(x) - other.x, static_cast<V>(y) - other.y);
}

template <class T>
template <class U>
inline Vec2<Promote<T, U>> Vec2<T>::operator*(const Vec2<U>& other) const {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(x) * other.x, static_cast<V>(y) * other.y);
}

template <class T>
template <class U>
inline Vec2<Promote<T, U>> Vec2<T>::operator/(const Vec2<U>& other) const {
  assert(other.x && other.y);
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(x) / other.x, static_cast<V>(y) / other.y);
}

template <class T>
inline Vec2<Promote<T>> Vec2<T>::operator-() const {
  using V = Promote<T>;
  return Vec2<V>(-static_cast<V>(x), -static_cast<V>(y));
}

#pragma mark Scalar arithmetic

template <class T>
inline Vec2<T>& Vec2<T>::operator+=(T scalar) {
  x += scalar;
  y += scalar;
  return *this;
}

template <class T>
inline Vec2<T>& Vec2<T>::operator-=(T scalar) {
  x -= scalar;
  y -= scalar;
  return *this;
}

template <class T>
inline Vec2<T>& Vec2<T>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

template <class T>
inline Vec2<T>& Vec2<T>::operator/=(T scalar) {
  assert(scalar);
  x /= scalar;
  y /= scalar;
  return *this;
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Vec2<Promote<T, U>> Vec2<T>::operator+(U scalar) const {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(x) + scalar, static_cast<V>(y) + scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Vec2<Promote<T, U>> Vec2<T>::operator-(U scalar) const {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(x) - scalar, static_cast<V>(y) - scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Vec2<Promote<T, U>> Vec2<T>::operator*(U scalar) const {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(x) * scalar, static_cast<V>(y) * scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Vec2<Promote<T, U>> Vec2<T>::operator/(U scalar) const {
  using V = Promote<T, U>;
  assert(scalar);
  return Vec2<V>(static_cast<V>(x) / scalar, static_cast<V>(y) / scalar);
}

template <class T, class U, EnableIfScalar<U> * = nullptr>
inline Vec2<Promote<T, U>> operator*(U scalar, const Vec2<T>& vector) {
  return vector * scalar;
}

#pragma mark Angle

template <class T>
inline Promote<T> Vec2<T>::heading() const {
  return std::atan2(y, x);
}

template <class T>
template <class U>
inline Promote<T, U> Vec2<T>::angle(const Vec2<U>& other) const {
  using V = Promote<T, U>;
  return std::atan2(static_cast<V>(x) * other.y - y * other.x,
                    static_cast<V>(x) * other.x + y * other.y);
}

#pragma mark Magnitude

template <class T>
inline Promote<T> Vec2<T>::magnitude() const {
  return std::sqrt(magnitudeSquared());
}

template <class T>
inline Promote<T> Vec2<T>::magnitudeSquared() const {
  return static_cast<Promote<T>>(x) * x + y * y;
}

template <class T>
template <class U>
inline Vec2<T>& Vec2<T>::limit(U limit) {
  if (magnitudeSquared() > static_cast<Promote<T>>(limit) * limit) {
    normalize();
    *this *= limit;
  }
  return *this;
}

template <class T>
template <class U>
inline Vec2<Promote<T>> Vec2<T>::limited(U limit) const {
  return Vec2<Promote<T>>(*this).limit(limit);
}

#pragma mark Normalization

template <class T>
inline Vec2<T>& Vec2<T>::normalize() {
  const auto denominator = magnitude();
  if (denominator) {
    *this /= denominator;
  }
  return *this;
}

template <class T>
inline Vec2<Promote<T>> Vec2<T>::normalized() const {
  return Vec2<Promote<T>>(*this).normalize();
}

#pragma mark Inversion

template <class T>
inline Vec2<T>& Vec2<T>::invert() {
  x *= -1;
  y *= -1;
  return *this;
}

template <class T>
inline Vec2<Promote<T>> Vec2<T>::inverted() const {
  return Vec2<Promote<T>>(*this).invert();
}

#pragma mark Distance

template <class T>
template <class U>
inline Promote<T, U> Vec2<T>::distance(const Vec2<U>& other) const {
  return (*this - other).magnitude();
}

template <class T>
template <class U>
inline Promote<T, U> Vec2<T>::distanceSquared(const Vec2<U>& other) const {
  return (*this - other).magnitudeSquared();
}

#pragma mark Products

template <class T>
template <class U>
inline Promote<T, U> Vec2<T>::dot(const Vec2<U>& other) const {
  return static_cast<Promote<T, U>>(x) * other.x + y * other.y;
}

template <class T>
template <class U>
inline Promote<T, U> Vec2<T>::cross(const Vec2<U>& other) const {
  return static_cast<Promote<T, U>>(x) * other.y - y * other.x;
}

#pragma mark Interpolation

template <class T>
template <class U, class V>
inline Vec2<T>& Vec2<T>::lerp(const Vec2<U>& other, V factor) {
  x += (other.x - x) * factor;
  y += (other.y - y) * factor;
}

template <class T>
template <class U, class V>
inline Vec2<Promote<T, U>> Vec2<T>::lerp(const Vec2<U>& other, V factor) const {
  return Vec2<Promote<T, U>>(x + (other.x - x) * factor,
                             y + (other.y - y) * factor);
}

#pragma mark Coordinate system conversion

template <class T>
inline Vec2<Promote<T>> Vec2<T>::cartesian() const {
  using V = Promote<T>;
  return Vec2<V>(static_cast<V>(x) * std::cos(y),
                 static_cast<V>(x) * std::sin(y));
}

template <class T>
inline Vec2<Promote<T>> Vec2<T>::polar() const {
  return Vec2<Promote<T>>(magnitude(), heading());
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Vec2<T>& other) {
  return os << "( " << other.x << ", " << other.y << " )";
}

}  // namespace math

using math::Vec;
using math::Vec2;
using math::Vec2i;
using math::Vec2f;
using math::Vec2d;

using math::Vector;
using math::Vector2;
using math::Vector2i;
using math::Vector2f;
using math::Vector2d;

}  // namespace takram

#endif  // TAKRAM_MATH_VECTOR2_H_
