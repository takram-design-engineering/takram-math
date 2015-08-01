//
//  takram/math/vector.h
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
#ifndef TAKRAM_MATH_VECTOR_H_
#define TAKRAM_MATH_VECTOR_H_

#if TAKRAM_HAS_BOOST
#include <boost/polygon/isotropy.hpp>
#include <boost/polygon/point_concept.hpp>
#endif  // TAKRAM_HAS_BOOST

#include "takram/math/vector2.h"
#include "takram/math/vector3.h"
#include "takram/math/vector4.h"

#if TAKRAM_HAS_BOOST

template <class T, int D>
struct boost::polygon::geometry_concept<takram::Vector<T, D>> {
  using type = boost::polygon::point_concept;
};

template <class T, int D>
struct boost::polygon::point_traits<takram::Vector<T, D>> {
  using coordinate_type = typename takram::Vector<T, D>::Type;

  static coordinate_type get(const takram::Vector<T, D>& point,
                             boost::polygon::orientation_2d orientation) {
    return orientation == boost::polygon::HORIZONTAL ? point.x : point.y;
  }
};

template <class T, int D>
struct boost::polygon::point_mutable_traits<takram::Vector<T, D>> {
  using coordinate_type = typename takram::Vector<T, D>::Type;

  static void set(takram::Vector<T, D>& point,
                  boost::polygon::orientation_2d orientation,
                  coordinate_type value) {
    if (orientation == boost::polygon::HORIZONTAL) {
      point.x = value;
    } else {
      point.y = value;
    }
  }

  static takram::Vector<T, D> construct(coordinate_type x, coordinate_type y) {
    return takram::Vector<T, D>(x, y);
  }
};

#endif  // TAKRAM_HAS_BOOST

#endif  // TAKRAM_MATH_VECTOR_H_
