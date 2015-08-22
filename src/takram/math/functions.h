//
//  takram/math/functions.h
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
#ifndef TAKRAM_MATH_FUNCTIONS_H_
#define TAKRAM_MATH_FUNCTIONS_H_

namespace takram {
namespace math {

template <class T, class U, class V>
constexpr T lerp(T start, U stop, V amount);
template <class T, class U, class V>
constexpr T norm(T amount, U start, V stop);
template <class T, class U, class V>
constexpr T normalize(T amount, U start, V stop);
template <class T, class U, class V>
constexpr T clamp(T value, U min, V max);
template <class T, class U, class V>
constexpr T constrain(T value, U min, V max);
template <class T, class U, class V>
constexpr T map(T value, U min1, U max1, V min2, V max2);

#pragma mark -

template <class T, class U, class V>
constexpr T lerp(T start, U stop, V amount) {
  return start + (stop - start) * amount;
}

template <class T, class U, class V>
constexpr T norm(T amount, U start, V stop) {
  return (amount - start) / (stop - start);
}

template <class T, class U, class V>
constexpr T normalize(T amount, U start, V stop) {
  return norm(amount, start, stop);
}

template <class T, class U, class V>
constexpr T clamp(T value, U min, V max) {
  return (value < min ? min : (value > max ? max : value));
}

template <class T, class U, class V>
constexpr T constrain(T value, U min, V max) {
  return clamp(value, min, max);
}

template <class T, class U, class V>
constexpr T map(T value, U min1, U max1, V min2, V max2) {
  return min2 + (max2 - min2) * ((value - min1) / (max1 - min1));
}

}  // namespace math
}  // namespace takram

#endif  // TAKRAM_MATH_FUNCTIONS_H_
