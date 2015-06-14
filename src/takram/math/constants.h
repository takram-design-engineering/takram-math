//
//  takram/math/constants.h
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
#ifndef TAKRAM_MATH_CONSTANTS_H_
#define TAKRAM_MATH_CONSTANTS_H_

namespace takram {
namespace math {

template <class T = double>
constexpr const T e = 2.718281828459045235360287471352662497e+00L;
template constexpr const float e<float>;
template constexpr const double e<double>;
template constexpr const long double e<long double>;

template <class T = double>
constexpr const T pi = 3.141592653589793238462643383279502884e+00L;
template constexpr const float pi<float>;
template constexpr const double pi<double>;
template constexpr const long double pi<long double>;

template <class T = double>
constexpr const T half_pi = 1.570796326794896619231321691639751442e+00L;
template constexpr const float half_pi<float>;
template constexpr const double half_pi<double>;
template constexpr const long double half_pi<long double>;

template <class T = double>
constexpr const T third_pi = 1.047197551196597746154214461093167628e+00L;
template constexpr const float third_pi<float>;
template constexpr const double third_pi<double>;
template constexpr const long double third_pi<long double>;

template <class T = double>
constexpr const T quarter_pi = 0.785398163397448309615660845819875721+00L;
template constexpr const float quarter_pi<float>;
template constexpr const double quarter_pi<double>;
template constexpr const long double quarter_pi<long double>;

template <class T = double>
constexpr const T two_pi = 6.283185307179586476925286766559005768e+00L;
template constexpr const float two_pi<float>;
template constexpr const double two_pi<double>;
template constexpr const long double two_pi<long double>;

template <class T = double>
constexpr const T tau = 6.283185307179586476925286766559005768e+00L;
template constexpr const float tau<float>;
template constexpr const double tau<double>;
template constexpr const long double tau<long double>;

template <class T = double>
constexpr const T degree = 1.745329251994329576923690768488612713e-02L;
template constexpr const float degree<float>;
template constexpr const double degree<double>;
template constexpr const long double degree<long double>;

template <class T = double>
constexpr const T radian = 5.729577951308232087679815481410517033e+01L;
template constexpr const float radian<float>;
template constexpr const double radian<double>;
template constexpr const long double radian<long double>;

}  // namespace math
}  // namespace takram

#endif  // TAKRAM_MATH_CONSTANTS_H_
