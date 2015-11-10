//
//  size_test.cc
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

#include <cstdint>
#include <random>
#include <tuple>
#include <type_traits>

#include "gtest/gtest.h"

#include "takram/math/promotion.h"
#include "takram/math/random.h"
#include "takram/math/size.h"

namespace takram {
namespace math {

template <class T>
class SizeTest : public ::testing::Test {};

using Types = ::testing::Types<
  std::int16_t,
  std::uint16_t,
  std::int32_t,
  std::uint32_t,
  float,
  double
>;
TYPED_TEST_CASE(SizeTest, Types);

TEST(SizeTest, Concepts) {
  ASSERT_TRUE(std::is_default_constructible<Size2d>::value);
  ASSERT_TRUE(std::is_copy_constructible<Size2d>::value);
  ASSERT_TRUE(std::is_copy_assignable<Size2d>::value);
  ASSERT_TRUE(std::is_move_constructible<Size2d>::value);
  ASSERT_TRUE(std::is_move_assignable<Size2d>::value);
  ASSERT_FALSE(std::has_virtual_destructor<Size2d>::value);
}

TYPED_TEST(SizeTest, DefaultConstructible) {
  {
    Size2<TypeParam> s;
    ASSERT_EQ(s.width, TypeParam());
    ASSERT_EQ(s.height, TypeParam());
  } {
    Size3<TypeParam> s;
    ASSERT_EQ(s.width, TypeParam());
    ASSERT_EQ(s.height, TypeParam());
    ASSERT_EQ(s.depth, TypeParam());
  }
}

TYPED_TEST(SizeTest, ConstructibleWithValue) {
  const auto value = math::Random<>().uniform<TypeParam>();
  {
    Size2<TypeParam> s(value);
    ASSERT_EQ(s.width, value);
    ASSERT_EQ(s.height, value);
  } {
    Size3<TypeParam> s(value);
    ASSERT_EQ(s.width, value);
    ASSERT_EQ(s.height, value);
    ASSERT_EQ(s.depth, value);
  }
}

TYPED_TEST(SizeTest, ConstructibleWithValues) {
  const auto w = math::Random<>().uniform<TypeParam>();
  const auto h = math::Random<>().uniform<TypeParam>();
  const auto d = math::Random<>().uniform<TypeParam>();
  {
    Size2<TypeParam> s(w, h);
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, h);
  } {
    Size3<TypeParam> s(w, h, d);
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, h);
    ASSERT_EQ(s.depth, d);
  }
}

TYPED_TEST(SizeTest, ConstructibleWithTuple) {
  const auto w = math::Random<>().uniform<TypeParam>();
  const auto h = math::Random<>().uniform<TypeParam>();
  const auto d = math::Random<>().uniform<TypeParam>();
  {
    Size2<TypeParam> s(std::make_tuple(w, h));
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, h);
  } {
    Size3<TypeParam> s(std::make_tuple(w, h, d));
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, h);
    ASSERT_EQ(s.depth, d);
  }
}

TYPED_TEST(SizeTest, ConstructibleWithInitializerList) {
  const auto w = math::Random<>().uniform<TypeParam>();
  const auto h = math::Random<>().uniform<TypeParam>();
  const auto d = math::Random<>().uniform<TypeParam>();
  {
    Size2<TypeParam> s{w};
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, TypeParam());
  } {
    Size2<TypeParam> s{w, h, TypeParam()};
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, h);
  } {
    Size3<TypeParam> s{w};
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, TypeParam());
    ASSERT_EQ(s.depth, TypeParam());
  } {
    Size3<TypeParam> s{w, h, d, TypeParam()};
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, h);
    ASSERT_EQ(s.depth, d);
  }
}

TYPED_TEST(SizeTest, CopyConstructible) {
  const auto w = math::Random<>().uniform<TypeParam>();
  const auto h = math::Random<>().uniform<TypeParam>();
  const auto d = math::Random<>().uniform<TypeParam>();
  {
    Size2<TypeParam> s1(w, h);
    Size2<TypeParam> s2(s1);
    ASSERT_EQ(s1, s2);
  } {
    Size3<TypeParam> s1(w, h, d);
    Size3<TypeParam> s2(s1);
    ASSERT_EQ(s1, s2);
  }
}

TYPED_TEST(SizeTest, CopyAssignable) {
  const auto w = math::Random<>().uniform<TypeParam>();
  const auto h = math::Random<>().uniform<TypeParam>();
  const auto d = math::Random<>().uniform<TypeParam>();
  {
    Size2<TypeParam> s1(w, h);
    Size2<TypeParam> s2;
    s2 = s1;
    ASSERT_EQ(s1, s2);
  } {
    Size3<TypeParam> s1(w, h, d);
    Size3<TypeParam> s2;
    s2 = s1;
    ASSERT_EQ(s1, s2);
  }
}

TYPED_TEST(SizeTest, TupleAssignable) {
  const auto w = math::Random<>().uniform<TypeParam>();
  const auto h = math::Random<>().uniform<TypeParam>();
  const auto d = math::Random<>().uniform<TypeParam>();
  {
    Size2<TypeParam> s;
    s = std::make_tuple(w, h);
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, h);
  } {
    Size3<TypeParam> s;
    s = std::make_tuple(w, h, d);
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, h);
    ASSERT_EQ(s.depth, d);
  }
}

TYPED_TEST(SizeTest, InitializerListAssignable) {
  const auto w = math::Random<>().uniform<TypeParam>();
  const auto h = math::Random<>().uniform<TypeParam>();
  const auto d = math::Random<>().uniform<TypeParam>();
  {
    Size2<TypeParam> s;
    s = {w};
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, TypeParam());
  } {
    Size2<TypeParam> s;
    s = {w, h, TypeParam()};
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, h);
  } {
    Size3<TypeParam> s;
    s = {w};
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, TypeParam());
    ASSERT_EQ(s.depth, TypeParam());
  } {
    Size3<TypeParam> s;
    s = {w, h, d, TypeParam()};
    ASSERT_EQ(s.width, w);
    ASSERT_EQ(s.height, h);
    ASSERT_EQ(s.depth, d);
  }
}

TYPED_TEST(SizeTest, ImplicitlyConvertibleFromOtherTypes) {
  const auto w = math::Random<>().uniform<TypeParam>();
  const auto h = math::Random<>().uniform<TypeParam>();
  const auto d = math::Random<>().uniform<TypeParam>();
  {
    Size2<TypeParam> s(w, h);
    Size2<bool> s_bool(s);
    Size2<char> s_char(s);
    Size2<std::int8_t> s_int8(s);
    Size2<std::uint8_t> s_uint8(s);
    Size2<std::int16_t> s_int16(s);
    Size2<std::uint16_t> s_uint16(s);
    Size2<std::int32_t> s_int32(s);
    Size2<std::uint32_t> s_uint32(s);
    Size2<float> s_float(s);
    Size2<double> s_double(s);
    ASSERT_EQ(s_bool.width, static_cast<bool>(w));
    ASSERT_EQ(s_char.width, static_cast<char>(w));
    ASSERT_EQ(s_int8.width, static_cast<std::int8_t>(w));
    ASSERT_EQ(s_uint8.width, static_cast<std::uint8_t>(w));
    ASSERT_EQ(s_int16.width, static_cast<std::int16_t>(w));
    ASSERT_EQ(s_uint16.width, static_cast<std::uint16_t>(w));
    ASSERT_EQ(s_int32.width, static_cast<std::int32_t>(w));
    ASSERT_EQ(s_uint32.width, static_cast<std::uint32_t>(w));
    ASSERT_EQ(s_float.width, static_cast<float>(w));
    ASSERT_EQ(s_double.width, static_cast<double>(w));
    ASSERT_EQ(s_bool.height, static_cast<bool>(h));
    ASSERT_EQ(s_char.height, static_cast<char>(h));
    ASSERT_EQ(s_int8.height, static_cast<std::int8_t>(h));
    ASSERT_EQ(s_uint8.height, static_cast<std::uint8_t>(h));
    ASSERT_EQ(s_int16.height, static_cast<std::int16_t>(h));
    ASSERT_EQ(s_uint16.height, static_cast<std::uint16_t>(h));
    ASSERT_EQ(s_int32.height, static_cast<std::int32_t>(h));
    ASSERT_EQ(s_uint32.height, static_cast<std::uint32_t>(h));
    ASSERT_EQ(s_float.height, static_cast<float>(h));
    ASSERT_EQ(s_double.height, static_cast<double>(h));
  } {
    Size3<TypeParam> s(w, h, d);
    Size3<bool> s_bool(s);
    Size3<char> s_char(s);
    Size3<std::int8_t> s_int8(s);
    Size3<std::uint8_t> s_uint8(s);
    Size3<std::int16_t> s_int16(s);
    Size3<std::uint16_t> s_uint16(s);
    Size3<std::int32_t> s_int32(s);
    Size3<std::uint32_t> s_uint32(s);
    Size3<float> s_float(s);
    Size3<double> s_double(s);
    ASSERT_EQ(s_bool.width, static_cast<bool>(w));
    ASSERT_EQ(s_char.width, static_cast<char>(w));
    ASSERT_EQ(s_int8.width, static_cast<std::int8_t>(w));
    ASSERT_EQ(s_uint8.width, static_cast<std::uint8_t>(w));
    ASSERT_EQ(s_int16.width, static_cast<std::int16_t>(w));
    ASSERT_EQ(s_uint16.width, static_cast<std::uint16_t>(w));
    ASSERT_EQ(s_int32.width, static_cast<std::int32_t>(w));
    ASSERT_EQ(s_uint32.width, static_cast<std::uint32_t>(w));
    ASSERT_EQ(s_float.width, static_cast<float>(w));
    ASSERT_EQ(s_double.width, static_cast<double>(w));
    ASSERT_EQ(s_bool.height, static_cast<bool>(h));
    ASSERT_EQ(s_char.height, static_cast<char>(h));
    ASSERT_EQ(s_int8.height, static_cast<std::int8_t>(h));
    ASSERT_EQ(s_uint8.height, static_cast<std::uint8_t>(h));
    ASSERT_EQ(s_int16.height, static_cast<std::int16_t>(h));
    ASSERT_EQ(s_uint16.height, static_cast<std::uint16_t>(h));
    ASSERT_EQ(s_int32.height, static_cast<std::int32_t>(h));
    ASSERT_EQ(s_uint32.height, static_cast<std::uint32_t>(h));
    ASSERT_EQ(s_float.height, static_cast<float>(h));
    ASSERT_EQ(s_double.height, static_cast<double>(h));
    ASSERT_EQ(s_bool.depth, static_cast<bool>(d));
    ASSERT_EQ(s_char.depth, static_cast<char>(d));
    ASSERT_EQ(s_int8.depth, static_cast<std::int8_t>(d));
    ASSERT_EQ(s_uint8.depth, static_cast<std::uint8_t>(d));
    ASSERT_EQ(s_int16.depth, static_cast<std::int16_t>(d));
    ASSERT_EQ(s_uint16.depth, static_cast<std::uint16_t>(d));
    ASSERT_EQ(s_int32.depth, static_cast<std::int32_t>(d));
    ASSERT_EQ(s_uint32.depth, static_cast<std::uint32_t>(d));
    ASSERT_EQ(s_float.depth, static_cast<float>(d));
    ASSERT_EQ(s_double.depth, static_cast<double>(d));
  }
}

TYPED_TEST(SizeTest, SupportsArithmetic) {
  {
    Size2<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    Size2<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>());
    auto unary = s + operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) + operand.w);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) + operand.h);
  } {
    Size2<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    Size2<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>());
    auto unary = s - operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) - operand.w);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) - operand.h);
  } {
    Size2<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    Size2<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>());
    auto unary = s * operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) * operand.w);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) * operand.h);
  } {
    Size2<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    Size2<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>());
    auto unary = s / operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) / operand.w);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) / operand.h);
  } {
    Size3<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    Size3<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>());
    auto unary = s + operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) + operand.w);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) + operand.h);
    ASSERT_EQ(unary.d, Promote<TypeParam>(s.d) + operand.d);
  } {
    Size3<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    Size3<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>());
    auto unary = s - operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) - operand.w);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) - operand.h);
    ASSERT_EQ(unary.d, Promote<TypeParam>(s.d) - operand.d);
  } {
    Size3<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    Size3<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>());
    auto unary = s * operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) * operand.w);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) * operand.h);
    ASSERT_EQ(unary.d, Promote<TypeParam>(s.d) * operand.d);
  } {
    Size3<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    Size3<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>(),
                             math::Random<>().uniform<TypeParam>());
    auto unary = s / operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) / operand.w);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) / operand.h);
    ASSERT_EQ(unary.d, Promote<TypeParam>(s.d) / operand.d);
  }
}

TYPED_TEST(SizeTest, SupportsScalarArithmetic) {
  {
    Size2<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = s + operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) + operand);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) + operand);
  } {
    Size2<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = s - operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) - operand);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) - operand);
  } {
    Size2<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = s * operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) * operand);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) * operand);
  } {
    Size2<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = s / operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) / operand);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) / operand);
  } {
    Size2<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = operand * s;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) * operand);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) * operand);
  } {
    Size3<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = s + operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) + operand);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) + operand);
    ASSERT_EQ(unary.d, Promote<TypeParam>(s.d) + operand);
  } {
    Size3<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = s - operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) - operand);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) - operand);
    ASSERT_EQ(unary.d, Promote<TypeParam>(s.d) - operand);
  } {
    Size3<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = s * operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) * operand);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) * operand);
    ASSERT_EQ(unary.d, Promote<TypeParam>(s.d) * operand);
  } {
    Size3<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = s / operand;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) / operand);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) / operand);
    ASSERT_EQ(unary.d, Promote<TypeParam>(s.d) / operand);
  } {
    Size3<TypeParam> s(math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>(),
                       math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = operand * s;
    ASSERT_EQ(unary.w, Promote<TypeParam>(s.w) * operand);
    ASSERT_EQ(unary.h, Promote<TypeParam>(s.h) * operand);
    ASSERT_EQ(unary.d, Promote<TypeParam>(s.d) * operand);
  }
}

}  // namespace math
}  // namespace takram
