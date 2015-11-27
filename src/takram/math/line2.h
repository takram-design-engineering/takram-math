//
//  takram/math/line.h
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
#ifndef TAKRAM_MATH_LINE2_H_
#define TAKRAM_MATH_LINE2_H_

#include <cassert>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <utility>

#include "takram/math/promotion.h"
#include "takram/math/side.h"
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
class Line<T, 2> final {
 public:
  using Type = T;
  using Iterator = Vec2<T> *;
  using ConstIterator = const Vec2<T> *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  static constexpr const auto dimensions = Vec2<T>::dimensions;

 public:
  Line();
  Line(T x1, T y1, T x2, T y2);
  Line(const Vec2<T>& a, const Vec2<T>& b);
  Line(std::initializer_list<T> list);
  Line(std::initializer_list<Vec2<T>> list);

  // Implicit conversion
  template <class U>
  Line(const Line2<U>& other);

  // Explicit conversion
  template <class U>
  explicit Line(const Line3<U>& other);

  // Copy semantics
  Line(const Line&) = default;
  Line& operator=(const Line&) = default;

  // Mutators
  void set(T x1, T y1, T x2, T y2);
  void set(const Vec2<T>& a, const Vec2<T>& b);
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
  Vec2<T>& back() { return b; }
  const Vec2<T>& back() const { return b; }

  // Comparison
  template <class V, class U = T>
  bool equals(const Line2<U>& other, V tolerance) const;

  // Attributes
  bool empty() const { return a == b; }
  Vec2<Promote<T>> direction() const;
  Vec2<Promote<T>> normal() const;
  Vec2<Promote<T>> mid() const;

  // Length
  Promote<T> length() const;
  Promote<T> lengthSquared() const;

  // Intersection
  template <class U = T>
  std::pair<bool, Vec2<Promote<T>>> intersect(const Line2<U>& other) const;

  // Projection
  template <class U = T>
  Vec2<T> project(const Vec2<U>& point) const;
  template <class U = T>
  Side side(const Vec2<U>& point) const;

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
};

// Comparison
template <class T, class U>
bool operator==(const Line2<T>& lhs, const Line2<U>& rhs);
template <class T, class U>
bool operator!=(const Line2<T>& lhs, const Line2<U>& rhs);

using Line2i = Line2<int>;
using Line2f = Line2<float>;
using Line2d = Line2<double>;

#pragma mark -

template <class T>
inline Line<T, 2>::Line() : a(), b() {}

template <class T>
inline Line<T, 2>::Line(T x1, T y1, T x2, T y2) : a(x1, y1), b(x2, y2) {}

template <class T>
inline Line<T, 2>::Line(const Vec2<T>& a, const Vec2<T>& b) : a(a), b(b) {}

template <class T>
inline Line<T, 2>::Line(std::initializer_list<T> list) : a(), b() {
  set(list);
}

template <class T>
inline Line<T, 2>::Line(std::initializer_list<Vec2<T>> list) : a(), b() {
  set(list);
}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Line<T, 2>::Line(const Line2<U>& other) : a(other.a), b(other.b) {}

#pragma mark Explicit conversion

template <class T>
template <class U>
inline Line<T, 2>::Line(const Line3<U>& other) : a(other.a), b(other.b) {}

#pragma mark Mutators

template <class T>
inline void Line<T, 2>::set(T x1, T y1, T x2, T y2) {
  a.x = x1; a.y = y1;
  b.x = x2; b.y = y2;
}

template <class T>
inline void Line<T, 2>::set(const Vec2<T>& a, const Vec2<T>& b) {
  this->a = a;
  this->b = b;
}

template <class T>
inline void Line<T, 2>::set(std::initializer_list<T> list) {
  auto itr = std::begin(list);
  if (itr == std::end(list)) return;
  a.x = *itr;
  if (++itr == std::end(list)) return;
  a.y = *itr;
  if (++itr == std::end(list)) return;
  b.x = *itr;
  if (++itr == std::end(list)) return;
  b.y = *itr;
}

template <class T>
inline void Line<T, 2>::set(std::initializer_list<Vec2<T>> list) {
  auto itr = std::begin(list);
  if (itr == std::end(list)) return;
  a = decltype(a)(*itr);
  if (++itr == std::end(list)) return;
  b = decltype(b)(*itr);
}

template <class T>
inline void Line<T, 2>::reset() {
  *this = Line();
}

#pragma mark Element access

template <class T>
inline Vec2<T>& Line<T, 2>::at(int index) {
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
inline const Vec2<T>& Line<T, 2>::at(int index) const {
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

template <class T, class U>
inline bool operator==(const Line2<T>& lhs, const Line2<U>& rhs) {
  return lhs.a == rhs.a && lhs.b == rhs.b;
}

template <class T, class U>
inline bool operator!=(const Line2<U>& lhs, const Line2<U>& rhs) {
  return !(lhs == rhs);
}

template <class T>
template <class V, class U>
inline bool Line<T, 2>::equals(const Line2<U>& other, V tolerance) const {
  return a.equals(other.a, tolerance) && b.equals(other.b, tolerance);
}

#pragma mark Attributes

template <class T>
inline Vec2<Promote<T>> Line<T, 2>::direction() const {
  return (b - a).normalize();
}

template <class T>
inline Vec2<Promote<T>> Line<T, 2>::normal() const {
  return Vec2<Promote<T>>(a.y - b.y, b.x - a.x);
}

template <class T>
inline Vec2<Promote<T>> Line<T, 2>::mid() const {
  return (a + b) / 2;
}

#pragma mark Length

template <class T>
inline Promote<T> Line<T, 2>::length() const {
  return a.distance(b);
}

template <class T>
inline Promote<T> Line<T, 2>::lengthSquared() const {
  return a.distanceSquared(b);
}

#pragma mark Intersection

template <class T>
template <class U>
inline std::pair<bool, Vec2<Promote<T>>> Line<T, 2>::intersect(
    const Line2<U>& other) const {
  const auto denominator = (other.b.y - other.a.y) * (b.x - a.x) -
                           (other.b.x - other.a.x) * (b.y - a.y);
  if (denominator) {
    const auto s = ((other.b.x - other.a.x) * (a.y - other.a.y) -
                    (other.b.y - other.a.y) * (a.x - other.a.x)) / denominator;
    const auto t = ((b.x - a.x) * (a.y - other.a.y) -
                    (b.y - a.y) * (a.x - other.a.x)) / denominator;
    if (0 <= s && s <= 1 && 0 <= t && t <= 1) {
      return std::make_pair(true, a + (b - a) * s);
    }
  }
  return std::make_pair(false, Vec2<Promote<T>>());
}

#pragma mark Projection

template <class T>
template <class U>
inline Vec2<T> Line<T, 2>::project(const Vec2<U>& point) const {
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

template <class T>
template <class U>
inline Side Line<T, 2>::side(const Vec2<U>& point) const {
  const auto d = (b.x - a.x) * (point.y - a.y) - (b.y - a.y) * (point.x - a.x);
  return !d ? (d < 0 ? Side::LEFT : Side::RIGHT) : Side::COINCIDENT;
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Line2<T>& line) {
  return os << "( " << line.a << ", " << line.b << " )";
}

}  // namespace math

using math::Line;
using math::Line2;
using math::Line2i;
using math::Line2f;
using math::Line2d;

}  // namespace takram

template <class T>
struct std::hash<takram::math::Line2<T>> {
  std::size_t operator()(const takram::math::Line2<T>& value) const {
    std::hash<takram::math::Vec2<T>> hash;
    return (hash(value.a) << 0) ^ (hash(value.b) << 1);
  }
};

#endif  // TAKRAM_MATH_LINE2_H_
