//
//  takram/math/triangle3.h
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
#ifndef TAKRAM_MATH_TRIANGLE3_H_
#define TAKRAM_MATH_TRIANGLE3_H_

#include <cassert>
#include <initializer_list>
#include <iterator>
#include <ostream>

#include "takram/math/vector.h"

namespace takram {
namespace math {

template <class T, int D>
class Triangle;

template <class T>
using Triangle2 = Triangle<T, 2>;
template <class T>
using Triangle3 = Triangle<T, 3>;

template <class T>
class Triangle<T, 3> final {
 public:
  using Type = T;
  using Iterator = Vec3<T> *;
  using ConstIterator = const Vec3<T> *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const auto dimensions = Vec3<T>::dimensions;

 public:
  Triangle();
  Triangle(T x1, T y1, T z1, T x2, T y2, T z2, T x3, T y3, T z3);
  Triangle(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c);
  Triangle(std::initializer_list<T> list);
  Triangle(std::initializer_list<Vec3<T>> list);

  // Implicit conversion
  template <class U>
  Triangle(const Triangle3<U>& other);

  // Explicit conversion
  template <class U>
  explicit Triangle(const Triangle2<U>& other);

  // Copy semantics
  Triangle(const Triangle& other) = default;
  Triangle& operator=(const Triangle& other) = default;

  // Mutators
  void set(T x1, T y1, T z1, T x2, T y2, T z2, T x3, T y3, T z3);
  void set(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c);
  void set(std::initializer_list<T> list);
  void set(std::initializer_list<Vec3<T>> list);
  void reset();

  // Element access
  Vec3<T>& operator[](int index) { return at(index); }
  const Vec3<T>& operator[](int index) const { return at(index); }
  Vec3<T>& at(int index);
  const Vec3<T>& at(int index) const;
  Vec3<T>& front() { return a; }
  const Vec3<T>& front() const { return a; }
  Vec3<T>& back() { return c; }
  const Vec3<T>& back() const { return c; }

  // Comparison
  template <class U>
  bool operator==(const Triangle3<U>& other) const;
  template <class U>
  bool operator!=(const Triangle3<U>& other) const;

  // Iterator
  Iterator begin() { return &a; }
  ConstIterator begin() const { return &a; }
  Iterator end() { return &c + 1; }
  ConstIterator end() const { return &c + 1; }
  ReverseIterator rbegin() { return ReverseIterator(begin()); }
  ConstReverseIterator rbegin() const { return ConstReverseIterator(begin()); }
  ReverseIterator rend() { return ReverseIterator(end()); }
  ConstReverseIterator rend() const { return ConstReverseIterator(end()); }

  // Pointer
  Vec3<T> * ptr() { return &a; }
  const Vec3<T> * ptr() const { return &a; }

 public:
  union {
    Vec3<T> a;
    struct { T x1; T y1; T z1; };
  };
  union {
    Vec3<T> b;
    struct { T x2; T y2; T z2; };
  };
  union {
    Vec3<T> c;
    struct { T x3; T y3; T z3; };
  };
};

using Triangle3i = Triangle3<int>;
using Triangle3f = Triangle3<float>;
using Triangle3d = Triangle3<double>;

#pragma mark -

template <class T>
inline Triangle3<T>::Triangle() : a(), b(), c() {}

template <class T>
inline Triangle3<T>::Triangle(T x1, T y1, T z1,
                              T x2, T y2, T z2,
                              T x3, T y3, T z3)
    : a(x1, y1, z1),
      b(x2, y2, z2),
      c(x3, y3, z3) {}

template <class T>
inline Triangle3<T>::Triangle(const Vec3<T>& a,
                              const Vec3<T>& b,
                              const Vec3<T>& c)
    : a(a),
      b(b),
      c(c) {}

template <class T>
inline Triangle3<T>::Triangle(std::initializer_list<T> list) {
  set(list);
}

template <class T>
inline Triangle3<T>::Triangle(std::initializer_list<Vec3<T>> list) {
  set(list);
}

#pragma mark Mutators

template <class T>
inline void Triangle3<T>::set(T x1, T y1, T z1,
                              T x2, T y2, T z2,
                              T x3, T y3, T z3) {
  a.x = x1; a.y = y1; a.z = z1;
  b.x = x2; b.y = y2; b.z = z2;
  c.x = x3; c.y = y3; c.z = z3;
}

template <class T>
inline void Triangle3<T>::set(const Vec3<T>& a,
                              const Vec3<T>& b,
                              const Vec3<T>& c) {
  this->a = a;
  this->b = b;
  this->c = c;
}

template <class T>
inline void Triangle3<T>::set(std::initializer_list<T> list) {
  auto itr = std::begin(list);
  if (itr == std::end(list)) return; a.x = *itr;
  if (++itr == std::end(list)) return; a.y = *itr;
  if (++itr == std::end(list)) return; a.z = *itr;
  if (++itr == std::end(list)) return; b.x = *itr;
  if (++itr == std::end(list)) return; b.y = *itr;
  if (++itr == std::end(list)) return; b.z = *itr;
  if (++itr == std::end(list)) return; c.x = *itr;
  if (++itr == std::end(list)) return; c.y = *itr;
  if (++itr == std::end(list)) return; c.z = *itr;
}

template <class T>
inline void Triangle3<T>::set(std::initializer_list<Vec3<T>> list) {
  auto itr = std::begin(list);
  if (itr == std::end(list)) return; a = decltype(a)(*itr);
  if (++itr == std::end(list)) return; b = decltype(b)(*itr);
  if (++itr == std::end(list)) return; c = decltype(c)(*itr);
}

template <class T>
inline void Triangle3<T>::reset() {
  *this = Triangle();
}

#pragma mark Element access

template <class T>
inline Vec3<T>& Triangle3<T>::at(int index) {
  switch (index) {
    case 0: return a;
    case 1: return b;
    case 2: return c;
    default:
      assert(false);
      break;
  }
  return a;
}

template <class T>
inline const Vec3<T>& Triangle3<T>::at(int index) const {
  switch (index) {
    case 0: return a;
    case 1: return b;
    case 2: return c;
    default:
      assert(false);
      break;
  }
  return a;
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Triangle3<T>::operator==(const Triangle3<U>& other) const {
  return a == other.a && b == other.b && c == other.c;
}

template <class T>
template <class U>
inline bool Triangle3<T>::operator!=(const Triangle3<U>& other) const {
  return !operator==(other);
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Triangle3<T>& other) {
  return os << "( " << other.a << ", " << other.b << ", " << other.c << " )";
}

}  // namespace math

using math::Triangle;
using math::Triangle3;
using math::Triangle3i;
using math::Triangle3f;
using math::Triangle3d;

}  // namespace takram

#endif  // TAKRAM_MATH_TRIANGLE3_H_
