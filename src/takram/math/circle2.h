//
//  takram/math/circle2.h
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
#ifndef TAKRAM_MATH_CIRCLE2_H_
#define TAKRAM_MATH_CIRCLE2_H_

#include "takram/math/constants.h"
#include "takram/math/promotion.h"
#include "takram/math/vector.h"

namespace takram {
namespace math {

template <class T, int D>
class Circle;

template <class T>
using Circle2 = Circle<T, 2>;

template <class T>
class Circle<T, 2> final {
 public:
  using Type = T;

 public:
  Circle();
  Circle(const Vec2<T>& center, T radius);
  Circle(const Vec2<T>& a, const Vec2<T>& b);
  Circle(const Vec2<T>& a, const Vec2<T>& b, const Vec2<T>& c);

  // Copy semantics
  Circle(const Circle& other) = default;
  Circle& operator=(const Circle& other) = default;

  // Mutators
  void set(const Vec2<T>& center, T radius);
  void set(const Vec2<T>& a, const Vec2<T>& b);
  void set(const Vec2<T>& a, const Vec2<T>& b, const Vec2<T>& c);
  void reset();

  // Comparison
  template <class U>
  bool operator==(const Circle2<U>& other) const;
  template <class U>
  bool operator!=(const Circle2<U>& other) const;
  template <class U>
  bool operator<(const Circle2<U>& other) const;
  template <class U>
  bool operator>(const Circle2<U>& other) const;
  template <class U>
  bool operator<=(const Circle2<U>& other) const;
  template <class U>
  bool operator>=(const Circle2<U>& other) const;

  // Attributes
  bool empty() const { return !radius; }
  Promote<T> diameter() const;
  Promote<T> circumference() const;
  Promote<T> area() const;

  // Canonicalization
  bool canonical() const { return radius > 0; }
  Circle& canonicalize();
  Circle2<Promote<T>> canonicalized() const;

  // Containment
  template <class U = T>
  bool contains(const Vec2<U>& point) const;

 public:
  union {
    Vec2<T> center;
    struct { T x; T y; };
  };
  T radius;
};

using Circle2i = Circle2<int>;
using Circle2f = Circle2<float>;
using Circle2d = Circle2<double>;

#pragma mark -

template <class T>
inline Circle2<T>::Circle() : center(), radius() {}

template <class T>
inline Circle2<T>::Circle(const Vec2<T>& center, T radius)
    : center(center),
      radius(radius) {}

template <class T>
inline Circle2<T>::Circle(const Vec2<T>& a, const Vec2<T>& b) {
  set(a, b);
}

template <class T>
inline Circle2<T>::Circle(const Vec2<T>& a,
                          const Vec2<T>& b,
                          const Vec2<T>& c) {
  set(a, b, c);
}

#pragma mark Mutators

template <class T>
inline void Circle2<T>::set(const Vec2<T>& center, T radius) {
  this->center = center;
  this->radius = radius;
}

template <class T>
inline void Circle2<T>::set(const Vec2<T>& a, const Vec2<T>& b) {
  center = (a + b) / 2;
  radius = center.distance(a);
}

template <class T>
inline void Circle2<T>::set(const Vec2<T>& a,
                            const Vec2<T>& b,
                            const Vec2<T>& c) {
  // TODO:
}

template <class T>
inline void Circle2<T>::reset() {
  *this = Circle();
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Circle2<T>::operator==(const Circle2<U>& other) const {
  return center < other.center || center == other.center;
}

template <class T>
template <class U>
inline bool Circle2<T>::operator!=(const Circle2<U>& other) const {
  return !operator==(other);
}

template <class T>
template <class U>
inline bool Circle2<T>::operator<(const Circle2<U>& other) const {
  return center < other.center ||
      (center == other.center && radius < other.radius);
}

template <class T>
template <class U>
inline bool Circle2<T>::operator>(const Circle2<U>& other) const {
  return center > other.center ||
      (center == other.center && radius > other.radius);
}

template <class T>
template <class U>
inline bool Circle2<T>::operator<=(const Circle2<U>& other) const {
  return operator<(other) || operator==(other);
}

template <class T>
template <class U>
inline bool Circle2<T>::operator>=(const Circle2<U>& other) const {
  return operator>(other) || operator==(other);
}

#pragma mark Attributes

template <class T>
inline Promote<T> Circle2<T>::diameter() const {
  return radius + radius;
}

template <class T>
inline Promote<T> Circle2<T>::circumference() const {
  return radius * tau<T>();
}

template <class T>
inline Promote<T> Circle2<T>::area() const {
  return radius * radius * pi<T>();
}

#pragma mark Canonicalization

template <class T>
inline Circle2<T>& Circle2<T>::canonicalize() {
  if (radius < 0) {
    radius = -radius;
  }
  return *this;
}

template <class T>
inline Circle2<Promote<T>> Circle2<T>::canonicalized() const {
  return Circle2<Promote<T>>(*this).canonicalize();
}

#pragma mark Containment

template <class T>
template <class U>
inline bool Circle2<T>::contains(const Vec2<U>& point) const {
  return center.distanceSquared(point) <= radius * radius;
}

}  // namespace math

using math::Circle2;
using math::Circle2i;
using math::Circle2f;
using math::Circle2d;

}  // namespace takram

#endif  // TAKRAM_MATH_CIRCLE2_H_
