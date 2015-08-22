//
//  takram/math.h
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
#ifndef TAKRAM_MATH_H_
#define TAKRAM_MATH_H_

namespace takram {
namespace math {

extern const double version_number;
extern const unsigned char version_string[];

}  // namespace math
}  // namespace takram

#include "takram/math/axis.h"
#include "takram/math/circle.h"
#include "takram/math/constants.h"
#include "takram/math/functions.h"
#include "takram/math/line.h"
#include "takram/math/promotion.h"
#include "takram/math/random.h"
#include "takram/math/rectangle.h"
#include "takram/math/size.h"
#include "takram/math/triangle.h"
#include "takram/math/vector.h"

#endif  // TAKRAM_MATH_H_
