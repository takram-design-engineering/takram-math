//
//  takram/math/matrix2.h
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
#ifndef TAKRAM_MATH_MATRIX2_H_
#define TAKRAM_MATH_MATRIX2_H_

#include <array>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <tuple>
#include <utility>

#include "takram/math/axis.h"
#include "takram/math/enablers.h"
#include "takram/math/promotion.h"
#include "takram/math/vector.h"

namespace takram {
namespace math {

template <class T, int D>
class Matrix;

template <class T>
using Matrix2 = Matrix<T, 2>;
template <class T>
using Matrix3 = Matrix<T, 3>;

template <class T>
class Matrix<T, 2> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const int dimensions = 2;

 public:
  // Constructors
  Matrix();
  Matrix(T v00, T v01, T v02,
         T v03, T v04, T v05,
         T v06, T v07, T v08);
  Matrix(const Vector3<T>& vx, const Vector3<T>& vy,
         const Vector3<T>& vz = Vector3<T>(0, 0, 1));

  // Implicit conversion
  template <class U>
  Matrix(const Matrix2<U>& other);

  // Copy and assign
  Matrix(const Matrix2<T>& other);
  Matrix2<T>& operator=(const Matrix2<T>& other);

  // Iterator
  Iterator begin() { return m.begin(); }
  ConstIterator begin() const { return m.begin(); }
  Iterator end() { return m.end(); }
  ConstIterator end() const { return m.end(); }
  ReverseIterator rbegin() { return m.rbegin(); }
  ConstReverseIterator rbegin() const { return m.rbegin(); }
  ReverseIterator rend() { return m.rend(); }
  ConstReverseIterator rend() const { return m.rend(); }

  // Pointer
  T * ptr() { return m.data(); }
  const T * ptr() const { return m.data(); }

 public:
  union {
    struct {
      Vector4<T> c1;
      Vector4<T> c2;
      Vector4<T> c3;
    };
    struct {
      T m00, m10, m20;
      T m01, m11, m21;
      T m02, m12, m22;
    };
    std::array<T, 9> m;
  };
};

using Matrix2i = Matrix2<int>;
using Matrix2f = Matrix2<float>;
using Matrix2d = Matrix2<double>;

#pragma mark -

template <class T>
inline Matrix2<T>::Matrix() : c1(), c2(), c3() {}

template <class T>
inline Matrix2<T>::Matrix(T v00, T v01, T v02,
                          T v03, T v04, T v05,
                          T v06, T v07, T v08)
    : c1(v00, v01, v02),
      c2(v03, v04, v05),
      c3(v06, v07, v08) {}

template <class T>
inline Matrix2<T>::Matrix(const Vector3<T>& vx,
                          const Vector3<T>& vy,
                          const Vector3<T>& vz)
    : c1(vx.x, vy.x, vz.x),
      c2(vx.y, vy.y, vz.y),
      c3(vx.z, vy.z, vz.z) {}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Matrix2<T>::Matrix(const Matrix2<U>& other) : m(other.m) {}

#pragma mark Copy and assign

template <class T>
inline Matrix2<T>::Matrix(const Matrix2<T>& other) : m(other.m) {}

template <class T>
inline Matrix2<T>& Matrix2<T>::operator=(const Matrix2<T>& other) {
  if (&other != this) {
    m = other.m;
  }
  return *this;
}

}  // namespace math
}  // namespace takram

#endif  // TAKRAM_MATH_MATRIX2_H_
