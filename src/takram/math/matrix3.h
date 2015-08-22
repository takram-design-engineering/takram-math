//
//  takram/math/matrix3.h
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
#ifndef TAKRAM_MATH_MATRIX3_H_
#define TAKRAM_MATH_MATRIX3_H_

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
class Matrix<T, 3> final {
 public:
  using Type = T;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const int dimensions = 3;

 public:
  // Constructors
  Matrix();
  Matrix(T v00, T v01, T v02, T v03,
         T v04, T v05, T v06, T v07,
         T v08, T v09, T v10, T v11,
         T v12, T v13, T v14, T v15);
  Matrix(const Vector4<T>& vx, const Vector4<T>& vy, const Vector4<T>& vz,
         const Vector4<T>& vw = Vector4<T>(0, 0, 0, 1));

  // Implicit conversion
  template <class U>
  Matrix(const Matrix3<U>& other);

  // Copy and assign
  Matrix(const Matrix3<T>& other);
  Matrix3<T>& operator=(const Matrix3<T>& other);

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
      Vector4<T> c4;
    };
    struct {
      T m00, m10, m20, m30;
      T m01, m11, m21, m31;
      T m02, m12, m22, m32;
      T m03, m13, m23, m33;
    };
    std::array<T, 16> m;
  };
};

using Matrix3i = Matrix3<int>;
using Matrix3f = Matrix3<float>;
using Matrix3d = Matrix3<double>;

#pragma mark -

template <class T>
inline Matrix3<T>::Matrix() : c1(), c2(), c3(), c4() {}

template <class T>
inline Matrix3<T>::Matrix(T v00, T v01, T v02, T v03,
                          T v04, T v05, T v06, T v07,
                          T v08, T v09, T v10, T v11,
                          T v12, T v13, T v14, T v15)
    : c1(v00, v01, v02, v03),
      c2(v04, v05, v06, v07),
      c3(v08, v09, v10, v11),
      c4(v12, v13, v14, v15) {}

template <class T>
inline Matrix3<T>::Matrix(const Vector4<T>& vx,
                          const Vector4<T>& vy,
                          const Vector4<T>& vz,
                          const Vector4<T>& vw)
    : c1(vx.x, vy.x, vz.x, vw.x),
      c2(vx.y, vy.y, vz.y, vw.y),
      c3(vx.z, vy.z, vz.z, vw.z),
      c4(vx.w, vy.w, vz.w, vw.w) {}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Matrix3<T>::Matrix(const Matrix3<U>& other) : m(other.m) {}

#pragma mark Copy and assign

template <class T>
inline Matrix3<T>::Matrix(const Matrix3<T>& other) : m(other.m) {}

template <class T>
inline Matrix3<T>& Matrix3<T>::operator=(const Matrix3<T>& other) {
  if (&other != this) {
    m = other.m;
  }
  return *this;
}

}  // namespace math
}  // namespace takram

#endif  // TAKRAM_MATH_MATRIX3_H_
