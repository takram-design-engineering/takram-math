//
//  takram/math/vector4.h
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
#ifndef TAKRAM_MATH_VECTOR4_H_
#define TAKRAM_MATH_VECTOR4_H_

#include <cassert>
#include <cmath>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <ostream>
#include <tuple>

#if TAKRAM_HAS_OPENFRAMEWORKS
#include "ofVec4f.h"
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
#include "cinder/Vec.h"
#endif  // TAKRAM_HAS_CINDER

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
class Vec<T, 4> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const int dimensions = 4;

 public:
  Vec();
  explicit Vec(T value);
  Vec(T x, T y, T z = T(), T w = T());
  explicit Vec(const T *values, int size = 4);
  template <class... Args>
  Vec(const std::tuple<Args...>& tuple);
  Vec(std::initializer_list<T> list);

  // Implicit conversion
  template <class U>
  Vec(const Vec4<U>& other);

#if TAKRAM_HAS_OPENFRAMEWORKS
  Vec(const ofVec4f& other);
  operator ofVec4f() const;
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
  template <class U>
  Vec(const ci::Vec4<U>& other);
  template <class U>
  operator ci::Vec4<U>() const;
#endif  // TAKRAM_HAS_CINDER

  // Explicit conversion
  template <class U>
  explicit Vec(const Vec2<U>& other);
  template <class U>
  explicit Vec(const Vec3<U>& other);

#if TAKRAM_HAS_OPENCV
  template <class U>
  explicit Vec(const cv::Vec<U, 4>& other);
  template <class U>
  explicit operator cv::Vec<U, 4>() const;
#endif  // TAKRAM_HAS_OPENCV

  // Copy semantics
  Vec(const Vec&) = default;
  Vec& operator=(const Vec&) = default;

  // Factory
  static Vec min();
  static Vec max();
  static Vec headingXY(Promote<T> angle);
  static Vec headingYZ(Promote<T> angle);
  static Vec headingZX(Promote<T> angle);
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
  void set(T x, T y, T z = T(), T w = T());
  void set(const T *values, int size = 4);
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
  T& back() { return w; }
  const T& back() const { return w; }

  // Comparison
  template <class U>
  bool operator==(const Vec4<U>& other) const;
  template <class U>
  bool operator!=(const Vec4<U>& other) const;
  template <class U>
  bool operator<(const Vec4<U>& other) const;
  template <class U>
  bool operator>(const Vec4<U>& other) const;
  template <class U>
  bool operator<=(const Vec4<U>& other) const;
  template <class U>
  bool operator>=(const Vec4<U>& other) const;
  template <class V, class U = T>
  bool equals(const Vec4<U>& other, V tolerance) const;

  // Arithmetic
  Vec& operator+=(const Vec& other);
  Vec& operator-=(const Vec& other);
  Vec& operator*=(const Vec& other);
  Vec& operator/=(const Vec& other);
  Vec4<Promote<T>> operator-() const;
  template <class U>
  Vec4<Promote<T, U>> operator+(const Vec4<U>& other) const;
  template <class U>
  Vec4<Promote<T, U>> operator-(const Vec4<U>& other) const;
  template <class U>
  Vec4<Promote<T, U>> operator*(const Vec4<U>& other) const;
  template <class U>
  Vec4<Promote<T, U>> operator/(const Vec4<U>& other) const;

  // Scalar arithmetic
  Vec& operator+=(T scalar);
  Vec& operator-=(T scalar);
  Vec& operator*=(T scalar);
  Vec& operator/=(T scalar);
  template <class U, EnableIfScalar<U> * = nullptr>
  Vec4<Promote<T, U>> operator+(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Vec4<Promote<T, U>> operator-(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Vec4<Promote<T, U>> operator*(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Vec4<Promote<T, U>> operator/(U scalar) const;

  // Attributes
  bool empty() const { return !x && !y && !z && !w; }

  // Angle
  Promote<T> headingXY() const;
  Promote<T> headingYZ() const;
  Promote<T> headingZX() const;
  template <class U>
  Promote<T, U> angle(const Vec4<U>& other) const;

  // Magnitude
  Promote<T> magnitude() const;
  Promote<T> magnitudeSquared() const;
  template <class U>
  Vec& limit(U limit);
  template <class U>
  Vec4<Promote<T, U>> limited(U limit) const;

  // Normalization
  bool normal() const { return magnitude() == 1; }
  Vec& normalize();
  Vec4<Promote<T>> normalized() const;

  // Inversion
  Vec& invert();
  Vec4<Promote<T>> inverted() const;

  // Distance
  template <class U = T>
  Promote<T, U> distance(const Vec4<U>& other) const;
  template <class U = T>
  Promote<T, U> distanceSquared(const Vec4<U>& other) const;

  // Product
  template <class U = T>
  Promote<T, U> dot(const Vec4<U>& other) const;
  template <class U = T>
  Vec4<Promote<T, U>> cross(const Vec4<U>& other) const;

  // Interpolation
  template <class V, class U = T>
  Vec4<Promote<T, U>> lerp(const Vec4<U>& other, V factor) const;

  // Jitter
  template <class U = T>
  Vec& jitter(const Vec4<U>& vector);
  template <class Random, class U = T>
  Vec& jitter(const Vec4<U>& vector, Random *random);
  template <class U = T>
  Vec4<Promote<T, U>> jittered(const Vec4<U>& vector) const;
  template <class Random, class U = T>
  Vec4<Promote<T, U>> jittered(const Vec4<U>& vector, Random *random) const;

  // Iterator
  Iterator begin() { return &x; }
  ConstIterator begin() const { return &x; }
  Iterator end() { return &w + 1; }
  ConstIterator end() const { return &w + 1; }
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
  T z;
  T w;
};

// Scalar arithmetic
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec4<Promote<T, U>> operator+(T lhs, const Vec4<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec4<Promote<T, U>> operator-(T lhs, const Vec4<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec4<Promote<T, U>> operator*(T lhs, const Vec4<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec4<Promote<T, U>> operator/(T lhs, const Vec4<U>& rhs);

using Vec4i = Vec4<int>;
using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;

template <class T, int D>
using Vector = Vec<T, D>;
template <class T>
using Vector4 = Vec4<T>;
using Vector4i = Vec4i;
using Vector4f = Vec4f;
using Vector4d = Vec4d;

#pragma mark -

template <class T>
inline Vec<T, 4>::Vec() : x(), y(), z(), w() {}

template <class T>
inline Vec<T, 4>::Vec(T value) : x(value), y(value), z(value), w(value) {}

template <class T>
inline Vec<T, 4>::Vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

template <class T>
inline Vec<T, 4>::Vec(const T *values, int size) {
  set(values, size);
}

template <class T>
template <class... Args>
inline Vec<T, 4>::Vec(const std::tuple<Args...>& tuple) {
  set(tuple);
}

template <class T>
inline Vec<T, 4>::Vec(std::initializer_list<T> list) {
  set(list);
}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Vec<T, 4>::Vec(const Vec4<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z),
      w(other.w) {}

#if TAKRAM_HAS_OPENFRAMEWORKS

template <class T>
inline Vec<T, 4>::Vec(const ofVec4f& other)
    : x(other.x),
      y(other.y),
      z(other.z),
      w(other.w) {}

template <class T>
inline Vec<T, 4>::operator ofVec4f() const {
  return ofVec4f(x, y, z, w);
}

#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER

template <class T>
template <class U>
inline Vec<T, 4>::Vec(const ci::Vec4<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z),
      w(other.w) {}

template <class T>
template <class U>
inline Vec<T, 4>::operator ci::Vec4<U>() const {
  return ci::Vec4<U>(x, y, z, w);
}

#endif  // TAKRAM_HAS_CINDER

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Vec<T, 4>::Vec(const Vec2<U>& other)
    : x(other.x),
      y(other.y),
      z(),
      w() {}

template <class T>
template <class U>
inline Vec<T, 4>::Vec(const Vec3<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z),
      w() {}

#if TAKRAM_HAS_OPENCV

template <class T>
template <class U>
inline Vec<T, 4>::Vec(const cv::Vec<U, 4>& other) : Vec(other.val, 4) {}

template <class T>
template <class U>
inline Vec<T, 4>::operator cv::Vec<U, 4>() const {
  return cv::Vec<U, 4>(x, y, z, w);
}

#endif  // TAKRAM_HAS_OPENCV

#pragma mark Factory

template <class T>
inline Vec4<T> Vec<T, 4>::min() {
  return Vec(std::numeric_limits<T>::min(),
             std::numeric_limits<T>::min(),
             std::numeric_limits<T>::min(),
             std::numeric_limits<T>::min());
}

template <class T>
inline Vec4<T> Vec<T, 4>::max() {
  return Vec(std::numeric_limits<T>::max(),
             std::numeric_limits<T>::max(),
             std::numeric_limits<T>::max(),
             std::numeric_limits<T>::max());
}

template <class T>
inline Vec4<T> Vec<T, 4>::headingXY(Promote<T> angle) {
  return Vec(std::cos(angle), std::sin(angle));
}

template <class T>
inline Vec4<T> Vec<T, 4>::headingYZ(Promote<T> angle) {
  return Vec(std::cos(angle), T(), std::sin(angle));
}

template <class T>
inline Vec4<T> Vec<T, 4>::headingZX(Promote<T> angle) {
  return Vec(T(), std::cos(angle), std::sin(angle));
}

template <class T>
inline Vec4<T> Vec<T, 4>::random() {
  return random(&Random<>::shared());
}

template <class T>
inline Vec4<T> Vec<T, 4>::random(T max) {
  return random(max, &Random<>::shared());
}

template <class T>
inline Vec4<T> Vec<T, 4>::random(T min, T max) {
  return random(min, max, &Random<>::shared());
}

template <class T>
template <class Random>
inline Vec4<T> Vec<T, 4>::random(Random *random) {
  return Vec::random(std::numeric_limits<T>::min(),
                     std::numeric_limits<T>::max(),
                     random);
}

template <class T>
template <class Random>
inline Vec4<T> Vec<T, 4>::random(T max, Random *random) {
  return Vec::random(T(), max, random);
}

template <class T>
template <class Random>
inline Vec4<T> Vec<T, 4>::random(T min, T max, Random *random) {
  assert(random);
  return Vec(random->template uniform<T>(min, max),
             random->template uniform<T>(min, max),
             random->template uniform<T>(min, max),
             random->template uniform<T>(min, max));
}

#pragma mark Mutators

template <class T>
inline void Vec<T, 4>::set(T value) {
  x = y = z = w = value;
}

template <class T>
inline void Vec<T, 4>::set(T x, T y, T z, T w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

template <class T>
inline void Vec<T, 4>::set(const T *values, int size) {
  reset();
  const auto end = values + size;
  if (values == end) return;
  x = *values;
  if (++values == end) return;
  y = *values;
  if (++values == end) return;
  z = *values;
  if (++values == end) return;
  w = *values;
}

template <class T>
template <class... Args>
inline void Vec<T, 4>::set(const std::tuple<Args...>& tuple) {
  std::tie(x, y, z, w) = tuple;
}

template <class T>
inline void Vec<T, 4>::set(std::initializer_list<T> list) {
  reset();
  auto itr = std::begin(list);
  if (itr == std::end(list)) return;
  x = *itr;
  if (++itr == std::end(list)) return;
  y = *itr;
  if (++itr == std::end(list)) return;
  z = *itr;
  if (++itr == std::end(list)) return;
  w = *itr;
}

template <class T>
inline void Vec<T, 4>::reset() {
  *this = Vec();
}

#pragma mark Element access

template <class T>
inline T& Vec<T, 4>::at(int index) {
  switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default:
      assert(false);
      break;
  }
  return x;
}

template <class T>
inline const T& Vec<T, 4>::at(int index) const {
  switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default:
      assert(false);
      break;
  }
  return x;
}

template <class T>
inline T& Vec<T, 4>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <class T>
inline const T& Vec<T, 4>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Vec<T, 4>::operator==(const Vec4<U>& other) const {
  return x == other.x && y == other.y && z == other.z && w == other.w;
}

template <class T>
template <class U>
inline bool Vec<T, 4>::operator!=(const Vec4<U>& other) const {
  return !operator==(other);
}

template <class T>
template <class U>
inline bool Vec<T, 4>::operator<(const Vec4<U>& other) const {
  return x < other.x || (x == other.x &&
        (y < other.y || (y == other.y &&
        (z < other.y || (z == other.y && w < other.w)))));
}

template <class T>
template <class U>
inline bool Vec<T, 4>::operator>(const Vec4<U>& other) const {
  return x > other.x || (x == other.x &&
        (y > other.y || (y == other.y &&
        (z > other.y || (z == other.y && w > other.w)))));
}

template <class T>
template <class U>
inline bool Vec<T, 4>::operator<=(const Vec4<U>& other) const {
  return operator<(other) || operator==(other);
}

template <class T>
template <class U>
inline bool Vec<T, 4>::operator>=(const Vec4<U>& other) const {
  return operator>(other) || operator==(other);
}

template <class T>
template <class V, class U>
inline bool Vec<T, 4>::equals(const Vec4<U>& other, V tolerance) const {
  return (std::abs(x - other.x) <= tolerance &&
          std::abs(y - other.y) <= tolerance &&
          std::abs(z - other.z) <= tolerance &&
          std::abs(w - other.w) <= tolerance);
}

#pragma mark Arithmetic

template <class T>
inline Vec4<T>& Vec<T, 4>::operator+=(const Vec& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  w += other.w;
  return *this;
}

template <class T>
inline Vec4<T>& Vec<T, 4>::operator-=(const Vec& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  w -= other.w;
  return *this;
}

template <class T>
inline Vec4<T>& Vec<T, 4>::operator*=(const Vec& other) {
  x *= other.x;
  y *= other.y;
  z *= other.z;
  w *= other.w;
  return *this;
}

template <class T>
inline Vec4<T>& Vec<T, 4>::operator/=(const Vec& other) {
  x /= other.x;
  y /= other.y;
  z /= other.z;
  w /= other.w;
  return *this;
}

template <class T>
inline Vec4<Promote<T>> Vec<T, 4>::operator-() const {
  using V = Promote<T>;
  return Vec4<V>(-static_cast<V>(x),
                 -static_cast<V>(y),
                 -static_cast<V>(z),
                 -static_cast<V>(w));
}

template <class T>
template <class U>
inline Vec4<Promote<T, U>> Vec<T, 4>::operator+(const Vec4<U>& other) const {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(x) + other.x,
                 static_cast<V>(y) + other.y,
                 static_cast<V>(z) + other.z,
                 static_cast<V>(w) + other.w);
}

template <class T>
template <class U>
inline Vec4<Promote<T, U>> Vec<T, 4>::operator-(const Vec4<U>& other) const {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(x) - other.x,
                 static_cast<V>(y) - other.y,
                 static_cast<V>(z) - other.z,
                 static_cast<V>(w) - other.w);
}

template <class T>
template <class U>
inline Vec4<Promote<T, U>> Vec<T, 4>::operator*(const Vec4<U>& other) const {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(x) * other.x,
                 static_cast<V>(y) * other.y,
                 static_cast<V>(z) * other.z,
                 static_cast<V>(w) * other.w);
}

template <class T>
template <class U>
inline Vec4<Promote<T, U>> Vec<T, 4>::operator/(const Vec4<U>& other) const {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(x) / other.x,
                 static_cast<V>(y) / other.y,
                 static_cast<V>(z) / other.z,
                 static_cast<V>(w) / other.w);
}

#pragma mark Scalar arithmetic

template <class T>
inline Vec4<T>& Vec<T, 4>::operator+=(T scalar) {
  x += scalar;
  y += scalar;
  z += scalar;
  w += scalar;
  return *this;
}

template <class T>
inline Vec4<T>& Vec<T, 4>::operator-=(T scalar) {
  x -= scalar;
  y -= scalar;
  z -= scalar;
  w -= scalar;
  return *this;
}

template <class T>
inline Vec4<T>& Vec<T, 4>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  w *= scalar;
  return *this;
}

template <class T>
inline Vec4<T>& Vec<T, 4>::operator/=(T scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
  w /= scalar;
  return *this;
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Vec4<Promote<T, U>> Vec<T, 4>::operator+(U scalar) const {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(x) + scalar,
                 static_cast<V>(y) + scalar,
                 static_cast<V>(z) + scalar,
                 static_cast<V>(w) + scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Vec4<Promote<T, U>> Vec<T, 4>::operator-(U scalar) const {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(x) - scalar,
                 static_cast<V>(y) - scalar,
                 static_cast<V>(z) - scalar,
                 static_cast<V>(w) - scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Vec4<Promote<T, U>> Vec<T, 4>::operator*(U scalar) const {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(x) * scalar,
                 static_cast<V>(y) * scalar,
                 static_cast<V>(z) * scalar,
                 static_cast<V>(w) * scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Vec4<Promote<T, U>> Vec<T, 4>::operator/(U scalar) const {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(x) / scalar,
                 static_cast<V>(y) / scalar,
                 static_cast<V>(z) / scalar,
                 static_cast<V>(w) / scalar);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec4<Promote<T, U>> operator+(T lhs, const Vec4<U>& rhs) {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(lhs) + rhs.x,
                 static_cast<V>(lhs) + rhs.y,
                 static_cast<V>(lhs) + rhs.z,
                 static_cast<V>(lhs) + rhs.w);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec4<Promote<T, U>> operator-(T lhs, const Vec4<U>& rhs) {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(lhs) - rhs.x,
                 static_cast<V>(lhs) - rhs.y,
                 static_cast<V>(lhs) - rhs.z,
                 static_cast<V>(lhs) - rhs.w);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec4<Promote<T, U>> operator*(T lhs, const Vec4<U>& rhs) {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(lhs) * rhs.x,
                 static_cast<V>(lhs) * rhs.y,
                 static_cast<V>(lhs) * rhs.z,
                 static_cast<V>(lhs) * rhs.w);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec4<Promote<T, U>> operator/(T lhs, const Vec4<U>& rhs) {
  using V = Promote<T, U>;
  return Vec4<V>(static_cast<V>(lhs) / rhs.x,
                 static_cast<V>(lhs) / rhs.y,
                 static_cast<V>(lhs) / rhs.z,
                 static_cast<V>(lhs) / rhs.w);
}

#pragma mark Attributes

template <class T>
inline Promote<T> Vec<T, 4>::headingXY() const {
  return std::atan2(y, x);
}

template <class T>
inline Promote<T> Vec<T, 4>::headingYZ() const {
  return std::atan2(z, y);
}

template <class T>
inline Promote<T> Vec<T, 4>::headingZX() const {
  return std::atan2(x, z);
}

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 4>::angle(const Vec4<U>& other) const {
  return std::acos(normalized().dot(other.normalized()));
}

#pragma mark Magnitude

template <class T>
inline Promote<T> Vec<T, 4>::magnitude() const {
  return std::sqrt(magnitudeSquared());
}

template <class T>
inline Promote<T> Vec<T, 4>::magnitudeSquared() const {
  return static_cast<Promote<T>>(x) * x + y * y + z * z + w * w;
}

template <class T>
template <class U>
inline Vec4<T>& Vec<T, 4>::limit(U limit) {
  if (magnitudeSquared() > static_cast<Promote<T>>(limit) * limit) {
    normalize();
    *this *= limit;
  }
  return *this;
}

template <class T>
template <class U>
inline Vec4<Promote<T, U>> Vec<T, 4>::limited(U limit) const {
  return Vec4<Promote<T, U>>(*this).limit(limit);
}

#pragma mark Normalization

template <class T>
inline Vec4<T>& Vec<T, 4>::normalize() {
  const auto denominator = magnitude();
  if (denominator) {
    *this /= denominator;
  }
  return *this;
}

template <class T>
inline Vec4<Promote<T>> Vec<T, 4>::normalized() const {
  return Vec4<Promote<T>>(*this).normalize();
}

#pragma mark Inversion

template <class T>
inline Vec4<T>& Vec<T, 4>::invert() {
  x *= -1;
  y *= -1;
  z *= -1;
  w *= -1;
  return *this;
}

template <class T>
inline Vec4<Promote<T>> Vec<T, 4>::inverted() const {
  return Vec4<Promote<T>>(*this).invert();
}

#pragma mark Distance

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 4>::distance(const Vec4<U>& other) const {
  return (*this - other).magnitude();
}

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 4>::distanceSquared(const Vec4<U>& other) const {
  return (*this - other).magnitudeSquared();
}

#pragma mark Products

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 4>::dot(const Vec4<U>& other) const {
  using V = Promote<T, U>;
  return static_cast<V>(x) * other.x + y * other.y + z * other.z + w * other.w;
}

template <class T>
template <class U>
inline Vec4<Promote<T, U>> Vec<T, 4>::cross(const Vec4<U>& other) const {
  return Vec3<T>(*this).cross(Vec3<U>(other));
}

#pragma mark Interpolation

template <class T>
template <class V, class U>
inline Vec4<Promote<T, U>> Vec<T, 4>::lerp(const Vec4<U>& other,
                                           V factor) const {
  return Vec4<Promote<T, U>>(x + (other.x - x) * factor,
                             y + (other.y - y) * factor,
                             z + (other.z - z) * factor,
                             w + (other.w - w) * factor);
}

#pragma mark Jitter

template <class T>
template <class U>
inline Vec4<T>& Vec<T, 4>::jitter(const Vec4<U>& vector) {
  return jitter(vector, &Random<>::shared());
}

template <class T>
template <class Random, class U>
inline Vec4<T>& Vec<T, 4>::jitter(const Vec4<U>& vector, Random *random) {
  if (vector.empty()) {
    return *this;
  }
  using V = Promote<T, U>;
  x += vector.x * random->template uniform<V>(-1, 1);
  y += vector.y * random->template uniform<V>(-1, 1);
  z += vector.z * random->template uniform<V>(-1, 1);
  w += vector.w * random->template uniform<V>(-1, 1);
  return *this;
}

template <class T>
template <class U>
inline Vec4<Promote<T, U>> Vec<T, 4>::jittered(const Vec4<U>& vector) const {
  return Vec4<Promote<T, U>>(*this).jitter(vector);
}

template <class T>
template <class Random, class U>
inline Vec4<Promote<T, U>> Vec<T, 4>::jittered(const Vec4<U>& vector,
                                               Random *random) const {
  return Vec4<Promote<T, U>>(*this).jitter(vector, random);
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Vec4<T>& vector) {
  return os << "( " << vector.x << ", " << vector.y << ", " << vector.z
            << ", " << vector.w << " )";
}

}  // namespace math

using math::Vec;
using math::Vec4;
using math::Vec4i;
using math::Vec4f;
using math::Vec4d;

using math::Vector;
using math::Vector4;
using math::Vector4i;
using math::Vector4f;
using math::Vector4d;

}  // namespace takram

template <class T>
struct std::hash<takram::math::Vec4<T>> {
  std::size_t operator()(const takram::math::Vec4<T>& value) const {
    std::hash<T> hash;
    return ((hash(value.x) << 0) ^
            (hash(value.y) << 1) ^
            (hash(value.z) << 2) ^
            (hash(value.w) << 3));
  }
};

#endif  // TAKRAM_MATH_VECTOR4_H_
