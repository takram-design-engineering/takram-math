//
//  takram/math/triangle2.h
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
#ifndef TAKRAM_MATH_TRIANGLE2_H_
#define TAKRAM_MATH_TRIANGLE2_H_

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
class Triangle<T, 2> final {
 public:
  using Type = T;
  using Iterator = Vec2<T> *;
  using ConstIterator = const Vec2<T> *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const auto dimensions = Vec2<T>::dimensions;

 public:
  Triangle();
  Triangle(T x1, T y1, T x2, T y2, T x3, T y3);
  Triangle(const Vec2<T>& a, const Vec2<T>& b, const Vec2<T>& c);
  Triangle(std::initializer_list<T> list);
  Triangle(std::initializer_list<Vec2<T>> list);

  // Implicit conversion
  template <class U>
  Triangle(const Triangle2<U>& other);

  // Explicit conversion
  template <class U>
  explicit Triangle(const Triangle3<U>& other);

  // Copy semantics
  Triangle(const Triangle&) = default;
  Triangle& operator=(const Triangle&) = default;

  // Mutators
  void set(T x1, T y1, T x2, T y2, T x3, T y3);
  void set(const Vec2<T>& a, const Vec2<T>& b, const Vec2<T>& c);
  void set(std::initializer_list<T> list);
  void set(std::initializer_list<Vec2<T>> list);
  void reset();

  // Element access
  Vec2<T>& operator[](int index) { return at(index); }
  const Vec2<T>& operator[](int index) const { return at(index); }
  Vec2<T>& at(int index);
  const Vec2<T>& at(int index) const;
  Vec2<T>& front() { return a; }
  const Vec2<T>& front() const { return a; }
  Vec2<T>& back() { return c; }
  const Vec2<T>& back() const { return c; }

  // Comparison
  template <class U>
  bool operator==(const Triangle2<U>& other) const;
  template <class U>
  bool operator!=(const Triangle2<U>& other) const;

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
  Vec2<T> * ptr() { return &a; }
  const Vec2<T> * ptr() const { return &a; }

 public:
  union {
    Vec2<T> a;
    struct { T x1; T y1; };
  };
  union {
    Vec2<T> b;
    struct { T x2; T y2; };
  };
  union {
    Vec2<T> c;
    struct { T x3; T y3; };
  };
};

using Triangle2i = Triangle2<int>;
using Triangle2f = Triangle2<float>;
using Triangle2d = Triangle2<double>;

#pragma mark -

template <class T>
inline Triangle2<T>::Triangle() : a(), b(), c() {}

template <class T>
inline Triangle2<T>::Triangle(T x1, T y1, T x2, T y2, T x3, T y3)
    : a(x1, y1),
      b(x2, y2),
      c(x3, y3) {}

template <class T>
inline Triangle2<T>::Triangle(const Vec2<T>& a,
                              const Vec2<T>& b,
                              const Vec2<T>& c)
    : a(a),
      b(b),
      c(c) {}

template <class T>
inline Triangle2<T>::Triangle(std::initializer_list<T> list) : a(), b(), c() {
  set(list);
}

template <class T>
inline Triangle2<T>::Triangle(std::initializer_list<Vec2<T>> list)
    : a(),
      b(),
      c() {
  set(list);
}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Triangle2<T>::Triangle(const Triangle2<U>& other)
    : a(other.a),
      b(other.b),
      c(other.c) {}

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Triangle2<T>::Triangle(const Triangle3<U>& other)
    : a(other.a),
      b(other.b),
      c(other.c) {}

#pragma mark Mutators

template <class T>
inline void Triangle2<T>::set(T x1, T y1, T x2, T y2, T x3, T y3) {
  a.x = x1; a.y = y1;
  b.x = x2; b.y = y2;
  c.x = x3; c.y = y3;
}

template <class T>
inline void Triangle2<T>::set(const Vec2<T>& a,
                              const Vec2<T>& b,
                              const Vec2<T>& c) {
  this->a = a;
  this->b = b;
  this->c = c;
}

template <class T>
inline void Triangle2<T>::set(std::initializer_list<T> list) {
  auto itr = std::begin(list);
  if (itr == std::end(list)) return;
  a.x = *itr;
  if (++itr == std::end(list)) return;
  a.y = *itr;
  if (++itr == std::end(list)) return;
  b.x = *itr;
  if (++itr == std::end(list)) return;
  b.y = *itr;
  if (++itr == std::end(list)) return;
  c.x = *itr;
  if (++itr == std::end(list)) return;
  c.y = *itr;
}

template <class T>
inline void Triangle2<T>::set(std::initializer_list<Vec2<T>> list) {
  auto itr = std::begin(list);
  if (itr == std::end(list)) return;
  a = decltype(a)(*itr);
  if (++itr == std::end(list)) return;
  b = decltype(b)(*itr);
  if (++itr == std::end(list)) return;
  c = decltype(c)(*itr);
}

template <class T>
inline void Triangle2<T>::reset() {
  *this = Triangle();
}

#pragma mark Element access

template <class T>
inline Vec2<T>& Triangle2<T>::at(int index) {
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
inline const Vec2<T>& Triangle2<T>::at(int index) const {
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
inline bool Triangle2<T>::operator==(const Triangle2<U>& other) const {
  return a == other.a && b == other.b && c == other.c;
}

template <class T>
template <class U>
inline bool Triangle2<T>::operator!=(const Triangle2<U>& other) const {
  return !operator==(other);
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Triangle2<T>& tri) {
  return os << "( " << tri.a << ", " << tri.b << ", " << tri.c << " )";
}

}  // namespace math

using math::Triangle;
using math::Triangle2;
using math::Triangle2i;
using math::Triangle2f;
using math::Triangle2d;

}  // namespace takram

#endif  // TAKRAM_MATH_TRIANGLE2_H_
