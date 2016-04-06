//
//  takram/math/vector2.h
//
//  The MIT License
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
#include <cstddef>
#include <functional>
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
  explicit Vec(const T *values, int size = 2);
  template <class... Args>
  Vec(const std::tuple<Args...>& tuple);
  Vec(std::initializer_list<T> list);

  // Implicit conversion
  template <class U>
  Vec(const Vec2<U>& other);

#if TAKRAM_HAS_OPENCV
  template <class U>
  Vec(const cv::Point_<U>& other);
  template <class U>
  operator cv::Point_<U>() const;
#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS
  Vec(const ofVec2f& other);
  operator ofVec2f() const;
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
  template <class U>
  Vec(const ci::Vec2<U>& other);
  template <class U>
  operator ci::Vec2<U>() const;
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
  explicit Vec(const cv::Vec<U, 2>& other);
  template <class U>
  explicit operator cv::Vec<U, 2>() const;
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
  void set(const T *values, int size = 2);
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
  template <class V, class U = T>
  bool equals(const Vec2<U>& other, V tolerance) const;

  // Arithmetic
  Vec& operator+=(const Vec& other);
  Vec& operator-=(const Vec& other);
  Vec& operator*=(const Vec& other);
  Vec& operator/=(const Vec& other);
  Vec2<Promote<T>> operator-() const;

  // Scalar arithmetic
  Vec& operator+=(T scalar);
  Vec& operator-=(T scalar);
  Vec& operator*=(T scalar);
  Vec& operator/=(T scalar);

  // Attributes
  bool empty() const { return !x && !y; }

  // Angle
  Promote<T> heading() const;
  template <class U = T>
  Promote<T, U> angle(const Vec2<U>& other) const;

  // Magnitude
  Promote<T> magnitude() const;
  Promote<T> magnitudeSquared() const;
  template <class U>
  Vec& limit(U limit);
  template <class U>
  Vec2<Promote<T, U>> limited(U limit) const;

  // Normalization
  bool normal() const { return magnitude() == 1; }
  Vec& normalize();
  Vec2<Promote<T>> normalized() const;

  // Inversion
  Vec& invert();
  Vec2<Promote<T>> inverted() const;

  // Distance
  template <class U = T>
  Promote<T, U> distance(const Vec2<U>& other) const;
  template <class U = T>
  Promote<T, U> distanceSquared(const Vec2<U>& other) const;

  // Products
  template <class U = T>
  Promote<T, U> dot(const Vec2<U>& other) const;
  template <class U = T>
  Promote<T, U> cross(const Vec2<U>& other) const;

  // Interpolation
  template <class V, class U = T>
  Vec2<Promote<T, U>> lerp(const Vec2<U>& other, V factor) const;

  // Jitter
  template <class U = T>
  Vec& jitter(const Vec2<U>& vector);
  template <class Random, class U = T>
  Vec& jitter(const Vec2<U>& vector, Random *random);
  template <class U = T>
  Vec2<Promote<T, U>> jittered(const Vec2<U>& vector) const;
  template <class Random, class U = T>
  Vec2<Promote<T, U>> jittered(const Vec2<U>& vector, Random *random) const;

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
  T * pointer() { return &x; }
  const T * pointer() const { return &x; }

 public:
  T x;
  T y;
};

// Comparison
template <class T, class U>
bool operator==(const Vec2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
bool operator!=(const Vec2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
bool operator<(const Vec2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
bool operator>(const Vec2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
bool operator<=(const Vec2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
bool operator>=(const Vec2<T>& lhs, const Vec2<U>& rhs);

// Arithmetic
template <class T, class U>
Vec2<Promote<T, U>> operator+(const Vec2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
Vec2<Promote<T, U>> operator-(const Vec2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
Vec2<Promote<T, U>> operator*(const Vec2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
Vec2<Promote<T, U>> operator/(const Vec2<T>& lhs, const Vec2<U>& rhs);

// Scalar arithmetic
template <class T, class U, EnableIfScalar<U> * = nullptr>
Vec2<Promote<T, U>> operator+(const Vec2<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<U> * = nullptr>
Vec2<Promote<T, U>> operator-(const Vec2<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<U> * = nullptr>
Vec2<Promote<T, U>> operator*(const Vec2<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<U> * = nullptr>
Vec2<Promote<T, U>> operator/(const Vec2<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec2<Promote<T, U>> operator+(T lhs, const Vec2<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec2<Promote<T, U>> operator-(T lhs, const Vec2<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec2<Promote<T, U>> operator*(T lhs, const Vec2<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec2<Promote<T, U>> operator/(T lhs, const Vec2<U>& rhs);

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
inline Vec<T, 2>::Vec() : x(), y() {}

template <class T>
inline Vec<T, 2>::Vec(T value) : x(value), y(value) {}

template <class T>
inline Vec<T, 2>::Vec(T x, T y) : x(x), y(y) {}

template <class T>
template <class... Args>
inline Vec<T, 2>::Vec(const std::tuple<Args...>& tuple) {
  set(tuple);
}

template <class T>
inline Vec<T, 2>::Vec(const T *values, int size) {
  set(values, size);
}

template <class T>
inline Vec<T, 2>::Vec(std::initializer_list<T> list) {
  set(list);
}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Vec<T, 2>::Vec(const Vec2<U>& other) : x(other.x), y(other.y) {}

#if TAKRAM_HAS_OPENCV

template <class T>
template <class U>
inline Vec<T, 2>::Vec(const cv::Point_<U>& other) : x(other.x), y(other.y) {}

template <class T>
template <class U>
inline Vec<T, 2>::operator cv::Point_<U>() const {
  return cv::Point_<U>(x, y);
}

#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS

template <class T>
inline Vec<T, 2>::Vec(const ofVec2f& other) : x(other.x), y(other.y) {}

template <class T>
inline Vec<T, 2>::operator ofVec2f() const {
  return ofVec2f(x, y);
}

#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER

template <class T>
template <class U>
inline Vec<T, 2>::Vec(const ci::Vec2<U>& other) : x(other.x), y(other.y) {}

template <class T>
template <class U>
inline Vec<T, 2>::operator ci::Vec2<U>() const {
  return ci::Vec2<U>(x, y);
}

#endif  // TAKRAM_HAS_CINDER

#if TAKRAM_HAS_COREGRAPHICS

template <class T>
inline Vec<T, 2>::Vec(const CGPoint& other) : x(other.x), y(other.y) {}

template <class T>
inline Vec<T, 2>::operator CGPoint() const {
  return CGPointMake(x, y);
}

#endif  // TAKRAM_HAS_COREGRAPHICS

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Vec<T, 2>::Vec(const Vec3<U>& other) : x(other.x), y(other.y) {}

template <class T>
template <class U>
inline Vec<T, 2>::Vec(const Vec4<U>& other) : x(other.x), y(other.y) {}

#if TAKRAM_HAS_OPENCV

template <class T>
template <class U>
inline Vec<T, 2>::Vec(const cv::Vec<U, 2>& other) : Vec(other.val, 2) {}

template <class T>
template <class U>
inline Vec<T, 2>::operator cv::Vec<U, 2>() const {
  return cv::Vec<U, 2>(x, y);
}

#endif  // TAKRAM_HAS_OPENCV

#pragma mark Factory

template <class T>
inline Vec2<T> Vec<T, 2>::min() {
  return Vec(std::numeric_limits<T>::min(), std::numeric_limits<T>::min());
}

template <class T>
inline Vec2<T> Vec<T, 2>::max() {
  return Vec(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
}

template <class T>
inline Vec2<T> Vec<T, 2>::heading(Promote<T> angle) {
  return Vec(std::cos(angle), std::sin(angle));
}

template <class T>
inline Vec2<T> Vec<T, 2>::random() {
  return random(&Random<>::shared());
}

template <class T>
inline Vec2<T> Vec<T, 2>::random(T max) {
  return random(max, &Random<>::shared());
}

template <class T>
inline Vec2<T> Vec<T, 2>::random(T min, T max) {
  return random(min, max, &Random<>::shared());
}

template <class T>
template <class Random>
inline Vec2<T> Vec<T, 2>::random(Random *random) {
  return Vec::random(std::numeric_limits<T>::min(),
                     std::numeric_limits<T>::max(),
                     random);
}

template <class T>
template <class Random>
inline Vec2<T> Vec<T, 2>::random(T max, Random *random) {
  return Vec::random(T(), max, random);
}

template <class T>
template <class Random>
inline Vec2<T> Vec<T, 2>::random(T min, T max, Random *random) {
  assert(random);
  return Vec(random->template uniform<T>(min, max),
             random->template uniform<T>(min, max));
}

#pragma mark Mutators

template <class T>
inline void Vec<T, 2>::set(T value) {
  x = y = value;
}

template <class T>
inline void Vec<T, 2>::set(T x, T y) {
  this->x = x;
  this->y = y;
}

template <class T>
inline void Vec<T, 2>::set(const T *values, int size) {
  reset();
  const auto end = values + size;
  if (values == end) return;
  x = *values;
  if (++values == end) return;
  y = *values;
}

template <class T>
template <class... Args>
inline void Vec<T, 2>::set(const std::tuple<Args...>& tuple) {
  std::tie(x, y) = tuple;
}

template <class T>
inline void Vec<T, 2>::set(std::initializer_list<T> list) {
  reset();
  auto itr = std::begin(list);
  if (itr == std::end(list)) return;
  x = *itr;
  if (++itr == std::end(list)) return;
  y = *itr;
}

template <class T>
inline void Vec<T, 2>::reset() {
  *this = Vec();
}

#pragma mark Element access

template <class T>
inline T& Vec<T, 2>::at(int index) {
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
inline const T& Vec<T, 2>::at(int index) const {
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
inline T& Vec<T, 2>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <class T>
inline const T& Vec<T, 2>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <class T, class U>
inline bool operator==(const Vec2<T>& lhs, const Vec2<U>& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <class T, class U>
inline bool operator!=(const Vec2<T>& lhs, const Vec2<U>& rhs) {
  return !(lhs == rhs);
}

template <class T, class U>
inline bool operator<(const Vec2<T>& lhs, const Vec2<U>& rhs) {
  return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}

template <class T, class U>
inline bool operator>(const Vec2<T>& lhs, const Vec2<U>& rhs) {
  return lhs.x > rhs.x || (lhs.x == rhs.x && lhs.y > rhs.y);
}

template <class T, class U>
inline bool operator<=(const Vec2<T>& lhs, const Vec2<U>& rhs) {
  return lhs < rhs || lhs == rhs;
}

template <class T, class U>
inline bool operator>=(const Vec2<T>& lhs, const Vec2<U>& rhs) {
  return lhs > rhs || lhs == rhs;
}

template <class T>
template <class V, class U>
inline bool Vec<T, 2>::equals(const Vec2<U>& other, V tolerance) const {
  return (std::abs(x - other.x) <= tolerance &&
          std::abs(y - other.y) <= tolerance);
}

#pragma mark Arithmetic

template <class T>
inline Vec2<T>& Vec<T, 2>::operator+=(const Vec& other) {
  x += other.x;
  y += other.y;
  return *this;
}

template <class T>
inline Vec2<T>& Vec<T, 2>::operator-=(const Vec& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

template <class T>
inline Vec2<T>& Vec<T, 2>::operator*=(const Vec& other) {
  x *= other.x;
  y *= other.y;
  return *this;
}

template <class T>
inline Vec2<T>& Vec<T, 2>::operator/=(const Vec& other) {
  x /= other.x;
  y /= other.y;
  return *this;
}

template <class T>
inline Vec2<Promote<T>> Vec<T, 2>::operator-() const {
  using V = Promote<T>;
  return Vec2<V>(-static_cast<V>(x), -static_cast<V>(y));
}

template <class T, class U>
inline Vec2<Promote<T, U>> operator+(const Vec2<T>& lhs, const Vec2<U>& rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs.x) + rhs.x, static_cast<V>(lhs.y) + rhs.y);
}

template <class T, class U>
inline Vec2<Promote<T, U>> operator-(const Vec2<T>& lhs, const Vec2<U>& rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs.x) - rhs.x, static_cast<V>(lhs.y) - rhs.y);
}

template <class T, class U>
inline Vec2<Promote<T, U>> operator*(const Vec2<T>& lhs, const Vec2<U>& rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs.x) * rhs.x, static_cast<V>(lhs.y) * rhs.y);
}

template <class T, class U>
inline Vec2<Promote<T, U>> operator/(const Vec2<T>& lhs, const Vec2<U>& rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs.x) / rhs.x, static_cast<V>(lhs.y) / rhs.y);
}

#pragma mark Scalar arithmetic

template <class T>
inline Vec2<T>& Vec<T, 2>::operator+=(T scalar) {
  x += scalar;
  y += scalar;
  return *this;
}

template <class T>
inline Vec2<T>& Vec<T, 2>::operator-=(T scalar) {
  x -= scalar;
  y -= scalar;
  return *this;
}

template <class T>
inline Vec2<T>& Vec<T, 2>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

template <class T>
inline Vec2<T>& Vec<T, 2>::operator/=(T scalar) {
  x /= scalar;
  y /= scalar;
  return *this;
}

template <class T, class U, EnableIfScalar<U> *>
inline Vec2<Promote<T, U>> operator+(const Vec2<T>& lhs, U rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs.x) + rhs, static_cast<V>(lhs.y) + rhs);
}

template <class T, class U, EnableIfScalar<U> *>
inline Vec2<Promote<T, U>> operator-(const Vec2<T>& lhs, U rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs.x) - rhs, static_cast<V>(lhs.y) - rhs);
}

template <class T, class U, EnableIfScalar<U> *>
inline Vec2<Promote<T, U>> operator*(const Vec2<T>& lhs, U rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs.x) * rhs, static_cast<V>(lhs.y) * rhs);
}

template <class T, class U, EnableIfScalar<U> *>
inline Vec2<Promote<T, U>> operator/(const Vec2<T>& lhs, U rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs.x) / rhs, static_cast<V>(lhs.y) / rhs);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec2<Promote<T, U>> operator+(T lhs, const Vec2<U>& rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs) + rhs.x, static_cast<V>(lhs) + rhs.y);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec2<Promote<T, U>> operator-(T lhs, const Vec2<U>& rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs) - rhs.x, static_cast<V>(lhs) - rhs.y);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec2<Promote<T, U>> operator*(T lhs, const Vec2<U>& rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs) * rhs.x, static_cast<V>(lhs) * rhs.y);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec2<Promote<T, U>> operator/(T lhs, const Vec2<U>& rhs) {
  using V = Promote<T, U>;
  return Vec2<V>(static_cast<V>(lhs) / rhs.x, static_cast<V>(lhs) / rhs.y);
}

#pragma mark Angle

template <class T>
inline Promote<T> Vec<T, 2>::heading() const {
  return std::atan2(y, x);
}

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 2>::angle(const Vec2<U>& other) const {
  using V = Promote<T, U>;
  return std::atan2(static_cast<V>(x) * other.y - y * other.x,
                    static_cast<V>(x) * other.x + y * other.y);
}

#pragma mark Magnitude

template <class T>
inline Promote<T> Vec<T, 2>::magnitude() const {
  return std::sqrt(magnitudeSquared());
}

template <class T>
inline Promote<T> Vec<T, 2>::magnitudeSquared() const {
  return static_cast<Promote<T>>(x) * x + y * y;
}

template <class T>
template <class U>
inline Vec2<T>& Vec<T, 2>::limit(U limit) {
  if (magnitudeSquared() > static_cast<Promote<T>>(limit) * limit) {
    normalize();
    *this *= limit;
  }
  return *this;
}

template <class T>
template <class U>
inline Vec2<Promote<T, U>> Vec<T, 2>::limited(U limit) const {
  return Vec2<Promote<T, U>>(*this).limit(limit);
}

#pragma mark Normalization

template <class T>
inline Vec2<T>& Vec<T, 2>::normalize() {
  const auto denominator = magnitude();
  if (denominator) {
    *this /= denominator;
  }
  return *this;
}

template <class T>
inline Vec2<Promote<T>> Vec<T, 2>::normalized() const {
  return Vec2<Promote<T>>(*this).normalize();
}

#pragma mark Inversion

template <class T>
inline Vec2<T>& Vec<T, 2>::invert() {
  x *= -1;
  y *= -1;
  return *this;
}

template <class T>
inline Vec2<Promote<T>> Vec<T, 2>::inverted() const {
  return Vec2<Promote<T>>(*this).invert();
}

#pragma mark Distance

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 2>::distance(const Vec2<U>& other) const {
  return (*this - other).magnitude();
}

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 2>::distanceSquared(const Vec2<U>& other) const {
  return (*this - other).magnitudeSquared();
}

#pragma mark Products

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 2>::dot(const Vec2<U>& other) const {
  return static_cast<Promote<T, U>>(x) * other.x + y * other.y;
}

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 2>::cross(const Vec2<U>& other) const {
  return static_cast<Promote<T, U>>(x) * other.y - y * other.x;
}

#pragma mark Interpolation

template <class T>
template <class V, class U>
inline Vec2<Promote<T, U>> Vec<T, 2>::lerp(const Vec2<U>& other,
                                           V factor) const {
  return Vec2<Promote<T, U>>(x + (other.x - x) * factor,
                             y + (other.y - y) * factor);
}

#pragma mark Jitter

template <class T>
template <class U>
inline Vec2<T>& Vec<T, 2>::jitter(const Vec2<U>& vector) {
  return jitter(vector, &Random<>::shared());
}

template <class T>
template <class Random, class U>
inline Vec2<T>& Vec<T, 2>::jitter(const Vec2<U>& vector, Random *random) {
  if (vector.empty()) {
    return *this;
  }
  using V = Promote<T, U>;
  x += vector.x * random->template uniform<V>(-1, 1);
  y += vector.y * random->template uniform<V>(-1, 1);
  return *this;
}

template <class T>
template <class U>
inline Vec2<Promote<T, U>> Vec<T, 2>::jittered(const Vec2<U>& vector) const {
  return Vec2<Promote<T, U>>(*this).jitter(vector);
}

template <class T>
template <class Random, class U>
inline Vec2<Promote<T, U>> Vec<T, 2>::jittered(const Vec2<U>& vector,
                                               Random *random) const {
  return Vec2<Promote<T, U>>(*this).jitter(vector, random);
}

#pragma mark Coordinate system conversion

template <class T>
inline Vec2<Promote<T>> Vec<T, 2>::cartesian() const {
  using V = Promote<T>;
  return Vec2<V>(static_cast<V>(x) * std::cos(y),
                 static_cast<V>(x) * std::sin(y));
}

template <class T>
inline Vec2<Promote<T>> Vec<T, 2>::polar() const {
  return Vec2<Promote<T>>(magnitude(), heading());
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Vec2<T>& vector) {
  return os << "( " << vector.x << ", " << vector.y << " )";
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

template <class T>
struct std::hash<takram::math::Vec2<T>> {
  std::size_t operator()(const takram::math::Vec2<T>& value) const {
    std::hash<T> hash;
    return (hash(value.x) << 0) ^ (hash(value.y) << 1);
  }
};

#endif  // TAKRAM_MATH_VECTOR2_H_
