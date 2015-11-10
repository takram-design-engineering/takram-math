//
//  takram/math/roots.h
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
#ifndef TAKRAM_MATH_ROOTS_H_
#define TAKRAM_MATH_ROOTS_H_

#include <cmath>

namespace takram {
namespace math {

template <class A, class B, class Iterator>
unsigned int solveLinear(A a, B b, Iterator result);
template <class A, class B, class C, class Iterator>
unsigned int solveQuadratic(A a, B b, C c, Iterator result);

#pragma mark -

template <class A, class B, class Iterator>
inline unsigned int solveLinear(A a, B b, Iterator result) {
  if (!a) {
    return 0;
  }
  *result = -b / a;
  return 1;
}

template <class A, class B, class C, class Iterator>
inline unsigned int solveQuadratic(A a, B b, C c, Iterator result) {
  if (!a) {
    return solveLinear(b, c, result);
  }
  const auto discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return 0;
  }
  if (!discriminant) {
    *result = -b / (2 * a);
    return 1;
  }
  const auto d = std::sqrt(discriminant);
  *result = (-b - d) / (2 * a);
  *++result = (-b + d) / (2 * a);
  return 2;
}

}  // namespace math
}  // namespace takram

#endif  // TAKRAM_MATH_ROOTS_H_
