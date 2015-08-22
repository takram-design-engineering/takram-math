//
//  takram/math/promotion.h
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
#ifndef TAKRAM_MATH_PROMOTION_H_
#define TAKRAM_MATH_PROMOTION_H_

#include <type_traits>

namespace takram {
namespace math {

template <class T>
struct Promotion1 {
  using Type = typename std::conditional<
    std::is_integral<T>::value,
    double, T
  >::type;
};

template <>
struct Promotion1<float> { using Type = float; };
template <>
struct Promotion1<double> { using Type = double; };
template <>
struct Promotion1<long double> { using Type = long double; };
template <>
struct Promotion1<int> { using Type = double; };

#pragma mark -

template <class T, class U>
struct Promotion2 {
 private:
  using PromotedT = typename Promotion1<T>::Type;
  using PromotedU = typename Promotion1<U>::Type;

 public:
  using Type = typename std::conditional<
    (std::is_floating_point<PromotedT>::value &&
     std::is_floating_point<PromotedU>::value),
    typename std::conditional<
      (std::is_same<long double, PromotedT>::value ||
       std::is_same<long double, PromotedU>::value),
      long double,
      typename std::conditional<
        (std::is_same<double, PromotedT>::value ||
         std::is_same<double, PromotedU>::value),
        double, float
      >::type
    >::type,
    typename std::conditional<
      (!std::is_floating_point<PromotedU>::value &&
       std::is_convertible<PromotedT, PromotedU>::value),
      PromotedU, PromotedT
    >::type
  >::type;
};

template <>
struct Promotion2<float, float> { using Type = float; };
template <>
struct Promotion2<double, double> { using Type = double; };
template <>
struct Promotion2<long double, long double> { using Type = long double; };
template <>
struct Promotion2<int, int> { using Type = double; };
template <>
struct Promotion2<int, float> { using Type = double; };
template <>
struct Promotion2<float, int> { using Type = double; };
template <>
struct Promotion2<int, double> { using Type = double; };
template <>
struct Promotion2<double, int> { using Type = double; };
template <>
struct Promotion2<int, long double> { using Type = long double; };
template <>
struct Promotion2<long double, int> { using Type = long double; };
template <>
struct Promotion2<float, double> { using Type = double; };
template <>
struct Promotion2<double, float> { using Type = double; };
template <>
struct Promotion2<float, long double> { using Type = long double; };
template <>
struct Promotion2<long double, float> { using Type = long double; };
template <>
struct Promotion2<double, long double> { using Type = long double; };
template <>
struct Promotion2<long double, double> { using Type = long double; };

#pragma mark -

template <class T, class U = T>
using Promote = typename Promotion2<T, U>::Type;

}  // namespace math
}  // namespace takram

#endif  // TAKRAM_MATH_PROMOTION_H_
