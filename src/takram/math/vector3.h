//
//  takram/math/vector3.h
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
#ifndef TAKRAM_MATH_VECTOR3_H_
#define TAKRAM_MATH_VECTOR3_H_

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
#include "ofVec3f.h"
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
class Vec;

template <class T>
using Vec2 = Vec<T, 2>;
template <class T>
using Vec3 = Vec<T, 3>;
template <class T>
using Vec4 = Vec<T, 4>;

template <class T>
class Vec<T, 3> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const int dimensions = 3;

 public:
  Vec();
  explicit Vec(T value);
  Vec(T x, T y, T z = T());
  explicit Vec(const T *values, int size = 3);
  template <class... Args>
  Vec(const std::tuple<Args...>& tuple);
  Vec(std::initializer_list<T> list);

  // Implicit conversion
  template <class U>
  Vec(const Vec3<U>& other);

#if TAKRAM_HAS_OPENCV
  template <class U>
  Vec(const cv::Point3_<U>& other);
  template <class U>
  operator cv::Point3_<U>() const;
#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS
  Vec(const ofVec3f& other);
  operator ofVec3f() const;
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
  template <class U>
  Vec(const ci::Vec3<U>& other);
  template <class U>
  operator ci::Vec3<U>() const;
#endif  // TAKRAM_HAS_CINDER

  // Explicit conversion
  template <class U>
  explicit Vec(const Vec2<U>& other);
  template <class U>
  explicit Vec(const Vec4<U>& other);

#if TAKRAM_HAS_OPENCV
  template <class U>
  explicit Vec(const cv::Vec<U, 3>& other);
  template <class U>
  explicit operator cv::Vec<U, 3>() const;
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
  void set(T x, T y, T z = T());
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
  T& back() { return z; }
  const T& back() const { return z; }

  // Comparison
  template <class V, class U = T>
  bool equals(const Vec3<U>& other, V tolerance) const;

  // Arithmetic
  Vec& operator+=(const Vec& other);
  Vec& operator-=(const Vec& other);
  Vec& operator*=(const Vec& other);
  Vec& operator/=(const Vec& other);
  Vec3<Promote<T>> operator-() const;

  // Scalar arithmetic
  Vec& operator+=(T scalar);
  Vec& operator-=(T scalar);
  Vec& operator*=(T scalar);
  Vec& operator/=(T scalar);

  // Attributes
  bool empty() const { return !x && !y && !z; }

  // Angle
  Promote<T> headingXY() const;
  Promote<T> headingYZ() const;
  Promote<T> headingZX() const;
  template <class U = T>
  Promote<T, U> angle(const Vec3<U>& other) const;

  // Magnitude
  Promote<T> magnitude() const;
  Promote<T> magnitudeSquared() const;
  template <class U>
  Vec& limit(U limit);
  template <class U>
  Vec3<Promote<T, U>> limited(U limit) const;

  // Normalization
  bool normal() const { return magnitude() == 1; }
  Vec& normalize();
  Vec3<Promote<T>> normalized() const;

  // Inversion
  Vec& invert();
  Vec3<Promote<T>> inverted() const;

  // Distance
  template <class U = T>
  Promote<T, U> distance(const Vec3<U>& other) const;
  template <class U = T>
  Promote<T, U> distanceSquared(const Vec3<U>& other) const;

  // Products
  template <class U = T>
  Promote<T, U> dot(const Vec3<U>& other) const;
  template <class U = T>
  Vec3<Promote<T, U>> cross(const Vec3<U>& other) const;

  // Interpolation
  template <class V, class U = T>
  Vec3<Promote<T, U>> lerp(const Vec3<U>& other, V factor) const;

  // Jitter
  template <class U = T>
  Vec& jitter(const Vec3<U>& vector);
  template <class Random, class U = T>
  Vec& jitter(const Vec3<U>& vector, Random *random);
  template <class U = T>
  Vec3<Promote<T, U>> jittered(const Vec3<U>& vector) const;
  template <class Random, class U = T>
  Vec3<Promote<T, U>> jittered(const Vec3<U>& vector, Random *random) const;

  // Coordinate system conversion
  Vec3<Promote<T>> cartesian() const;
  Vec3<Promote<T>> spherical() const;

  // Iterator
  Iterator begin() { return &x; }
  ConstIterator begin() const { return &x; }
  Iterator end() { return &z + 1; }
  ConstIterator end() const { return &z + 1; }
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
};

// Comparison
template <class T, class U>
bool operator==(const Vec3<T>& lhs, const Vec3<U>& rhs);
template <class T, class U>
bool operator!=(const Vec3<T>& lhs, const Vec3<U>& rhs);
template <class T, class U>
bool operator<(const Vec3<T>& lhs, const Vec3<U>& rhs);
template <class T, class U>
bool operator>(const Vec3<T>& lhs, const Vec3<U>& rhs);
template <class T, class U>
bool operator<=(const Vec3<T>& lhs, const Vec3<U>& rhs);
template <class T, class U>
bool operator>=(const Vec3<T>& lhs, const Vec3<U>& rhs);

// Arithmetic
template <class T, class U>
Vec3<Promote<T, U>> operator+(const Vec3<T>& lhs, const Vec3<U>& rhs);
template <class T, class U>
Vec3<Promote<T, U>> operator-(const Vec3<T>& lhs, const Vec3<U>& rhs);
template <class T, class U>
Vec3<Promote<T, U>> operator*(const Vec3<T>& lhs, const Vec3<U>& rhs);
template <class T, class U>
Vec3<Promote<T, U>> operator/(const Vec3<T>& lhs, const Vec3<U>& rhs);

// Scalar arithmetic
template <class T, class U, EnableIfScalar<U> * = nullptr>
Vec3<Promote<T, U>> operator+(const Vec3<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<U> * = nullptr>
Vec3<Promote<T, U>> operator-(const Vec3<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<U> * = nullptr>
Vec3<Promote<T, U>> operator*(const Vec3<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<U> * = nullptr>
Vec3<Promote<T, U>> operator/(const Vec3<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec3<Promote<T, U>> operator+(T lhs, const Vec3<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec3<Promote<T, U>> operator-(T lhs, const Vec3<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec3<Promote<T, U>> operator*(T lhs, const Vec3<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Vec3<Promote<T, U>> operator/(T lhs, const Vec3<U>& rhs);

using Vec3i = Vec3<int>;
using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;

template <class T, int D>
using Vector = Vec<T, D>;
template <class T>
using Vector3 = Vec3<T>;
using Vector3i = Vec3i;
using Vector3f = Vec3f;
using Vector3d = Vec3d;

#pragma mark -

template <class T>
inline Vec<T, 3>::Vec() : x(), y(), z() {}

template <class T>
inline Vec<T, 3>::Vec(T value) : x(value), y(value), z(value) {}

template <class T>
inline Vec<T, 3>::Vec(T x, T y, T z) : x(x), y(y), z(z) {}

template <class T>
inline Vec<T, 3>::Vec(const T *values, int size) {
  set(values, size);
}

template <class T>
template <class... Args>
inline Vec<T, 3>::Vec(const std::tuple<Args...>& tuple) {
  set(tuple);
}

template <class T>
inline Vec<T, 3>::Vec(std::initializer_list<T> list) {
  set(list);
}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Vec<T, 3>::Vec(const Vec3<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z) {}

#if TAKRAM_HAS_OPENCV

template <class T>
template <class U>
inline Vec<T, 3>::Vec(const cv::Point3_<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z) {}

template <class T>
template <class U>
inline Vec<T, 3>::operator cv::Point3_<U>() const {
  return cv::Point3_<U>(x, y, z);
}

#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS

template <class T>
inline Vec<T, 3>::Vec(const ofVec3f& other)
    : x(other.x),
      y(other.y),
      z(other.z) {}

template <class T>
inline Vec<T, 3>::operator ofVec3f() const {
  return ofVec3f(x, y, z);
}

#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER

template <class T>
template <class U>
inline Vec<T, 3>::Vec(const ci::Vec3<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z) {}

template <class T>
template <class U>
inline Vec<T, 3>::operator ci::Vec3<U>() const {
  return ci::Vec3<U>(x, y, z);
}

#endif  // TAKRAM_HAS_CINDER

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Vec<T, 3>::Vec(const Vec2<U>& other)
    : x(other.x),
      y(other.y),
      z() {}

template <class T>
template <class U>
inline Vec<T, 3>::Vec(const Vec4<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z) {}

#if TAKRAM_HAS_OPENCV

template <class T>
template <class U>
inline Vec<T, 3>::Vec(const cv::Vec<U, 3>& other) : Vec(other.val, 3) {}

template <class T>
template <class U>
inline Vec<T, 3>::operator cv::Vec<U, 3>() const {
  return cv::Vec<U, 3>(x, y, z);
}

#endif  // TAKRAM_HAS_OPENCV

#pragma mark Factory

template <class T>
inline Vec3<T> Vec<T, 3>::min() {
  return Vec(std::numeric_limits<T>::min(),
             std::numeric_limits<T>::min(),
             std::numeric_limits<T>::min());
}

template <class T>
inline Vec3<T> Vec<T, 3>::max() {
  return Vec(std::numeric_limits<T>::max(),
             std::numeric_limits<T>::max(),
             std::numeric_limits<T>::max());
}

template <class T>
inline Vec3<T> Vec<T, 3>::headingXY(Promote<T> angle) {
  return Vec(std::cos(angle), std::sin(angle));
}

template <class T>
inline Vec3<T> Vec<T, 3>::headingYZ(Promote<T> angle) {
  return Vec(std::cos(angle), T(), std::sin(angle));
}

template <class T>
inline Vec3<T> Vec<T, 3>::headingZX(Promote<T> angle) {
  return Vec(T(), std::cos(angle), std::sin(angle));
}

template <class T>
inline Vec3<T> Vec<T, 3>::random() {
  return random(&Random<>::shared());
}

template <class T>
inline Vec3<T> Vec<T, 3>::random(T max) {
  return random(max, &Random<>::shared());
}

template <class T>
inline Vec3<T> Vec<T, 3>::random(T min, T max) {
  return random(min, max, &Random<>::shared());
}

template <class T>
template <class Random>
inline Vec3<T> Vec<T, 3>::random(Random *random) {
  return Vec::random(std::numeric_limits<T>::min(),
                     std::numeric_limits<T>::max(),
                     random);
}

template <class T>
template <class Random>
inline Vec3<T> Vec<T, 3>::random(T max, Random *random) {
  return Vec::random(T(), max, random);
}

template <class T>
template <class Random>
inline Vec3<T> Vec<T, 3>::random(T min, T max, Random *random) {
  assert(random);
  return Vec(random->template uniform<T>(min, max),
             random->template uniform<T>(min, max),
             random->template uniform<T>(min, max));
}

#pragma mark Mutators

template <class T>
inline void Vec<T, 3>::set(T value) {
  x = y = z = value;
}

template <class T>
inline void Vec<T, 3>::set(T x, T y, T z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

template <class T>
inline void Vec<T, 3>::set(const T *values, int size) {
  reset();
  const auto end = values + size;
  if (values == end) return;
  x = *values;
  if (++values == end) return;
  y = *values;
  if (++values == end) return;
  z = *values;
}

template <class T>
template <class... Args>
inline void Vec<T, 3>::set(const std::tuple<Args...>& tuple) {
  std::tie(x, y, z) = tuple;
}

template <class T>
inline void Vec<T, 3>::set(std::initializer_list<T> list) {
  reset();
  auto itr = std::begin(list);
  if (itr == std::end(list)) return;
  x = *itr;
  if (++itr == std::end(list)) return;
  y = *itr;
  if (++itr == std::end(list)) return;
  z = *itr;
}

template <class T>
inline void Vec<T, 3>::reset() {
  *this = Vec();
}

#pragma mark Element access

template <class T>
inline T& Vec<T, 3>::at(int index) {
  switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default:
      assert(false);
      break;
  }
  return x;
}

template <class T>
inline const T& Vec<T, 3>::at(int index) const {
  switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default:
      assert(false);
      break;
  }
  return x;
}

template <class T>
inline T& Vec<T, 3>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <class T>
inline const T& Vec<T, 3>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <class T, class U>
inline bool operator==(const Vec3<T>& lhs, const Vec3<U>& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <class T, class U>
inline bool operator!=(const Vec3<T>& lhs, const Vec3<U>& rhs) {
  return !(lhs == rhs);
}

template <class T, class U>
inline bool operator<(const Vec3<T>& lhs, const Vec3<U>& rhs) {
  return lhs.x < rhs.x || (lhs.x == rhs.x &&
        (lhs.y < rhs.y || (lhs.y == rhs.y && lhs.z < rhs.z)));
}

template <class T, class U>
inline bool operator>(const Vec3<T>& lhs, const Vec3<U>& rhs) {
  return lhs.x > rhs.x || (lhs.x == rhs.x &&
        (lhs.y > rhs.y || (lhs.y == rhs.y && lhs.z > rhs.z)));
}

template <class T, class U>
inline bool operator<=(const Vec3<T>& lhs, const Vec3<U>& rhs) {
  return lhs < rhs || lhs == rhs;
}

template <class T, class U>
inline bool operator>=(const Vec3<T>& lhs, const Vec3<U>& rhs) {
  return lhs > rhs || lhs == rhs;
}

template <class T>
template <class V, class U>
inline bool Vec<T, 3>::equals(const Vec3<U>& other, V tolerance) const {
  return (std::abs(x - other.x) <= tolerance &&
          std::abs(y - other.y) <= tolerance &&
          std::abs(z - other.z) <= tolerance);
}

#pragma mark Arithmetic

template <class T>
inline Vec3<T>& Vec<T, 3>::operator+=(const Vec& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

template <class T>
inline Vec3<T>& Vec<T, 3>::operator-=(const Vec& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

template <class T>
inline Vec3<T>& Vec<T, 3>::operator*=(const Vec& other) {
  x *= other.x;
  y *= other.y;
  z *= other.z;
  return *this;
}

template <class T>
inline Vec3<T>& Vec<T, 3>::operator/=(const Vec& other) {
  x /= other.x;
  y /= other.y;
  z /= other.z;
  return *this;
}

template <class T>
inline Vec3<Promote<T>> Vec<T, 3>::operator-() const {
  using V = Promote<T>;
  return Vec3<V>(-static_cast<V>(x), -static_cast<V>(y), -static_cast<V>(z));
}

template <class T, class U>
inline Vec3<Promote<T, U>> operator+(const Vec3<T>& lhs, const Vec3<U>& rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(lhs.x) + rhs.x,
                 static_cast<V>(lhs.y) + rhs.y,
                 static_cast<V>(lhs.z) + rhs.z);
}

template <class T, class U>
inline Vec3<Promote<T, U>> operator-(const Vec3<T>& lhs, const Vec3<U>& rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(lhs.x) - rhs.x,
                 static_cast<V>(lhs.y) - rhs.y,
                 static_cast<V>(lhs.z) - rhs.z);
}

template <class T, class U>
inline Vec3<Promote<T, U>> operator*(const Vec3<T>& lhs, const Vec3<U>& rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(lhs.x) * rhs.x,
                 static_cast<V>(lhs.y) * rhs.y,
                 static_cast<V>(lhs.z) * rhs.z);
}

template <class T, class U>
inline Vec3<Promote<T, U>> operator/(const Vec3<T>& lhs, const Vec3<U>& rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<Promote<T, U>>(lhs.x) / rhs.x,
                 static_cast<Promote<T, U>>(lhs.y) / rhs.y,
                 static_cast<Promote<T, U>>(lhs.z) / rhs.z);
}

#pragma mark Scalar arithmetic

template <class T>
inline Vec3<T>& Vec<T, 3>::operator+=(T scalar) {
  x += scalar;
  y += scalar;
  z += scalar;
  return *this;
}

template <class T>
inline Vec3<T>& Vec<T, 3>::operator-=(T scalar) {
  x -= scalar;
  y -= scalar;
  z -= scalar;
  return *this;
}

template <class T>
inline Vec3<T>& Vec<T, 3>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

template <class T>
inline Vec3<T>& Vec<T, 3>::operator/=(T scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
  return *this;
}

template <class T, class U, EnableIfScalar<U> *>
inline Vec3<Promote<T, U>> operator+(const Vec3<T>& lhs, U rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(lhs.x) + rhs,
                 static_cast<V>(lhs.y) + rhs,
                 static_cast<V>(lhs.z) + rhs);
}

template <class T, class U, EnableIfScalar<U> *>
inline Vec3<Promote<T, U>> operator-(const Vec3<T>& lhs, U rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(lhs.x) - rhs,
                 static_cast<V>(lhs.y) - rhs,
                 static_cast<V>(lhs.z) - rhs);
}

template <class T, class U, EnableIfScalar<U> *>
inline Vec3<Promote<T, U>> operator*(const Vec3<T>& lhs, U rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(lhs.x) * rhs,
                 static_cast<V>(lhs.y) * rhs,
                 static_cast<V>(lhs.z) * rhs);
}

template <class T, class U, EnableIfScalar<U> *>
inline Vec3<Promote<T, U>> operator/(const Vec3<T>& lhs, U rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(lhs.x) / rhs,
                 static_cast<V>(lhs.y) / rhs,
                 static_cast<V>(lhs.z) / rhs);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec3<Promote<T, U>> operator+(T lhs, const Vec3<U>& rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(lhs) + rhs.x,
                 static_cast<V>(lhs) + rhs.y,
                 static_cast<V>(lhs) + rhs.z);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec3<Promote<T, U>> operator-(T lhs, const Vec3<U>& rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(lhs) - rhs.x,
                 static_cast<V>(lhs) - rhs.y,
                 static_cast<V>(lhs) - rhs.z);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec3<Promote<T, U>> operator*(T lhs, const Vec3<U>& rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(lhs) * rhs.x,
                 static_cast<V>(lhs) * rhs.y,
                 static_cast<V>(lhs) * rhs.z);
}

template <class T, class U, EnableIfScalar<T> *>
inline Vec3<Promote<T, U>> operator/(T lhs, const Vec3<U>& rhs) {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(lhs) / rhs.x,
                 static_cast<V>(lhs) * rhs.y,
                 static_cast<V>(lhs) * rhs.z);
}

#pragma mark Angle

template <class T>
inline Promote<T> Vec<T, 3>::headingXY() const {
  return std::atan2(y, x);
}

template <class T>
inline Promote<T> Vec<T, 3>::headingYZ() const {
  return std::atan2(z, y);
}

template <class T>
inline Promote<T> Vec<T, 3>::headingZX() const {
  return std::atan2(x, z);
}

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 3>::angle(const Vec3<U>& other) const {
  return std::acos(normalized().dot(other.normalized()));
}

#pragma mark Magnitude

template <class T>
inline Promote<T> Vec<T, 3>::magnitude() const {
  return std::sqrt(magnitudeSquared());
}

template <class T>
inline Promote<T> Vec<T, 3>::magnitudeSquared() const {
  return static_cast<Promote<T>>(x) * x + y * y + z * z;
}

template <class T>
template <class U>
inline Vec3<T>& Vec<T, 3>::limit(U limit) {
  if (magnitudeSquared() > static_cast<Promote<T>>(limit) * limit) {
    normalize();
    *this *= limit;
  }
  return *this;
}

template <class T>
template <class U>
inline Vec3<Promote<T, U>> Vec<T, 3>::limited(U limit) const {
  return Vec3<Promote<T, U>>(*this).limit(limit);
}

#pragma mark Normalization

template <class T>
inline Vec3<T>& Vec<T, 3>::normalize() {
  const auto denominator = magnitude();
  if (denominator) {
    *this /= denominator;
  }
  return *this;
}

template <class T>
inline Vec3<Promote<T>> Vec<T, 3>::normalized() const {
  return Vec3<Promote<T>>(*this).normalize();
}

#pragma mark Inversion

template <class T>
inline Vec3<T>& Vec<T, 3>::invert() {
  x *= -1;
  y *= -1;
  z *= -1;
  return *this;
}

template <class T>
inline Vec3<Promote<T>> Vec<T, 3>::inverted() const {
  return Vec3<Promote<T>>(*this).invert();
}

#pragma mark Distance

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 3>::distance(const Vec3<U>& other) const {
  return (*this - other).magnitude();
}

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 3>::distanceSquared(const Vec3<U>& other) const {
  return (*this - other).magnitudeSquared();
}

#pragma mark Products

template <class T>
template <class U>
inline Promote<T, U> Vec<T, 3>::dot(const Vec3<U>& other) const {
  return static_cast<Promote<T, U>>(x) * other.x + y * other.y + z * other.z;
}

template <class T>
template <class U>
inline Vec3<Promote<T, U>> Vec<T, 3>::cross(const Vec3<U>& other) const {
  using V = Promote<T, U>;
  return Vec3<V>(static_cast<V>(y) * other.z - z * other.y,
                 static_cast<V>(z) * other.x - x * other.z,
                 static_cast<V>(x) * other.y - y * other.x);
}

#pragma mark Interpolation

template <class T>
template <class V, class U>
inline Vec3<Promote<T, U>> Vec<T, 3>::lerp(const Vec3<U>& other,
                                           V factor) const {
  return Vec3<Promote<T, U>>(x + (other.x - x) * factor,
                             y + (other.y - y) * factor,
                             z + (other.z - z) * factor);
}

#pragma mark Jitter

template <class T>
template <class U>
inline Vec3<T>& Vec<T, 3>::jitter(const Vec3<U>& vector) {
  return jitter(vector, &Random<>::shared());
}

template <class T>
template <class Random, class U>
inline Vec3<T>& Vec<T, 3>::jitter(const Vec3<U>& vector, Random *random) {
  if (vector.empty()) {
    return *this;
  }
  using V = Promote<T, U>;
  x += vector.x * random->template uniform<V>(-1, 1);
  y += vector.y * random->template uniform<V>(-1, 1);
  z += vector.z * random->template uniform<V>(-1, 1);
  return *this;
}

template <class T>
template <class U>
inline Vec3<Promote<T, U>> Vec<T, 3>::jittered(const Vec3<U>& vector) const {
  return Vec3<Promote<T, U>>(*this).jitter(vector);
}

template <class T>
template <class Random, class U>
inline Vec3<Promote<T, U>> Vec<T, 3>::jittered(const Vec3<U>& vector,
                                               Random *random) const {
  return Vec3<Promote<T, U>>(*this).jitter(vector, random);
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Vec3<T>& vector) {
  return os << "( " << vector.x << ", " << vector.y << ", " << vector.z << " )";
}

}  // namespace math

using math::Vec;
using math::Vec3;
using math::Vec3i;
using math::Vec3f;
using math::Vec3d;

using math::Vector;
using math::Vector3;
using math::Vector3i;
using math::Vector3f;
using math::Vector3d;

}  // namespace takram

template <class T>
struct std::hash<takram::math::Vec3<T>> {
  std::size_t operator()(const takram::math::Vec3<T>& value) const {
    std::hash<T> hash;
    return (hash(value.x) << 0) ^ (hash(value.y) << 1) ^ (hash(value.z) << 2);
  }
};

#endif  // TAKRAM_MATH_VECTOR3_H_
