//
//  takram/math/line.h
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
#ifndef TAKRAM_MATH_LINE3_H_
#define TAKRAM_MATH_LINE3_H_

#include <cassert>
#include <initializer_list>
#include <iterator>
#include <ostream>

#include "takram/math/promotion.h"
#include "takram/math/vector.h"

namespace takram {
namespace math {

template <class T, int D>
class Line;

template <class T>
using Line2 = Line<T, 2>;
template <class T>
using Line3 = Line<T, 3>;

template <class T>
class Line<T, 3> final {
 public:
  using Type = T;
  using Iterator = Vec3<T> *;
  using ConstIterator = const Vec3<T> *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const auto dimensions = Vec3<T>::dimensions;

 public:
  Line();
  Line(T x1, T y1, T z1, T x2, T y2, T z2);
  Line(const Vec3<T>& a, const Vec3<T>& b);
  Line(std::initializer_list<T> list);
  Line(std::initializer_list<Vec3<T>> list);

  // Implicit conversion
  template <class U>
  Line(const Line3<U>& other);

  // Explicit conversion
  template <class U>
  explicit Line(const Line2<U>& other);

  // Copy semantics
  Line(const Line&) = default;
  Line& operator=(const Line&) = default;

  // Mutators
  void set(T x1, T y1, T z1, T x2, T y2, T z2);
  void set(const Vec3<T>& a, const Vec3<T>& b);
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
  Vec3<T>& back() { return b; }
  const Vec3<T>& back() const { return b; }

  // Comparison
  template <class U>
  bool operator==(const Line3<U>& other) const;
  template <class U>
  bool operator!=(const Line3<U>& other) const;

  // Attributes
  bool empty() const { return a == b; }
  Vec3<Promote<T>> direction() const;
  Vec3<Promote<T>> normal() const;
  Vec3<Promote<T>> mid() const;

  // Length
  Promote<T> length() const;
  Promote<T> lengthSquared() const;

  // Projection
  template <class U = T>
  Vec3<T> project(const Vec3<U>& point) const;

  // Iterator
  Iterator begin() { return &a; }
  ConstIterator begin() const { return &a; }
  Iterator end() { return &b + 1; }
  ConstIterator end() const { return &b + 1; }
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
};

using Line3i = Line3<int>;
using Line3f = Line3<float>;
using Line3d = Line3<double>;

#pragma mark -

template <class T>
inline Line3<T>::Line() : a(), b() {}

template <class T>
inline Line3<T>::Line(T x1, T y1, T z1, T x2, T y2, T z2)
    : a(x1, y1, z1),
      b(x2, y2, z2) {}

template <class T>
inline Line3<T>::Line(const Vec3<T>& a, const Vec3<T>& b) : a(a), b(b) {}

template <class T>
inline Line3<T>::Line(std::initializer_list<T> list) : a(), b() {
  set(list);
}

template <class T>
inline Line3<T>::Line(std::initializer_list<Vec3<T>> list) : a(), b() {
  set(list);
}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Line3<T>::Line(const Line3<U>& other) : a(other.a), b(other.b) {}

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Line3<T>::Line(const Line2<U>& other) : a(other.a), b(other.b) {}

#pragma mark Mutators

template <class T>
inline void Line3<T>::set(T x1, T y1, T z1, T x2, T y2, T z2) {
  a.x = x1; a.y = y1; a.z = z1;
  b.x = x2; b.y = y2; b.z = z2;
}

template <class T>
inline void Line3<T>::set(const Vec3<T>& a, const Vec3<T>& b) {
  this->a = a;
  this->b = b;
}

template <class T>
inline void Line3<T>::set(std::initializer_list<T> list) {
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
}

template <class T>
inline void Line3<T>::set(std::initializer_list<Vec3<T>> list) {
  auto itr = std::begin(list);
  if (itr == std::end(list)) return;
  a = decltype(a)(*itr);
  if (++itr == std::end(list)) return;
  b = decltype(b)(*itr);
}

template <class T>
inline void Line3<T>::reset() {
  *this = Line();
}

#pragma mark Element access

template <class T>
inline Vec3<T>& Line3<T>::at(int index) {
  switch (index) {
    case 0: return a;
    case 1: return b;
    default:
      assert(false);
      break;
  }
  return a;
}

template <class T>
inline const Vec3<T>& Line3<T>::at(int index) const {
  switch (index) {
    case 0: return a;
    case 1: return b;
    default:
      assert(false);
      break;
  }
  return a;
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Line3<T>::operator==(const Line3<U>& other) const {
  return a == other.a && b == other.b;
}

template <class T>
template <class U>
inline bool Line3<T>::operator!=(const Line3<U>& other) const {
  return !operator==(other);
}

#pragma mark Attributes

template <class T>
inline Vec3<Promote<T>> Line3<T>::direction() const {
  return (b - a).normalize();
}

template <class T>
inline Vec3<Promote<T>> Line3<T>::normal() const {
  return b.cross(a);
}

template <class T>
inline Vec3<Promote<T>> Line3<T>::mid() const {
  return (a + b) / 2;
}

#pragma mark Length

template <class T>
inline Promote<T> Line3<T>::length() const {
  return a.distance(b);
}

template <class T>
inline Promote<T> Line3<T>::lengthSquared() const {
  return a.distanceSquared(b);
}

#pragma mark Projection

template <class T>
template <class U>
inline Vec3<T> Line3<T>::project(const Vec3<U>& point) const {
  const auto ab = b - a;
  const auto magnitude = ab.magnitudeSquared();
  if (!magnitude) {
    return a;
  }
  const auto scale = (point - a).dot(ab) / magnitude;
  if (scale <= 0) {
    return a;
  } else if (scale >= 1) {
    return b;
  }
  return a + ab * scale;
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Line3<T>& line) {
  return os << "( " << line.a << ", " << line.b << " )";
}

}  // namespace math

using math::Line;
using math::Line3;
using math::Line3i;
using math::Line3f;
using math::Line3d;

}  // namespace takram

#endif  // TAKRAM_MATH_LINE3_H_
