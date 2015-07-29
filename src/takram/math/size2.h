//
//  takram/math/size2.h
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
#ifndef TAKRAM_MATH_SIZE2_H_
#define TAKRAM_MATH_SIZE2_H_

#include <cmath>
#include <initializer_list>
#include <iterator>
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
#include "takram/math/vector.h"

namespace takram {
namespace math {

template <class T, int D>
class Size;

template <class T>
using Size2 = Size<T, 2>;
template <class T>
using Size3 = Size<T, 3>;

template <class T>
class Size<T, 2> final {
 public:
  using Type = T;
  using Iterator = typename Vector2<T>::Iterator;
  using ConstIterator = typename Vector2<T>::ConstIterator;
  using ReverseIterator = typename Vector2<T>::ReverseIterator;
  using ConstReverseIterator = typename Vector2<T>::ConstReverseIterator;
  static constexpr const auto dimensions = Vector2<T>::dimensions;

 public:
  Size();
  explicit Size(T value);
  Size(T width, T height);
  explicit Size(const T *values, int size = dimensions);
  template <class... Args>
  Size(const std::tuple<Args...>& tuple);
  Size(std::initializer_list<T> list);

  // Implicit conversion
  template <class U>
  Size(const Size2<U>& other);

#if TAKRAM_HAS_OPENCV
  template <class U>
  Size(const cv::Size_<U>& other);
  operator cv::Size_<T>() const;
#endif  // TAKRAM_HAS_OPENCV

  // Explicit conversion
  template <class U>
  explicit Size(const Size3<U>& other);
  explicit Size(const Vector2<T>& other);
  explicit Size(const Vector3<T>& other);
  explicit Size(const Vector4<T>& other);

#if TAKRAM_HAS_OPENFRAMEWORKS
  explicit Size(const ofVec2f& other);
  explicit operator ofVec2f() const;
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
  template <class U>
  explicit Size(const ci::Vec2<U>& other);
  explicit operator ci::Vec2<T>() const;
#endif  // TAKRAM_HAS_CINDER

  // Copy semantics
  Size(const Size2<T>& other);
  Size2<T>& operator=(const Size2<T>& other);

  // Factory
  static Size2<T> min();
  static Size2<T> max();
  static Size2<T> random();
  static Size2<T> random(T max);
  static Size2<T> random(T min, T max);
  template <class Random>
  static Size2<T> random(Random *random);
  template <class Random>
  static Size2<T> random(T max, Random *random);
  template <class Random>
  static Size2<T> random(T min, T max, Random *random);

  // Mutators
  void set(T value);
  void set(T width, T height);
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
  T& front() { return vector.front(); }
  const T& front() const { return vector.front(); }
  T& back() { return vector.back(); }
  const T& back() const { return vector.back(); }

  // Comparison
  template <class U>
  bool operator==(const Size2<U>& other) const;
  template <class U>
  bool operator!=(const Size2<U>& other) const;
  template <class U>
  bool operator<(const Size2<U>& other) const;
  template <class U>
  bool operator>(const Size2<U>& other) const;
  template <class U>
  bool operator<=(const Size2<U>& other) const;
  template <class U>
  bool operator>=(const Size2<U>& other) const;

  // Arithmetic
  Size2<T>& operator+=(const Size2<T>& other);
  Size2<T>& operator-=(const Size2<T>& other);
  Size2<T>& operator*=(const Size2<T>& other);
  Size2<T>& operator/=(const Size2<T>& other);
  template <class U>
  Size2<Promote<T, U>> operator+(const Size2<U>& other) const;
  template <class U>
  Size2<Promote<T, U>> operator-(const Size2<U>& other) const;
  template <class U>
  Size2<Promote<T, U>> operator*(const Size2<U>& other) const;
  template <class U>
  Size2<Promote<T, U>> operator/(const Size2<U>& other) const;
  Size2<Promote<T>> operator-() const;

  // Scalar arithmetic
  Size2<T>& operator+=(T scalar);
  Size2<T>& operator-=(T scalar);
  Size2<T>& operator*=(T scalar);
  Size2<T>& operator/=(T scalar);
  template <class U, EnableIfScalar<U> * = nullptr>
  Size2<Promote<T, U>> operator+(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Size2<Promote<T, U>> operator-(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Size2<Promote<T, U>> operator*(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Size2<Promote<T, U>> operator/(U scalar) const;

  // Vector arithmetic
  Size2<T>& operator+=(const Vector2<T>& other);
  Size2<T>& operator-=(const Vector2<T>& other);
  Size2<T>& operator*=(const Vector2<T>& other);
  Size2<T>& operator/=(const Vector2<T>& other);
  template <class U>
  Size2<Promote<T, U>> operator+(const Vector2<U>& other) const;
  template <class U>
  Size2<Promote<T, U>> operator-(const Vector2<U>& other) const;
  template <class U>
  Size2<Promote<T, U>> operator*(const Vector2<U>& other) const;
  template <class U>
  Size2<Promote<T, U>> operator/(const Vector2<U>& other) const;

  // Attributes
  bool empty() const { return !width && !height; }
  Promote<T> aspect() const;
  Promote<T> area() const;
  Promote<T> diagonal() const;

  // Conversion
  template <class U>
  explicit operator Vector2<U>() { return vector; }
  template <class U>
  explicit operator const Vector2<U>() const { return vector; }

  // Iterator
  Iterator begin() { return std::begin(vector); }
  ConstIterator begin() const { return std::begin(vector); }
  Iterator end() { return std::end(vector); }
  ConstIterator end() const { return std::end(vector); }
  ReverseIterator rbegin() { return std::rbegin(vector); }
  ConstReverseIterator rbegin() const { return std::rbegin(vector); }
  ReverseIterator rend() { return std::rend(vector); }
  ConstReverseIterator rend() const { return std::rend(vector); }

  // Pointer
  T * ptr() { return vector.ptr(); }
  const T * ptr() const { return vector.ptr(); }

 public:
  union {
    Vector2<T> vector;
    struct { T width; T height; };
    struct { T w; T h; };
  };
};

using Size2i = Size2<int>;
using Size2f = Size2<float>;
using Size2d = Size2<double>;

#pragma mark -

template <class T>
inline Size2<T>::Size() : vector() {}

template <class T>
inline Size2<T>::Size(T value) : vector(value) {}

template <class T>
inline Size2<T>::Size(T width, T height) : vector(width, height) {}

template <class T>
inline Size2<T>::Size(const T *values, int size) : vector(values, size) {}

template <class T>
template <class... Args>
inline Size2<T>::Size(const std::tuple<Args...>& tuple) : vector(tuple) {}

template <class T>
inline Size2<T>::Size(std::initializer_list<T> list) : vector(list) {}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Size2<T>::Size(const Size2<U>& other) : vector(other.vector) {}

#if TAKRAM_HAS_OPENCV

template <class T>
template <class U>
inline Size2<T>::Size(const cv::Size_<U>& other)
    : vector(other.width, other.height) {}

template <class T>
inline Size2<T>::operator cv::Size_<T>() const {
  return cv::Size_<T>(width, height);
}

#endif  // TAKRAM_HAS_OPENCV

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Size2<T>::Size(const Size3<U>& other) : vector(other.vector) {}

template <class T>
inline Size2<T>::Size(const Vector2<T>& other) : vector(other) {}

template <class T>
inline Size2<T>::Size(const Vector3<T>& other) : vector(other) {}

template <class T>
inline Size2<T>::Size(const Vector4<T>& other) : vector(other) {}

#if TAKRAM_HAS_OPENFRAMEWORKS

template <class T>
inline Size2<T>::Size(const ofVec2f& other) : vector(other) {}

template <class T>
inline Size2<T>::operator ofVec2f() const {
  return ofVec2f(vector);
}

#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER

template <class T>
template <class U>
inline Size2<T>::Size(const ci::Vec2<U>& other) : vector(other) {}

template <class T>
inline Size2<T>::operator ci::Vec2<T>() const {
  return ci::Vec2<T>(vector);
}

#endif  // TAKRAM_HAS_CINDER

#pragma mark Copy semantics

template <class T>
inline Size2<T>::Size(const Size2<T>& other) : vector(other.vector) {}

template <class T>
inline Size2<T>& Size2<T>::operator=(const Size2<T>& other) {
  if (&other != this) {
    vector = other.vector;
  }
  return *this;
}

#pragma mark Factory

template <class T>
inline Size2<T> Size2<T>::min() {
  return Size2<T>(Vector2<T>::min());
}

template <class T>
inline Size2<T> Size2<T>::max() {
  return Size2<T>(Vector2<T>::max());
}

template <class T>
inline Size2<T> Size2<T>::random() {
  return random(&Random<>::shared());
}

template <class T>
inline Size2<T> Size2<T>::random(T max) {
  return random(max, &Random<>::shared());
}

template <class T>
inline Size2<T> Size2<T>::random(T min, T max) {
  return random(min, max, &Random<>::shared());
}

template <class T>
template <class Random>
inline Size2<T> Size2<T>::random(Random *random) {
  return Size2<T>(Vector2<T>::random(random));
}

template <class T>
template <class Random>
inline Size2<T> Size2<T>::random(T max, Random *random) {
  return Size2<T>(Vector2<T>::random(max, random));
}

template <class T>
template <class Random>
inline Size2<T> Size2<T>::random(T min, T max, Random *random) {
  return Size2<T>(Vector2<T>::random(min, max, random));
}

#pragma mark Mutators

template <class T>
inline void Size2<T>::set(T value) {
  vector.set(value);
}

template <class T>
inline void Size2<T>::set(T width, T height) {
  vector.set(width, height);
}

template <class T>
inline void Size2<T>::set(const T *values, int size) {
  vector.set(values, size);
}

template <class T>
template <class... Args>
inline void Size2<T>::set(const std::tuple<Args...>& tuple) {
  vector.set(tuple);
}

template <class T>
inline void Size2<T>::set(std::initializer_list<T> list) {
  vector.set(list);
}

template <class T>
inline void Size2<T>::reset() {
  vector.reset();
}

#pragma mark Element access

template <class T>
inline T& Size2<T>::at(int index) {
  return vector.at(index);
}

template <class T>
inline const T& Size2<T>::at(int index) const {
  return vector.at(index);
}

template <class T>
inline T& Size2<T>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <class T>
inline const T& Size2<T>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Size2<T>::operator==(const Size2<U>& other) const {
  return vector == other.vector;
}

template <class T>
template <class U>
inline bool Size2<T>::operator!=(const Size2<U>& other) const {
  return vector != other.vector;
}

template <class T>
template <class U>
inline bool Size2<T>::operator<(const Size2<U>& other) const {
  return vector < other.vector;
}

template <class T>
template <class U>
inline bool Size2<T>::operator>(const Size2<U>& other) const {
  return vector > other.vector;
}

template <class T>
template <class U>
inline bool Size2<T>::operator<=(const Size2<U>& other) const {
  return vector <= other.vector;
}

template <class T>
template <class U>
inline bool Size2<T>::operator>=(const Size2<U>& other) const {
  return vector >= other.vector;
}

#pragma mark Arithmetic

template <class T>
inline Size2<T>& Size2<T>::operator+=(const Size2<T>& other) {
  vector += other.vector;
  return *this;
}

template <class T>
inline Size2<T>& Size2<T>::operator-=(const Size2<T>& other) {
  vector -= other.vector;
  return *this;
}

template <class T>
inline Size2<T>& Size2<T>::operator*=(const Size2<T>& other) {
  vector *= other.vector;
  return *this;
}

template <class T>
inline Size2<T>& Size2<T>::operator/=(const Size2<T>& other) {
  vector /= other.vector;
  return *this;
}

template <class T>
template <class U>
inline Size2<Promote<T, U>> Size2<T>::operator+(const Size2<U>& other) const {
  return Size2<Promote<T, U>>(vector + other.vector);
}

template <class T>
template <class U>
inline Size2<Promote<T, U>> Size2<T>::operator-(const Size2<U>& other) const {
  return Size2<Promote<T, U>>(vector - other.vector);
}

template <class T>
template <class U>
inline Size2<Promote<T, U>> Size2<T>::operator*(const Size2<U>& other) const {
  return Size2<Promote<T, U>>(vector * other.vector);
}

template <class T>
template <class U>
inline Size2<Promote<T, U>> Size2<T>::operator/(const Size2<U>& other) const {
  return Size2<Promote<T, U>>(vector / other.vector);
}

template <class T>
inline Size2<Promote<T>> Size2<T>::operator-() const {
  return Size2<Promote<T>>(-vector);
}

#pragma mark Scalar arithmetic

template <class T>
inline Size2<T>& Size2<T>::operator+=(T scalar) {
  vector += scalar;
  return *this;
}

template <class T>
inline Size2<T>& Size2<T>::operator-=(T scalar) {
  vector -= scalar;
  return *this;
}

template <class T>
inline Size2<T>& Size2<T>::operator*=(T scalar) {
  vector *= scalar;
  return *this;
}

template <class T>
inline Size2<T>& Size2<T>::operator/=(T scalar) {
  vector /= scalar;
  return *this;
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> Size2<T>::operator+(U scalar) const {
  return Size2<Promote<T, U>>(vector + scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> Size2<T>::operator-(U scalar) const {
  return Size2<Promote<T, U>>(vector - scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> Size2<T>::operator*(U scalar) const {
  return Size2<Promote<T, U>>(vector * scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> Size2<T>::operator/(U scalar) const {
  return Size2<Promote<T, U>>(vector / scalar);
}

template <class T, class U, EnableIfScalar<U> * = nullptr>
inline Size2<Promote<T, U>> operator*(U scalar, const Size2<T>& size) {
  return size * scalar;
}

#pragma mark Vector arithmetic

template <class T>
inline Size2<T>& Size2<T>::operator+=(const Vector2<T>& other) {
  vector += other;
  return *this;
}

template <class T>
inline Size2<T>& Size2<T>::operator-=(const Vector2<T>& other) {
  vector -= other;
  return *this;
}

template <class T>
inline Size2<T>& Size2<T>::operator*=(const Vector2<T>& other) {
  vector *= other;
  return *this;
}

template <class T>
inline Size2<T>& Size2<T>::operator/=(const Vector2<T>& other) {
  vector /= other;
  return *this;
}

template <class T>
template <class U>
inline Size2<Promote<T, U>> Size2<T>::operator+(const Vector2<U>& other) const {
  return Size2<Promote<T, U>>(vector + other);
}

template <class T>
template <class U>
inline Size2<Promote<T, U>> Size2<T>::operator-(const Vector2<U>& other) const {
  return Size2<Promote<T, U>>(vector - other);
}

template <class T>
template <class U>
inline Size2<Promote<T, U>> Size2<T>::operator*(const Vector2<U>& other) const {
  return Size2<Promote<T, U>>(vector * other);
}

template <class T>
template <class U>
inline Size2<Promote<T, U>> Size2<T>::operator/(const Vector2<U>& other) const {
  return Size2<Promote<T, U>>(vector / other);
}

template <class T, class U>
inline Size2<Promote<T, U>> operator*(const Vector2<U>& vector,
                                      const Size2<T>& size) {
  return size * vector;
}

#pragma mark Attributes

template <class T>
inline Promote<T> Size2<T>::aspect() const {
  return static_cast<Promote<T>>(width) / height;
}

template <class T>
inline Promote<T> Size2<T>::area() const {
  return std::abs(static_cast<Promote<T>>(width) * height);
}

template <class T>
inline Promote<T> Size2<T>::diagonal() const {
  return vector.magnitude();
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Size2<T>& other) {
  return os << other.vector;
}

}  // namespace math

using math::Size;
using math::Size2;
using math::Size2i;
using math::Size2f;
using math::Size2d;

}  // namespace takram

#endif  // TAKRAM_MATH_SIZE2_H_
