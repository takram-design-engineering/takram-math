//
//  takram/math/vector4.h
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
#ifndef TAKRAM_MATH_VECTOR4_H_
#define TAKRAM_MATH_VECTOR4_H_

#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <ostream>
#include <tuple>

#if TAKRAM_HAS_OPENFRAMEWORKS
#include "ofVec4f.h"
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
class Vector<T, 4> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const int dimensions = 4;

 public:
  Vector();
  explicit Vector(T value);
  Vector(T x, T y, T z = T(), T w = T());
  explicit Vector(const T *values, int size = dimensions);
  template <class... Args>
  Vector(const std::tuple<Args...>& tuple);
  Vector(std::initializer_list<T> list);

  // Implicit conversion
  template <class U>
  Vector(const Vector4<U>& other);

#if TAKRAM_HAS_OPENFRAMEWORKS
  Vector(const ofVec4f& other);
  operator ofVec4f() const;
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
  template <class U>
  Vector(const ci::Vec4<U>& other);
  operator ci::Vec4<T>() const;
#endif  // TAKRAM_HAS_CINDER

  // Explicit conversion
  template <class U>
  explicit Vector(const Vector2<U>& other);
  template <class U>
  explicit Vector(const Vector3<U>& other);

#if TAKRAM_HAS_OPENCV
  template <class U>
  explicit Vector(const cv::Vec<U, dimensions>& other);
  explicit operator cv::Vec<T, dimensions>() const;
#endif  // TAKRAM_HAS_OPENCV

  // Copy semantics
  Vector(const Vector4<T>& other) = default;
  Vector4<T>& operator=(const Vector4<T>& other) = default;

  // Factory
  static Vector4<T> min();
  static Vector4<T> max();
  template <class Random>
  static Vector4<T> random(Random *random);
  template <class Random>
  static Vector4<T> random(T max, Random *random);
  template <class Random>
  static Vector4<T> random(T min, T max, Random *random);

  // Mutators
  void set(T value);
  void set(T x, T y, T z = T(), T w = T());
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
  T& back() { return w; }
  const T& back() const { return w; }

  // Comparison
  template <class U>
  bool operator==(const Vector4<U>& other) const;
  template <class U>
  bool operator!=(const Vector4<U>& other) const;
  template <class U>
  bool operator<(const Vector4<U>& other) const;
  template <class U>
  bool operator>(const Vector4<U>& other) const;
  template <class U>
  bool operator<=(const Vector4<U>& other) const;
  template <class U>
  bool operator>=(const Vector4<U>& other) const;

  // Arithmetic
  Vector4<T>& operator+=(const Vector4<T>& other);
  Vector4<T>& operator-=(const Vector4<T>& other);
  Vector4<T>& operator*=(const Vector4<T>& other);
  Vector4<T>& operator/=(const Vector4<T>& other);
  template <class U>
  const Vector4<Promote<T, U>> operator+(const Vector4<U>& other) const;
  template <class U>
  const Vector4<Promote<T, U>> operator-(const Vector4<U>& other) const;
  template <class U>
  const Vector4<Promote<T, U>> operator*(const Vector4<U>& other) const;
  template <class U>
  const Vector4<Promote<T, U>> operator/(const Vector4<U>& other) const;
  const Vector4<Promote<T>> operator-() const;

  // Scalar arithmetic
  Vector4<T>& operator+=(T scalar);
  Vector4<T>& operator-=(T scalar);
  Vector4<T>& operator*=(T scalar);
  Vector4<T>& operator/=(T scalar);
  template <class U, EnableIfScalar<U> * = nullptr>
  const Vector4<Promote<T, U>> operator+(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  const Vector4<Promote<T, U>> operator-(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  const Vector4<Promote<T, U>> operator*(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  const Vector4<Promote<T, U>> operator/(U scalar) const;

  // Attributes
  bool empty() const { return !x && !y && !z && !w; }

  // Angle
  Promote<T> headingXY() const;
  Promote<T> headingYZ() const;
  Promote<T> headingZX() const;
  template <class U>
  Promote<T> angle(const Vector4<U>& other) const;

  // Magnitude
  Promote<T> magnitude() const;
  Promote<T> magnitudeSquared() const;
  template <class U>
  Vector4<T>& limit(U limit);
  template <class U>
  Vector4<Promote<T>> limited(U limit) const;

  // Normalization
  bool normal() const { return magnitude() == 1; }
  Vector4<T>& normalize();
  Vector4<Promote<T>> normalized() const;

  // Inversion
  Vector4<T>& invert();
  Vector4<Promote<T>> inverted() const;

  // Distance
  template <class U>
  Promote<T> distance(const Vector4<U>& other) const;
  template <class U>
  Promote<T> distanceSquared(const Vector4<U>& other) const;

  // Product
  template <class U>
  Promote<T, U> dot(const Vector4<U>& other) const;
  template <class U>
  Vector4<Promote<T, U>> cross(const Vector4<U>& other) const;

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

using Vector4i = Vector4<int>;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;

template <class T>
using Vec4 = Vector4<T>;
using Vec4i = Vector4<int>;
using Vec4f = Vector4<float>;
using Vec4d = Vector4<double>;

#pragma mark -

template <class T>
inline Vector4<T>::Vector() : x(), y(), z(), w() {}

template <class T>
inline Vector4<T>::Vector(T value) : x(value), y(value), z(value), w(value) {}

template <class T>
inline Vector4<T>::Vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

template <class T>
inline Vector4<T>::Vector(const T *values, int size) {
  set(values, size);
}

template <class T>
template <class... Args>
inline Vector4<T>::Vector(const std::tuple<Args...>& tuple) {
  set(tuple);
}

template <class T>
inline Vector4<T>::Vector(std::initializer_list<T> list) {
  set(list);
}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Vector4<T>::Vector(const Vector4<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z),
      w(other.w) {}

#if TAKRAM_HAS_OPENFRAMEWORKS

template <class T>
inline Vector4<T>::Vector(const ofVec4f& other)
    : x(other.x),
      y(other.y),
      z(other.z),
      w(other.w) {}

template <class T>
inline Vector4<T>::operator ofVec4f() const {
  return ofVec4f(x, y, z, w);
}

#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER

template <class T>
template <class U>
inline Vector4<T>::Vector(const ci::Vec4<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z),
      w(other.w) {}

template <class T>
inline Vector4<T>::operator ci::Vec4<T>() const {
  return ci::Vec4<T>(x, y, z, w);
}

#endif  // TAKRAM_HAS_CINDER

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Vector4<T>::Vector(const Vector2<U>& other)
    : x(other.x),
      y(other.y),
      z(),
      w() {}

template <class T>
template <class U>
inline Vector4<T>::Vector(const Vector3<U>& other)
    : x(other.x),
      y(other.y),
      z(other.z),
      w() {}

#if TAKRAM_HAS_OPENCV

template <class T>
template <class U>
inline Vector4<T>::Vector(const cv::Vec<U, dimensions>& other)
    : Vector(other.val, dimensions) {}

template <class T>
inline Vector4<T>::operator cv::Vec<T, dimensions>() const {
  return cv::Vec<T, dimensions>(x, y, z, w);
}

#endif  // TAKRAM_HAS_OPENCV

#pragma mark Factory

template <class T>
inline Vector4<T> Vector4<T>::min() {
  return Vector4<T>(std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::min());
}

template <class T>
inline Vector4<T> Vector4<T>::max() {
  return Vector4<T>(std::numeric_limits<T>::max(),
                    std::numeric_limits<T>::max(),
                    std::numeric_limits<T>::max(),
                    std::numeric_limits<T>::max());
}

template <class T>
template <class Random>
inline Vector4<T> Vector4<T>::random(Random *random) {
  return Vector4<T>::random(std::numeric_limits<T>::min(),
                            std::numeric_limits<T>::max(),
                            random);
}

template <class T>
template <class Random>
inline Vector4<T> Vector4<T>::random(T max, Random *random) {
  return Vector4<T>::random(T(), max, random);
}

template <class T>
template <class Random>
inline Vector4<T> Vector4<T>::random(T min, T max, Random *random) {
  assert(random);
  return Vector4<T>(random->template uniform<T>(min, max),
                    random->template uniform<T>(min, max),
                    random->template uniform<T>(min, max),
                    random->template uniform<T>(min, max));
}

#pragma mark Mutators

template <class T>
inline void Vector4<T>::set(T value) {
  x = y = z = w = value;
}

template <class T>
inline void Vector4<T>::set(T x, T y, T z, T w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

template <class T>
inline void Vector4<T>::set(const T *values, int size) {
  reset();
  const auto end = values + size;
  if (values == end) return; x = *values;
  if (++values == end) return; y = *values;
  if (++values == end) return; z = *values;
  if (++values == end) return; w = *values;
}

template <class T>
template <class... Args>
inline void Vector4<T>::set(const std::tuple<Args...>& tuple) {
  std::tie(x, y, z, w) = tuple;
}

template <class T>
inline void Vector4<T>::set(std::initializer_list<T> list) {
  reset();
  auto itr = std::begin(list);
  if (itr == std::end(list)) return; x = *itr;
  if (++itr == std::end(list)) return; y = *itr;
  if (++itr == std::end(list)) return; z = *itr;
  if (++itr == std::end(list)) return; w = *itr;
}

template <class T>
inline void Vector4<T>::reset() {
  *this = Vector4<T>();
}

#pragma mark Element access

template <class T>
inline T& Vector4<T>::at(int index) {
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
inline const T& Vector4<T>::at(int index) const {
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
inline T& Vector4<T>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <class T>
inline const T& Vector4<T>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Vector4<T>::operator==(const Vector4<U>& other) const {
  return x == other.x && y == other.y && z == other.z && w == other.w;
}

template <class T>
template <class U>
inline bool Vector4<T>::operator!=(const Vector4<U>& other) const {
  return !operator==(other);
}

template <class T>
template <class U>
inline bool Vector4<T>::operator<(const Vector4<U>& other) const {
  return x < other.x || (x == other.x &&
        (y < other.y || (y == other.y &&
        (z < other.y || (z == other.y && w < other.w)))));
}

template <class T>
template <class U>
inline bool Vector4<T>::operator>(const Vector4<U>& other) const {
  return x > other.x || (x == other.x &&
        (y > other.y || (y == other.y &&
        (z > other.y || (z == other.y && w > other.w)))));
}

template <class T>
template <class U>
inline bool Vector4<T>::operator<=(const Vector4<U>& other) const {
  return operator<(other) || operator==(other);
}

template <class T>
template <class U>
inline bool Vector4<T>::operator>=(const Vector4<U>& other) const {
  return operator>(other) || operator==(other);
}

#pragma mark Arithmetic

template <class T>
inline Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  w += other.w;
  return *this;
}

template <class T>
inline Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  w -= other.w;
  return *this;
}

template <class T>
inline Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& other) {
  x *= other.x;
  y *= other.y;
  z *= other.z;
  w *= other.w;
  return *this;
}

template <class T>
inline Vector4<T>& Vector4<T>::operator/=(const Vector4<T>& other) {
  assert(other.x && other.y && other.z && other.w);
  x /= other.x;
  y /= other.y;
  z /= other.z;
  w /= other.w;
  return *this;
}

template <class T>
template <class U>
inline const Vector4<Promote<T, U>> Vector4<T>::operator+(
    const Vector4<U>& other) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) + other.x,
                    static_cast<V>(y) + other.y,
                    static_cast<V>(z) + other.z,
                    static_cast<V>(w) + other.w);
}

template <class T>
template <class U>
inline const Vector4<Promote<T, U>> Vector4<T>::operator-(
    const Vector4<U>& other) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) - other.x,
                    static_cast<V>(y) - other.y,
                    static_cast<V>(z) - other.z,
                    static_cast<V>(w) - other.w);
}

template <class T>
template <class U>
inline const Vector4<Promote<T, U>> Vector4<T>::operator*(
    const Vector4<U>& other) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) * other.x,
                    static_cast<V>(y) * other.y,
                    static_cast<V>(z) * other.z,
                    static_cast<V>(w) * other.w);
}

template <class T>
template <class U>
inline const Vector4<Promote<T, U>> Vector4<T>::operator/(
    const Vector4<U>& other) const {
  using V = Promote<T, U>;
  assert(other.x && other.y && other.z && other.w);
  return Vector4<V>(static_cast<V>(x) / other.x,
                    static_cast<V>(y) / other.y,
                    static_cast<V>(z) / other.z,
                    static_cast<V>(w) / other.w);
}

template <class T>
inline const Vector4<Promote<T>> Vector4<T>::operator-() const {
  using V = Promote<T>;
  return Vector4<V>(-static_cast<V>(x),
                    -static_cast<V>(y),
                    -static_cast<V>(z),
                    -static_cast<V>(w));
}

#pragma mark Scalar arithmetic

template <class T>
inline Vector4<T>& Vector4<T>::operator+=(T scalar) {
  x += scalar;
  y += scalar;
  z += scalar;
  w += scalar;
  return *this;
}

template <class T>
inline Vector4<T>& Vector4<T>::operator-=(T scalar) {
  x -= scalar;
  y -= scalar;
  z -= scalar;
  w -= scalar;
  return *this;
}

template <class T>
inline Vector4<T>& Vector4<T>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  w *= scalar;
  return *this;
}

template <class T>
inline Vector4<T>& Vector4<T>::operator/=(T scalar) {
  assert(scalar);
  x /= scalar;
  y /= scalar;
  z /= scalar;
  w /= scalar;
  return *this;
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Vector4<Promote<T, U>> Vector4<T>::operator+(U scalar) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) + scalar,
                    static_cast<V>(y) + scalar,
                    static_cast<V>(z) + scalar,
                    static_cast<V>(w) + scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Vector4<Promote<T, U>> Vector4<T>::operator-(U scalar) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) - scalar,
                    static_cast<V>(y) - scalar,
                    static_cast<V>(z) - scalar,
                    static_cast<V>(w) - scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Vector4<Promote<T, U>> Vector4<T>::operator*(U scalar) const {
  using V = Promote<T, U>;
  return Vector4<V>(static_cast<V>(x) * scalar,
                    static_cast<V>(y) * scalar,
                    static_cast<V>(z) * scalar,
                    static_cast<V>(w) * scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Vector4<Promote<T, U>> Vector4<T>::operator/(U scalar) const {
  using V = Promote<T, U>;
  assert(scalar);
  return Vector4<V>(static_cast<V>(x) / scalar,
                    static_cast<V>(y) / scalar,
                    static_cast<V>(z) / scalar,
                    static_cast<V>(w) / scalar);
}

template <class T, class U, EnableIfScalar<U> * = nullptr>
inline const Vector4<Promote<T, U>> operator*(
    U scalar, const Vector4<T>& vector) {
  return vector * scalar;
}

#pragma mark Attributes

template <class T>
inline Promote<T> Vector4<T>::headingXY() const {
  return std::atan2(y, x);
}

template <class T>
inline Promote<T> Vector4<T>::headingYZ() const {
  return std::atan2(z, y);
}

template <class T>
inline Promote<T> Vector4<T>::headingZX() const {
  return std::atan2(x, z);
}

template <class T>
template <class U>
inline Promote<T> Vector4<T>::angle(const Vector4<U>& other) const {
  return std::acos(normalized().dot(other.normalized()));
}

#pragma mark Magnitude

template <class T>
inline Promote<T> Vector4<T>::magnitude() const {
  return std::sqrt(magnitudeSquared());
}

template <class T>
inline Promote<T> Vector4<T>::magnitudeSquared() const {
  return static_cast<Promote<T>>(x) * x + y * y + z * z + w * w;
}

template <class T>
template <class U>
inline Vector4<T>& Vector4<T>::limit(U limit) {
  if (magnitudeSquared() > static_cast<Promote<T>>(limit) * limit) {
    normalize();
    *this *= limit;
  }
  return *this;
}

template <class T>
template <class U>
inline Vector4<Promote<T>> Vector4<T>::limited(U limit) const {
  return Vector4<Promote<T>>(*this).limit(limit);
}

#pragma mark Normalization

template <class T>
inline Vector4<T>& Vector4<T>::normalize() {
  const auto denominator = magnitude();
  if (denominator) {
    *this /= denominator;
  }
  return *this;
}

template <class T>
inline Vector4<Promote<T>> Vector4<T>::normalized() const {
  return Vector4<Promote<T>>(*this).normalize();
}

#pragma mark Inversion

template <class T>
inline Vector4<T>& Vector4<T>::invert() {
  x *= -1;
  y *= -1;
  z *= -1;
  w *= -1;
  return *this;
}

template <class T>
inline Vector4<Promote<T>> Vector4<T>::inverted() const {
  return Vector4<Promote<T>>(*this).invert();
}

#pragma mark Distance

template <class T>
template <class U>
inline Promote<T> Vector4<T>::distance(const Vector4<U>& other) const {
  return (*this - other).magnitude();
}

template <class T>
template <class U>
inline Promote<T> Vector4<T>::distanceSquared(const Vector4<U>& other) const {
  return (*this - other).magnitudeSquared();
}

#pragma mark Product

template <class T>
template <class U>
inline Promote<T, U> Vector4<T>::dot(const Vector4<U>& other) const {
  using V = Promote<T, U>;
  return static_cast<V>(x) * other.x + y * other.y + z * other.z + w * other.w;
}

template <class T>
template <class U>
inline Vector4<Promote<T, U>> Vector4<T>::cross(const Vector4<U>& other) const {
  return Vector3<T>(*this).cross(Vector3<T>(other));
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Vector4<T>& other) {
  return os << "( " << other.x << ", " << other.y << ", " << other.z
            << ", " << other.w << " )";
}

}  // namespace math

using math::Vector;
using math::Vector4i;
using math::Vector4f;
using math::Vector4d;
using math::Vec4;
using math::Vec4i;
using math::Vec4f;
using math::Vec4d;

}  // namespace takram

#endif  // TAKRAM_MATH_VECTOR4_H_
