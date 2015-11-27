//
//  takram/math/size3.h
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
#ifndef TAKRAM_MATH_SIZE3_H_
#define TAKRAM_MATH_SIZE3_H_

#include <cmath>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <tuple>

#if TAKRAM_HAS_OPENFRAMEWORKS
#include "ofVec2f.h"
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
#include "cinder/Vec.h"
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
class Size<T, 3> final {
 public:
  using Type = T;
  using Iterator = typename Vec3<T>::Iterator;
  using ConstIterator = typename Vec3<T>::ConstIterator;
  using ReverseIterator = typename Vec3<T>::ReverseIterator;
  using ConstReverseIterator = typename Vec3<T>::ConstReverseIterator;
  static constexpr const auto dimensions = Vec3<T>::dimensions;

 public:
  Size();
  explicit Size(T value);
  Size(T width, T height, T depth = T());
  explicit Size(const T *values, int size = 3);
  template <class... Args>
  Size(const std::tuple<Args...>& tuple);
  Size(std::initializer_list<T> list);

  // Implicit conversion
  template <class U>
  Size(const Size3<U>& other);

  // Explicit conversion
  template <class U>
  explicit Size(const Size2<U>& other);
  explicit Size(const Vec2<T>& other);
  explicit Size(const Vec3<T>& other);
  explicit Size(const Vec4<T>& other);

#if TAKRAM_HAS_OPENFRAMEWORKS
  explicit Size(const ofVec3f& other);
  explicit operator ofVec3f() const;
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
  template <class U>
  explicit Size(const ci::Vec3<U>& other);
  explicit operator ci::Vec3<T>() const;
#endif  // TAKRAM_HAS_CINDER

  // Copy semantics
  Size(const Size&) = default;
  Size& operator=(const Size&) = default;

  // Factory
  static Size min();
  static Size max();
  static Size random();
  static Size random(T max);
  static Size random(T min, T max);
  template <class Random>
  static Size random(Random *random);
  template <class Random>
  static Size random(T max, Random *random);
  template <class Random>
  static Size random(T min, T max, Random *random);

  // Mutators
  void set(T value);
  void set(T width, T height, T depth = T());
  void set(const T *values, int size = 3);
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
  bool operator==(const Size3<U>& other) const;
  template <class U>
  bool operator!=(const Size3<U>& other) const;
  template <class U>
  bool operator<(const Size3<U>& other) const;
  template <class U>
  bool operator>(const Size3<U>& other) const;
  template <class U>
  bool operator<=(const Size3<U>& other) const;
  template <class U>
  bool operator>=(const Size3<U>& other) const;
  template <class V, class U = T>
  bool equals(const Size3<U>& other, V tolerance) const;

  // Arithmetic
  Size& operator+=(const Size& other);
  Size& operator-=(const Size& other);
  Size& operator*=(const Size& other);
  Size& operator/=(const Size& other);
  Size3<Promote<T>> operator-() const;
  template <class U>
  Size3<Promote<T, U>> operator+(const Size3<U>& other) const;
  template <class U>
  Size3<Promote<T, U>> operator-(const Size3<U>& other) const;
  template <class U>
  Size3<Promote<T, U>> operator*(const Size3<U>& other) const;
  template <class U>
  Size3<Promote<T, U>> operator/(const Size3<U>& other) const;

  // Scalar arithmetic
  Size& operator+=(T scalar);
  Size& operator-=(T scalar);
  Size& operator*=(T scalar);
  Size& operator/=(T scalar);
  template <class U, EnableIfScalar<U> * = nullptr>
  Size3<Promote<T, U>> operator+(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Size3<Promote<T, U>> operator-(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Size3<Promote<T, U>> operator*(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  Size3<Promote<T, U>> operator/(U scalar) const;

  // Vector arithmetic
  Size& operator+=(const Vec3<T>& vector);
  Size& operator-=(const Vec3<T>& vector);
  Size& operator*=(const Vec3<T>& vector);
  Size& operator/=(const Vec3<T>& vector);
  template <class U>
  Size3<Promote<T, U>> operator+(const Vec3<U>& vector) const;
  template <class U>
  Size3<Promote<T, U>> operator-(const Vec3<U>& vector) const;
  template <class U>
  Size3<Promote<T, U>> operator*(const Vec3<U>& vector) const;
  template <class U>
  Size3<Promote<T, U>> operator/(const Vec3<U>& vector) const;

  // Attributes
  bool empty() const { return !width && !height; }
  Promote<T> aspectXY() const;
  Promote<T> aspectYZ() const;
  Promote<T> aspectZX() const;
  Promote<T> volume() const;
  Promote<T> diagonal() const;

  // Conversion
  template <class U>
  explicit operator Vec3<U>&() { return vector; }
  template <class U>
  explicit operator const Vec3<U>&() const { return vector; }

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
    Vec3<T> vector;
    struct { T width; T height; T depth; };
    struct { T w; T h; T d; };
  };
};

// Scalar arithmetic
template <class T, class U, EnableIfScalar<T> * = nullptr>
Size3<Promote<T, U>> operator+(T lhs, const Size3<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Size3<Promote<T, U>> operator-(T lhs, const Size3<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Size3<Promote<T, U>> operator*(T lhs, const Size3<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Size3<Promote<T, U>> operator/(T lhs, const Size3<U>& rhs);

// Vector arithmetic
template <class T, class U>
Vec3<Promote<T, U>> operator+(const Vec3<T>& lhs, const Size3<U>& rhs);
template <class T, class U>
Vec3<Promote<T, U>> operator-(const Vec3<T>& lhs, const Size3<U>& rhs);
template <class T, class U>
Vec3<Promote<T, U>> operator*(const Vec3<T>& lhs, const Size3<U>& rhs);
template <class T, class U>
Vec3<Promote<T, U>> operator/(const Vec3<T>& lhs, const Size3<U>& rhs);

using Size3i = Size3<int>;
using Size3f = Size3<float>;
using Size3d = Size3<double>;

#pragma mark -

template <class T>
inline Size<T, 3>::Size() : vector() {}

template <class T>
inline Size<T, 3>::Size(T value) : vector(value) {}

template <class T>
inline Size<T, 3>::Size(T width, T height, T depth)
    : vector(width, height, depth) {}

template <class T>
inline Size<T, 3>::Size(const T *values, int size) : vector(values, size) {}

template <class T>
template <class... Args>
inline Size<T, 3>::Size(const std::tuple<Args...>& tuple) : vector(tuple) {}

template <class T>
inline Size<T, 3>::Size(std::initializer_list<T> list) : vector(list) {}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Size<T, 3>::Size(const Size3<U>& other) : vector(other.vector) {}

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Size<T, 3>::Size(const Size2<U>& other) : vector(other.vector) {}

template <class T>
inline Size<T, 3>::Size(const Vec2<T>& other) : vector(other) {}

template <class T>
inline Size<T, 3>::Size(const Vec3<T>& other) : vector(other) {}

template <class T>
inline Size<T, 3>::Size(const Vec4<T>& other) : vector(other) {}

#if TAKRAM_HAS_OPENFRAMEWORKS

template <class T>
inline Size<T, 3>::Size(const ofVec3f& other) : vector(other) {}

template <class T>
inline Size<T, 3>::operator ofVec3f() const {
  return ofVec3f(vector);
}

#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER

template <class T>
template <class U>
inline Size<T, 3>::Size(const ci::Vec3<U>& other) : vector(other) {}

template <class T>
inline Size<T, 3>::operator ci::Vec3<T>() const {
  return ci::Vec3<T>(width, height, depth);
}

#endif  // TAKRAM_HAS_CINDER

#pragma mark Factory

template <class T>
inline Size3<T> Size<T, 3>::min() {
  return Size(Vec3<T>::min());
}

template <class T>
inline Size3<T> Size<T, 3>::max() {
  return Size(Vec3<T>::max());
}

template <class T>
inline Size3<T> Size<T, 3>::random() {
  return random(&Random<>::shared());
}

template <class T>
inline Size3<T> Size<T, 3>::random(T max) {
  return random(max, &Random<>::shared());
}

template <class T>
inline Size3<T> Size<T, 3>::random(T min, T max) {
  return random(min, max, &Random<>::shared());
}

template <class T>
template <class Random>
inline Size3<T> Size<T, 3>::random(Random *random) {
  return Size(Vec3<T>::random(random));
}

template <class T>
template <class Random>
inline Size3<T> Size<T, 3>::random(T max, Random *random) {
  return Size(Vec3<T>::random(max, random));
}

template <class T>
template <class Random>
inline Size3<T> Size<T, 3>::random(T min, T max, Random *random) {
  return Size(Vec3<T>::random(min, max, random));
}

#pragma mark Mutators

template <class T>
inline void Size<T, 3>::set(T value) {
  vector.set(value);
}

template <class T>
inline void Size<T, 3>::set(T width, T height, T depth) {
  vector.set(width, height, depth);
}

template <class T>
inline void Size<T, 3>::set(const T *values, int size) {
  vector.set(values, size);
}

template <class T>
template <class... Args>
inline void Size<T, 3>::set(const std::tuple<Args...>& tuple) {
  vector.set(tuple);
}

template <class T>
inline void Size<T, 3>::set(std::initializer_list<T> list) {
  vector.set(list);
}

template <class T>
inline void Size<T, 3>::reset() {
  vector.reset();
}

#pragma mark Element access

template <class T>
inline T& Size<T, 3>::at(int index) {
  return vector.at(index);
}

template <class T>
inline const T& Size<T, 3>::at(int index) const {
  return vector.at(index);
}

template <class T>
inline T& Size<T, 3>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <class T>
inline const T& Size<T, 3>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Size<T, 3>::operator==(const Size3<U>& other) const {
  return vector == other.vector;
}

template <class T>
template <class U>
inline bool Size<T, 3>::operator!=(const Size3<U>& other) const {
  return vector != other.vector;
}

template <class T>
template <class U>
inline bool Size<T, 3>::operator<(const Size3<U>& other) const {
  return vector < other.vector;
}

template <class T>
template <class U>
inline bool Size<T, 3>::operator>(const Size3<U>& other) const {
  return vector > other.vector;
}

template <class T>
template <class U>
inline bool Size<T, 3>::operator<=(const Size3<U>& other) const {
  return vector <= other.vector;
}

template <class T>
template <class U>
inline bool Size<T, 3>::operator>=(const Size3<U>& other) const {
  return vector >= other.vector;
}

template <class T>
template <class V, class U>
inline bool Size<T, 3>::equals(const Size3<U>& other, V tolerance) const {
  return vector.equals(other.vector);
}

#pragma mark Arithmetic

template <class T>
inline Size3<T>& Size<T, 3>::operator+=(const Size& other) {
  vector += other.vector;
  return *this;
}

template <class T>
inline Size3<T>& Size<T, 3>::operator-=(const Size& other) {
  vector -= other.vector;
  return *this;
}

template <class T>
inline Size3<T>& Size<T, 3>::operator*=(const Size& other) {
  vector *= other.vector;
  return *this;
}

template <class T>
inline Size3<T>& Size<T, 3>::operator/=(const Size& other) {
  vector /= other.vector;
  return *this;
}

template <class T>
inline Size3<Promote<T>> Size<T, 3>::operator-() const {
  return Size3<Promote<T>>(-vector);
}

template <class T>
template <class U>
inline Size3<Promote<T, U>> Size<T, 3>::operator+(const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector + other.vector);
}

template <class T>
template <class U>
inline Size3<Promote<T, U>> Size<T, 3>::operator-(const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector - other.vector);
}

template <class T>
template <class U>
inline Size3<Promote<T, U>> Size<T, 3>::operator*(const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector * other.vector);
}

template <class T>
template <class U>
inline Size3<Promote<T, U>> Size<T, 3>::operator/(const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector / other.vector);
}

#pragma mark Scalar arithmetic

template <class T>
inline Size3<T>& Size<T, 3>::operator+=(T scalar) {
  vector += scalar;
  return *this;
}

template <class T>
inline Size3<T>& Size<T, 3>::operator-=(T scalar) {
  vector -= scalar;
  return *this;
}

template <class T>
inline Size3<T>& Size<T, 3>::operator*=(T scalar) {
  vector *= scalar;
  return *this;
}

template <class T>
inline Size3<T>& Size<T, 3>::operator/=(T scalar) {
  vector /= scalar;
  return *this;
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Size3<Promote<T, U>> Size<T, 3>::operator+(U scalar) const {
  return Size3<Promote<T, U>>(vector + scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Size3<Promote<T, U>> Size<T, 3>::operator-(U scalar) const {
  return Size3<Promote<T, U>>(vector - scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Size3<Promote<T, U>> Size<T, 3>::operator*(U scalar) const {
  return Size3<Promote<T, U>>(vector * scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline Size3<Promote<T, U>> Size<T, 3>::operator/(U scalar) const {
  return Size3<Promote<T, U>>(vector / scalar);
}

template <class T, class U, EnableIfScalar<T> *>
inline Size3<Promote<T, U>> operator+(T lhs, const Size3<U>& rhs) {
  return Size3<Promote<T, U>>(lhs + rhs.vector);
}

template <class T, class U, EnableIfScalar<T> *>
inline Size3<Promote<T, U>> operator-(T lhs, const Size3<U>& rhs) {
  return Size3<Promote<T, U>>(lhs - rhs.vector);
}

template <class T, class U, EnableIfScalar<T> *>
inline Size3<Promote<T, U>> operator*(T lhs, const Size3<U>& rhs) {
  return Size3<Promote<T, U>>(lhs * rhs.vector);
}

template <class T, class U, EnableIfScalar<T> *>
inline Size3<Promote<T, U>> operator/(T lhs, const Size3<U>& rhs) {
  return Size3<Promote<T, U>>(lhs / rhs.vector);
}

#pragma mark Vector arithmetic

template <class T>
inline Size3<T>& Size<T, 3>::operator+=(const Vec3<T>& other) {
  vector += other;
  return *this;
}

template <class T>
inline Size3<T>& Size<T, 3>::operator-=(const Vec3<T>& other) {
  vector -= other;
  return *this;
}

template <class T>
inline Size3<T>& Size<T, 3>::operator*=(const Vec3<T>& other) {
  vector *= other;
  return *this;
}

template <class T>
inline Size3<T>& Size<T, 3>::operator/=(const Vec3<T>& other) {
  vector /= other;
  return *this;
}

template <class T>
template <class U>
inline Size3<Promote<T, U>> Size<T, 3>::operator+(const Vec3<U>& other) const {
  return Size3<Promote<T, U>>(vector + other);
}

template <class T>
template <class U>
inline Size3<Promote<T, U>> Size<T, 3>::operator-(const Vec3<U>& other) const {
  return Size3<Promote<T, U>>(vector - other);
}

template <class T>
template <class U>
inline Size3<Promote<T, U>> Size<T, 3>::operator*(const Vec3<U>& other) const {
  return Size3<Promote<T, U>>(vector * other);
}

template <class T>
template <class U>
inline Size3<Promote<T, U>> Size<T, 3>::operator/(const Vec3<U>& other) const {
  return Size3<Promote<T, U>>(vector / other);
}

template <class T, class U>
inline Vec3<Promote<T, U>> operator+(const Vec3<T>& lhs, const Size3<U>& rhs) {
  return lhs + rhs.vector;
}

template <class T, class U>
inline Vec3<Promote<T, U>> operator-(const Vec3<T>& lhs, const Size3<U>& rhs) {
  return lhs - rhs.vector;
}

template <class T, class U>
inline Vec3<Promote<T, U>> operator*(const Vec3<T>& lhs, const Size3<U>& rhs) {
  return lhs * rhs.vector;
}

template <class T, class U>
inline Vec3<Promote<T, U>> operator/(const Vec3<T>& lhs, const Size3<U>& rhs) {
  return lhs / rhs.vector;
}

#pragma mark Attributes

template <class T>
inline Promote<T> Size<T, 3>::aspectXY() const {
  return static_cast<Promote<T>>(width) / height;
}

template <class T>
inline Promote<T> Size<T, 3>::aspectYZ() const {
  return static_cast<Promote<T>>(height) / depth;
}

template <class T>
inline Promote<T> Size<T, 3>::aspectZX() const {
  return static_cast<Promote<T>>(depth) / width;
}

template <class T>
inline Promote<T> Size<T, 3>::volume() const {
  return std::abs(static_cast<Promote<T>>(width) * height * depth);
}

template <class T>
inline Promote<T> Size<T, 3>::diagonal() const {
  return vector.magnitude();
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Size3<T>& size) {
  return os << size.vector;
}

}  // namespace math

using math::Size;
using math::Size3;
using math::Size3i;
using math::Size3f;
using math::Size3d;

}  // namespace takram

template <class T>
struct std::hash<takram::math::Size3<T>> {
  std::size_t operator()(const takram::math::Size3<T>& value) const {
    std::hash<T> hash;
    return (hash(value.w) << 0) ^ (hash(value.h) << 1) ^ (hash(value.d) << 2);
  }
};

#endif  // TAKRAM_MATH_SIZE3_H_
