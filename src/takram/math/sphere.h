//
//  takram/math/sphere.h
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
#ifndef TAKRAM_MATH_SPHERE_H_
#define TAKRAM_MATH_SPHERE_H_

#include <ostream>

#include "takram/math/vector.h"

namespace takram {
namespace math {

template <class T>
class Sphere final {
 public:
  using Type = T;

 public:
  // Constructors
  Sphere();
  Sphere(const Vector3<T>& center, T radius);

  // Implicit conversion
  template <class U>
  Sphere(const Sphere<U>& other);

  // Copy and assign
  Sphere(const Sphere& other) = default;
  Sphere& operator=(const Sphere& other) = default;

  // Mutators
  void set(const Vector3<T>& center, T radius);
  void set(const Sphere& other);
  void reset();

  // Comparison
  template <class U>
  bool operator==(const Sphere<U>& other) const;
  template <class U>
  bool operator!=(const Sphere<U>& other) const;

  // Properties
  const Vector3<T>& center() const { return center_; }
  void set_center(const Vector3<T>& value);
  T radius() const { return radius_; }
  void set_radius(T value);

  // Attributes
  bool empty() const { return !radius_; }

 private:
  Vector3<T> center_;
  T radius_;
};

#pragma mark -

template <class T>
inline Sphere<T>::Sphere() : radius_() {}

template <class T>
inline Sphere<T>::Sphere(const Vector3<T>& center, T radius)
    : center_(center),
      radius_(radius) {}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Sphere<T>::Sphere(const Sphere<U>& other)
    : center_(other.center_),
      radius_(other.radius_) {}

#pragma mark Mutators

template <class T>
inline void Sphere<T>::set(const Vector3<T>& center, T radius) {
  center_ = center;
  radius_ = radius;
}

template <class T>
inline void Sphere<T>::set(const Sphere& other) {
  *this = other;
}

template <class T>
inline void Sphere<T>::reset() {
  *this = Sphere<T>();
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Sphere<T>::operator==(const Sphere<U>& other) const {
  return center_ == other.center_ && radius_ == other.radius_;
}

template <class T>
template <class U>
inline bool Sphere<T>::operator!=(const Sphere<U>& other) const {
  return !operator==(other);
}

#pragma mark Properties

template <class T>
inline void Sphere<T>::set_center(const Vector3<T>& value) {
  center_ = value;
}

template <class T>
inline void Sphere<T>::set_radius(T value) {
  radius_ = value;
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Sphere<T>& other) {
  return os << "( " << other.center() << ", " << other.radius() << " )";
}

}  // namespace math
}  // namespace takram

#endif  // TAKRAM_MATH_SPHERE_H_
