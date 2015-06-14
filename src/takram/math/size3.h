//
//  takram/math/size3.h
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
#ifndef TAKRAM_MATH_SIZE3_H_
#define TAKRAM_MATH_SIZE3_H_

#include <cmath>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <tuple>

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
  using Iterator = typename Vector3<T>::Iterator;
  using ConstIterator = typename Vector3<T>::ConstIterator;
  using ReverseIterator = typename Vector3<T>::ReverseIterator;
  using ConstReverseIterator = typename Vector3<T>::ConstReverseIterator;
  static constexpr const auto dimensions = Vector3<T>::dimensions;

 public:
  Size();
  explicit Size(T value);
  Size(T width, T height, T depth = T());
  explicit Size(const T *values, int size = dimensions);
  template <class... Args>
  Size(const std::tuple<Args...>& tuple);
  Size(std::initializer_list<T> list);

  // Implicit conversion
  template <class U>
  Size(const Size3<U>& other);

  // Explicit conversion
  template <class U>
  explicit Size(const Size2<U>& other);
  explicit Size(const Vector2<T>& other);
  explicit Size(const Vector3<T>& other);
  explicit Size(const Vector4<T>& other);

  // Copy semantics
  Size(const Size3<T>& other);
  Size3<T>& operator=(const Size3<T>& other);

  // Factory
  static Size3<T> min();
  static Size3<T> max();
  template <class Random>
  static Size3<T> random(Random *random);
  template <class Random>
  static Size3<T> random(T max, Random *random);
  template <class Random>
  static Size3<T> random(T min, T max, Random *random);

  // Mutators
  void set(T value);
  void set(T width, T height, T depth = T());
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

  // Arithmetic
  Size3<T>& operator+=(const Size3<T>& other);
  Size3<T>& operator-=(const Size3<T>& other);
  Size3<T>& operator*=(const Size3<T>& other);
  Size3<T>& operator/=(const Size3<T>& other);
  template <class U>
  const Size3<Promote<T, U>> operator+(const Size3<U>& other) const;
  template <class U>
  const Size3<Promote<T, U>> operator-(const Size3<U>& other) const;
  template <class U>
  const Size3<Promote<T, U>> operator*(const Size3<U>& other) const;
  template <class U>
  const Size3<Promote<T, U>> operator/(const Size3<U>& other) const;
  const Size3<Promote<T>> operator-() const;

  // Scalar arithmetic
  Size3<T>& operator+=(T scalar);
  Size3<T>& operator-=(T scalar);
  Size3<T>& operator*=(T scalar);
  Size3<T>& operator/=(T scalar);
  template <class U, EnableIfScalar<U> * = nullptr>
  const Size3<Promote<T, U>> operator+(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  const Size3<Promote<T, U>> operator-(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  const Size3<Promote<T, U>> operator*(U scalar) const;
  template <class U, EnableIfScalar<U> * = nullptr>
  const Size3<Promote<T, U>> operator/(U scalar) const;

  // Vector arithmetic
  Size3<T>& operator+=(const Vector3<T>& vector);
  Size3<T>& operator-=(const Vector3<T>& vector);
  Size3<T>& operator*=(const Vector3<T>& vector);
  Size3<T>& operator/=(const Vector3<T>& vector);
  template <class U>
  const Size3<Promote<T, U>> operator+(const Vector3<U>& vector) const;
  template <class U>
  const Size3<Promote<T, U>> operator-(const Vector3<U>& vector) const;
  template <class U>
  const Size3<Promote<T, U>> operator*(const Vector3<U>& vector) const;
  template <class U>
  const Size3<Promote<T, U>> operator/(const Vector3<U>& vector) const;

  // Attributes
  bool empty() const { return !width && !height; }
  Promote<T> aspectXY() const;
  Promote<T> aspectYZ() const;
  Promote<T> aspectZX() const;
  Promote<T> volume() const;
  Promote<T> diagonal() const;

  // Conversion
  template <class U>
  explicit operator Vector3<U>&() { return vector; }
  template <class U>
  explicit operator const Vector3<U>&() const { return vector; }

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
    Vector3<T> vector;
    struct { T width; T height; T depth; };
    struct { T w; T h; T d; };
  };
};

using Size3i = Size3<int>;
using Size3f = Size3<float>;
using Size3d = Size3<double>;

#pragma mark -

template <class T>
inline Size3<T>::Size() : vector() {}

template <class T>
inline Size3<T>::Size(T value) : vector(value) {}

template <class T>
inline Size3<T>::Size(T width, T height, T depth)
    : vector(width, height, depth) {}

template <class T>
inline Size3<T>::Size(const T *values, int size) : vector(values, size) {}

template <class T>
template <class... Args>
inline Size3<T>::Size(const std::tuple<Args...>& tuple) : vector(tuple) {}

template <class T>
inline Size3<T>::Size(std::initializer_list<T> list) : vector(list) {}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Size3<T>::Size(const Size3<U>& other) : vector(other.vector) {}

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Size3<T>::Size(const Size2<U>& other) : vector(other.vector) {}

template <class T>
inline Size3<T>::Size(const Vector2<T>& other) : vector(other) {}

template <class T>
inline Size3<T>::Size(const Vector3<T>& other) : vector(other) {}

template <class T>
inline Size3<T>::Size(const Vector4<T>& other) : vector(other) {}

#pragma mark Copy semantics

template <class T>
inline Size3<T>::Size(const Size3<T>& other) : vector(other.vector) {}

template <class T>
inline Size3<T>& Size3<T>::operator=(const Size3<T>& other) {
  if (&other != this) {
    vector = other.vector;
  }
  return *this;
}

#pragma mark Factory

template <class T>
inline Size3<T> Size3<T>::min() {
  return Size3<T>(Vector3<T>::min());
}

template <class T>
inline Size3<T> Size3<T>::max() {
  return Size3<T>(Vector3<T>::max());
}

template <class T>
template <class Random>
inline Size3<T> Size3<T>::random(Random *random) {
  return Size3<T>(Vector3<T>::Random(random));
}

template <class T>
template <class Random>
inline Size3<T> Size3<T>::random(T max, Random *random) {
  return Size3<T>(Vector3<T>::Random(max, random));
}

template <class T>
template <class Random>
inline Size3<T> Size3<T>::random(T min, T max, Random *random) {
  return Size3<T>(Vector3<T>::Random(min, max, random));
}

#pragma mark Mutators

template <class T>
inline void Size3<T>::set(T value) {
  vector.set(value);
}

template <class T>
inline void Size3<T>::set(T width, T height, T depth) {
  vector.set(width, height, depth);
}

template <class T>
inline void Size3<T>::set(const T *values, int size) {
  vector.set(values, size);
}

template <class T>
template <class... Args>
inline void Size3<T>::set(const std::tuple<Args...>& tuple) {
  vector.set(tuple);
}

template <class T>
inline void Size3<T>::set(std::initializer_list<T> list) {
  vector.set(list);
}

template <class T>
inline void Size3<T>::reset() {
  vector.reset();
}

#pragma mark Element access

template <class T>
inline T& Size3<T>::at(int index) {
  return vector.at(index);
}

template <class T>
inline const T& Size3<T>::at(int index) const {
  return vector.at(index);
}

template <class T>
inline T& Size3<T>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <class T>
inline const T& Size3<T>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Size3<T>::operator==(const Size3<U>& other) const {
  return vector == other.vector;
}

template <class T>
template <class U>
inline bool Size3<T>::operator!=(const Size3<U>& other) const {
  return vector != other.vector;
}

template <class T>
template <class U>
inline bool Size3<T>::operator<(const Size3<U>& other) const {
  return vector < other.vector;
}

template <class T>
template <class U>
inline bool Size3<T>::operator>(const Size3<U>& other) const {
  return vector > other.vector;
}

template <class T>
template <class U>
inline bool Size3<T>::operator<=(const Size3<U>& other) const {
  return vector <= other.vector;
}

template <class T>
template <class U>
inline bool Size3<T>::operator>=(const Size3<U>& other) const {
  return vector >= other.vector;
}

#pragma mark Arithmetic

template <class T>
inline Size3<T>& Size3<T>::operator+=(const Size3<T>& other) {
  vector += other.vector;
  return *this;
}

template <class T>
inline Size3<T>& Size3<T>::operator-=(const Size3<T>& other) {
  vector -= other.vector;
  return *this;
}

template <class T>
inline Size3<T>& Size3<T>::operator*=(const Size3<T>& other) {
  vector *= other.vector;
  return *this;
}

template <class T>
inline Size3<T>& Size3<T>::operator/=(const Size3<T>& other) {
  vector /= other.vector;
  return *this;
}

template <class T>
template <class U>
inline const Size3<Promote<T, U>> Size3<T>::operator+(
    const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector + other.vector);
}

template <class T>
template <class U>
inline const Size3<Promote<T, U>> Size3<T>::operator-(
    const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector - other.vector);
}

template <class T>
template <class U>
inline const Size3<Promote<T, U>> Size3<T>::operator*(
    const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector * other.vector);
}

template <class T>
template <class U>
inline const Size3<Promote<T, U>> Size3<T>::operator/(
    const Size3<U>& other) const {
  return Size3<Promote<T, U>>(vector / other.vector);
}

template <class T>
inline const Size3<Promote<T>> Size3<T>::operator-() const {
  return Size3<Promote<T>>(-vector);
}

#pragma mark Scalar arithmetic

template <class T>
inline Size3<T>& Size3<T>::operator+=(T scalar) {
  vector += scalar;
  return *this;
}

template <class T>
inline Size3<T>& Size3<T>::operator-=(T scalar) {
  vector -= scalar;
  return *this;
}

template <class T>
inline Size3<T>& Size3<T>::operator*=(T scalar) {
  vector *= scalar;
  return *this;
}

template <class T>
inline Size3<T>& Size3<T>::operator/=(T scalar) {
  vector /= scalar;
  return *this;
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Size3<Promote<T, U>> Size3<T>::operator+(U scalar) const {
  return Size3<Promote<T, U>>(vector + scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Size3<Promote<T, U>> Size3<T>::operator-(U scalar) const {
  return Size3<Promote<T, U>>(vector - scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Size3<Promote<T, U>> Size3<T>::operator*(U scalar) const {
  return Size3<Promote<T, U>>(vector * scalar);
}

template <class T>
template <class U, EnableIfScalar<U> *>
inline const Size3<Promote<T, U>> Size3<T>::operator/(U scalar) const {
  return Size3<Promote<T, U>>(vector / scalar);
}

template <class T, class U, EnableIfScalar<U> * = nullptr>
inline const Size3<Promote<T, U>> operator*(U scalar, const Size3<T>& size) {
  return size * scalar;
}

#pragma mark Vector arithmetic

template <class T>
inline Size3<T>& Size3<T>::operator+=(const Vector3<T>& other) {
  vector += other;
}

template <class T>
inline Size3<T>& Size3<T>::operator-=(const Vector3<T>& other) {
  vector -= other;
}

template <class T>
inline Size3<T>& Size3<T>::operator*=(const Vector3<T>& other) {
  vector *= other;
}

template <class T>
inline Size3<T>& Size3<T>::operator/=(const Vector3<T>& other) {
  vector /= other;
}

template <class T>
template <class U>
inline const Size3<Promote<T, U>> Size3<T>::operator+(
    const Vector3<U>& other) const {
  return Size3<Promote<T, U>>(vector + other);
}

template <class T>
template <class U>
inline const Size3<Promote<T, U>> Size3<T>::operator-(
    const Vector3<U>& other) const {
  return Size3<Promote<T, U>>(vector - other);
}

template <class T>
template <class U>
inline const Size3<Promote<T, U>> Size3<T>::operator*(
    const Vector3<U>& other) const {
  return Size3<Promote<T, U>>(vector * other);
}

template <class T>
template <class U>
inline const Size3<Promote<T, U>> Size3<T>::operator/(
    const Vector3<U>& other) const {
  return Size3<Promote<T, U>>(vector / other);
}

template <class T, class U>
inline const Size3<Promote<T, U>> operator*(
    const Vector3<U>& vector, const Size3<T>& size) {
  return size * vector;
}

#pragma mark Attributes

template <class T>
inline Promote<T> Size3<T>::aspectXY() const {
  return static_cast<Promote<T>>(width) / height;
}

template <class T>
inline Promote<T> Size3<T>::aspectYZ() const {
  return static_cast<Promote<T>>(height) / depth;
}

template <class T>
inline Promote<T> Size3<T>::aspectZX() const {
  return static_cast<Promote<T>>(depth) / width;
}

template <class T>
inline Promote<T> Size3<T>::volume() const {
  return std::abs(static_cast<Promote<T>>(width) * height * depth);
}

template <class T>
inline Promote<T> Size3<T>::diagonal() const {
  return vector.length();
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Size3<T>& other) {
  return os << other.vector;
}

}  // namespace math
}  // namespace takram

#endif  // TAKRAM_MATH_SIZE3_H_
