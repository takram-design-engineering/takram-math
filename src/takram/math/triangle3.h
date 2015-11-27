//
//  takram/math/triangle3.h
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
#ifndef TAKRAM_MATH_TRIANGLE3_H_
#define TAKRAM_MATH_TRIANGLE3_H_

#include <cassert>
#include <cmath>
#include <cstddef>
#include <functional>
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
  Triangle(const Triangle&) = default;
  Triangle& operator=(const Triangle&) = default;

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
  template <class V, class U = T>
  bool equals(const Triangle3<U>& other, V tolerance) const;

  // Attributes
  bool empty() const { return a.empty() && b.empty() && c.empty(); }
  Promote<T> area() const;
  Promote<T> perimeter() const;
  Vec3<Promote<T>> centroid() const;

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

// Comparison
template <class T, class U>
bool operator==(const Triangle3<T>& lhs, const Triangle3<U>& rhs);
template <class T, class U>
bool operator!=(const Triangle3<T>& lhs, const Triangle3<U>& rhs);

using Triangle3i = Triangle3<int>;
using Triangle3f = Triangle3<float>;
using Triangle3d = Triangle3<double>;

#pragma mark -

template <class T>
inline Triangle<T, 3>::Triangle() : a(), b(), c() {}

template <class T>
inline Triangle<T, 3>::Triangle(T x1, T y1, T z1,
                                T x2, T y2, T z2,
                                T x3, T y3, T z3)
    : a(x1, y1, z1),
      b(x2, y2, z2),
      c(x3, y3, z3) {}

template <class T>
inline Triangle<T, 3>::Triangle(const Vec3<T>& a,
                                const Vec3<T>& b,
                                const Vec3<T>& c)
    : a(a),
      b(b),
      c(c) {}

template <class T>
inline Triangle<T, 3>::Triangle(std::initializer_list<T> list) : a(), b(), c() {
  set(list);
}

template <class T>
inline Triangle<T, 3>::Triangle(std::initializer_list<Vec3<T>> list)
    : a(),
      b(),
      c() {
  set(list);
}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Triangle<T, 3>::Triangle(const Triangle3<U>& other)
    : a(other.a),
      b(other.b),
      c(other.c) {}

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Triangle<T, 3>::Triangle(const Triangle2<U>& other)
    : a(other.a),
      b(other.b),
      c(other.c) {}

#pragma mark Mutators

template <class T>
inline void Triangle<T, 3>::set(T x1, T y1, T z1,
                                T x2, T y2, T z2,
                                T x3, T y3, T z3) {
  a.x = x1; a.y = y1; a.z = z1;
  b.x = x2; b.y = y2; b.z = z2;
  c.x = x3; c.y = y3; c.z = z3;
}

template <class T>
inline void Triangle<T, 3>::set(const Vec3<T>& a,
                                const Vec3<T>& b,
                                const Vec3<T>& c) {
  this->a = a;
  this->b = b;
  this->c = c;
}

template <class T>
inline void Triangle<T, 3>::set(std::initializer_list<T> list) {
  auto itr = std::begin(list);
  if (itr == std::end(list)) return;
  a.x = *itr;
  if (++itr == std::end(list)) return;
  a.y = *itr;
  if (++itr == std::end(list)) return;
  a.z = *itr;
  if (++itr == std::end(list)) return;
  b.x = *itr;
  if (++itr == std::end(list)) return;
  b.y = *itr;
  if (++itr == std::end(list)) return;
  b.z = *itr;
  if (++itr == std::end(list)) return;
  c.x = *itr;
  if (++itr == std::end(list)) return;
  c.y = *itr;
  if (++itr == std::end(list)) return;
  c.z = *itr;
}

template <class T>
inline void Triangle<T, 3>::set(std::initializer_list<Vec3<T>> list) {
  auto itr = std::begin(list);
  if (itr == std::end(list)) return;
  a = decltype(a)(*itr);
  if (++itr == std::end(list)) return;
  b = decltype(b)(*itr);
  if (++itr == std::end(list)) return;
  c = decltype(c)(*itr);
}

template <class T>
inline void Triangle<T, 3>::reset() {
  *this = Triangle();
}

#pragma mark Element access

template <class T>
inline Vec3<T>& Triangle<T, 3>::at(int index) {
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
inline const Vec3<T>& Triangle<T, 3>::at(int index) const {
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

template <class T, class U>
inline bool operator==(const Triangle3<T>& lhs, const Triangle3<U>& rhs) {
  return lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c;
}

template <class T, class U>
inline bool operator!=(const Triangle3<T>& lhs, const Triangle3<U>& rhs) {
  return !(lhs == rhs);
}

template <class T>
template <class V, class U>
inline bool Triangle<T, 3>::equals(const Triangle3<U>& other,
                                   V tolerance) const {
  return (a.equals(other.a, tolerance) &&
          b.equals(other.b, tolerance) &&
          c.equals(other.c, tolerance));
}

#pragma mark Attributes

template <class T>
inline Promote<T> Triangle<T, 3>::area() const {
  return (b - a).cross(c - a).magnitude() / 2;
}

template <class T>
inline Promote<T> Triangle<T, 3>::perimeter() const {
  return std::sqrt(a.distanceSquared(b) +
                   b.distanceSquared(c) +
                   c.distanceSquared(a));
}

template <class T>
inline Vec3<Promote<T>> Triangle<T, 3>::centroid() const {
  return (a + b + c) / 3;
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Triangle3<T>& tri) {
  return os << "( " << tri.a << ", " << tri.b << ", " << tri.c << " )";
}

}  // namespace math

using math::Triangle;
using math::Triangle3;
using math::Triangle3i;
using math::Triangle3f;
using math::Triangle3d;

}  // namespace takram

template <class T>
struct std::hash<takram::math::Triangle3<T>> {
  std::size_t operator()(const takram::math::Triangle3<T>& value) const {
    std::hash<takram::math::Vec3<T>> hash;
    return (hash(value.a) << 0) ^ (hash(value.b) << 1) ^ (hash(value.c) << 1);
  }
};

#endif  // TAKRAM_MATH_TRIANGLE3_H_
