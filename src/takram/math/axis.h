//
//  takram/math/axis.h
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
#ifndef TAKRAM_MATH_AXIS_H_
#define TAKRAM_MATH_AXIS_H_

#include <cassert>
#include <ostream>

namespace takram {
namespace math {

enum class Axis : int {
  X = 0,
  Y = 1,
  Z = 2,
  W = 3
};

inline std::ostream& operator<<(std::ostream& os, Axis axis) {
  switch (axis) {
    case Axis::X: os << "x"; break;
    case Axis::Y: os << "y"; break;
    case Axis::Z: os << "z"; break;
    case Axis::W: os << "w"; break;
    default:
      assert(false);
      break;
  }
  return os;
}

}  // namespace math

using math::Axis;

}  // namespace takram

#endif  // TAKRAM_MATH_AXIS_H_
