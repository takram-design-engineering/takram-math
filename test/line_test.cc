//
//  line_test.cc
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

#include <cstdint>
#include <random>
#include <type_traits>

#include "gtest/gtest.h"

#include "takram/math/line.h"
#include "takram/math/random.h"
#include "takram/math/vector.h"

namespace takram {
namespace math {

template <class T>
class LineTest : public ::testing::Test {};

using Types = ::testing::Types<
  std::int8_t,
  std::uint8_t,
  std::int16_t,
  std::uint16_t,
  std::int32_t,
  std::uint32_t,
  float,
  double
>;
TYPED_TEST_CASE(LineTest, Types);

TEST(LineTest, Concepts) {
  ASSERT_TRUE(std::is_default_constructible<Line2d>::value);
  ASSERT_TRUE(std::is_copy_constructible<Line2d>::value);
  ASSERT_TRUE(std::is_copy_assignable<Line2d>::value);
  ASSERT_TRUE(std::is_move_constructible<Line2d>::value);
  ASSERT_TRUE(std::is_move_assignable<Line2d>::value);
  ASSERT_FALSE(std::has_virtual_destructor<Line2d>::value);
}

TYPED_TEST(LineTest, DefaultConstructible) {
  {
    Line2<TypeParam> l;
    ASSERT_EQ(l.x1, TypeParam());
    ASSERT_EQ(l.y1, TypeParam());
  } {
    Line3<TypeParam> l;
    ASSERT_EQ(l.x1, TypeParam());
    ASSERT_EQ(l.y1, TypeParam());
    ASSERT_EQ(l.z1, TypeParam());
  }
}

TYPED_TEST(LineTest, ConstructibleWithValues) {
  const auto x1 = math::Random<>().uniform<TypeParam>();
  const auto y1 = math::Random<>().uniform<TypeParam>();
  const auto z1 = math::Random<>().uniform<TypeParam>();
  const auto x2 = math::Random<>().uniform<TypeParam>();
  const auto y2 = math::Random<>().uniform<TypeParam>();
  const auto z2 = math::Random<>().uniform<TypeParam>();
  {
    Line2<TypeParam> l(x1, y1, x2, y2);
    ASSERT_EQ(l.x1, x1);
    ASSERT_EQ(l.y1, y1);
    ASSERT_EQ(l.x2, x2);
    ASSERT_EQ(l.y2, y2);
  } {
    Line3<TypeParam> l(x1, y1, z1, x2, y2, z2);
    ASSERT_EQ(l.x1, x1);
    ASSERT_EQ(l.y1, y1);
    ASSERT_EQ(l.z1, z1);
    ASSERT_EQ(l.x2, x2);
    ASSERT_EQ(l.y2, y2);
    ASSERT_EQ(l.z2, z2);
  }
}

TYPED_TEST(LineTest, ConstructibleWithInitializerList) {
  const auto x1 = math::Random<>().uniform<TypeParam>();
  const auto y1 = math::Random<>().uniform<TypeParam>();
  const auto z1 = math::Random<>().uniform<TypeParam>();
  const auto x2 = math::Random<>().uniform<TypeParam>();
  const auto y2 = math::Random<>().uniform<TypeParam>();
  const auto z2 = math::Random<>().uniform<TypeParam>();
  {
    Line2<TypeParam> l{x1};
    ASSERT_EQ(l.x1, x1);
    ASSERT_EQ(l.y1, TypeParam());
    ASSERT_EQ(l.x2, TypeParam());
    ASSERT_EQ(l.y2, TypeParam());
  } {
    Line2<TypeParam> l{x1, y1, x2, y2, TypeParam()};
    ASSERT_EQ(l.x1, x1);
    ASSERT_EQ(l.y1, y1);
    ASSERT_EQ(l.x2, x2);
    ASSERT_EQ(l.y2, y2);
  } {
    Vec2<TypeParam> a{x1, y1};
    Line2<TypeParam> l{a};
    ASSERT_EQ(l.a, a);
    ASSERT_EQ(l.b, Vec2<TypeParam>());
  } {
    Vec2<TypeParam> a{x1, y1};
    Vec2<TypeParam> b{x2, y2};
    Line2<TypeParam> l{a, b, Vec2<TypeParam>()};
    ASSERT_EQ(l.a, a);
    ASSERT_EQ(l.b, b);
  } {
    Line3<TypeParam> l{x1};
    ASSERT_EQ(l.x1, x1);
    ASSERT_EQ(l.y1, TypeParam());
    ASSERT_EQ(l.z1, TypeParam());
    ASSERT_EQ(l.x2, TypeParam());
    ASSERT_EQ(l.y2, TypeParam());
    ASSERT_EQ(l.z2, TypeParam());
  } {
    Line3<TypeParam> l{x1, y1, z1, x2, y2, z2, TypeParam()};
    ASSERT_EQ(l.x1, x1);
    ASSERT_EQ(l.y1, y1);
    ASSERT_EQ(l.z1, z1);
    ASSERT_EQ(l.x2, x2);
    ASSERT_EQ(l.y2, y2);
    ASSERT_EQ(l.z2, z2);
  } {
    Vec3<TypeParam> a{x1, y1, z1};
    Line3<TypeParam> l{a};
    ASSERT_EQ(l.a, a);
    ASSERT_EQ(l.b, Vec3<TypeParam>());
  } {
    Vec3<TypeParam> a{x1, y1, z1};
    Vec3<TypeParam> b{x2, y2, z2};
    Line3<TypeParam> l{a, b, Vec3<TypeParam>()};
    ASSERT_EQ(l.a, a);
    ASSERT_EQ(l.b, b);
  }
}

TYPED_TEST(LineTest, CopyConstructible) {
  const auto x1 = math::Random<>().uniform<TypeParam>();
  const auto y1 = math::Random<>().uniform<TypeParam>();
  const auto z1 = math::Random<>().uniform<TypeParam>();
  const auto x2 = math::Random<>().uniform<TypeParam>();
  const auto y2 = math::Random<>().uniform<TypeParam>();
  const auto z2 = math::Random<>().uniform<TypeParam>();
  {
    Line2<TypeParam> l1(x1, y1, x2, y2);
    Line2<TypeParam> l2(l1);
    ASSERT_EQ(l1, l2);
  } {
    Line3<TypeParam> l1(x1, y1, z1, x2, y2, z2);
    Line3<TypeParam> l2(l1);
    ASSERT_EQ(l1, l2);
  }
}

TYPED_TEST(LineTest, CopyAssignable) {
  const auto x1 = math::Random<>().uniform<TypeParam>();
  const auto y1 = math::Random<>().uniform<TypeParam>();
  const auto z1 = math::Random<>().uniform<TypeParam>();
  const auto x2 = math::Random<>().uniform<TypeParam>();
  const auto y2 = math::Random<>().uniform<TypeParam>();
  const auto z2 = math::Random<>().uniform<TypeParam>();
  {
    Line2<TypeParam> l1(x1, y1, x2, y2);
    Line2<TypeParam> l2;
    l2 = l1;
    ASSERT_EQ(l1, l2);
  } {
    Line3<TypeParam> l1(x1, y1, z1, x2, y2, z2);
    Line3<TypeParam> l2;
    l2 = l1;
    ASSERT_EQ(l1, l2);
  }
}

TYPED_TEST(LineTest, InitializerListAssignable) {
  const auto x1 = math::Random<>().uniform<TypeParam>();
  const auto y1 = math::Random<>().uniform<TypeParam>();
  const auto z1 = math::Random<>().uniform<TypeParam>();
  const auto x2 = math::Random<>().uniform<TypeParam>();
  const auto y2 = math::Random<>().uniform<TypeParam>();
  const auto z2 = math::Random<>().uniform<TypeParam>();
  {
    Line2<TypeParam> l;
    l = {x1};
    ASSERT_EQ(l.x1, x1);
    ASSERT_EQ(l.y1, TypeParam());
    ASSERT_EQ(l.x2, TypeParam());
    ASSERT_EQ(l.y2, TypeParam());
  } {
    Line2<TypeParam> l;
    l = {x1, y1, x2, y2, TypeParam()};
    ASSERT_EQ(l.x1, x1);
    ASSERT_EQ(l.y1, y1);
    ASSERT_EQ(l.x2, x2);
    ASSERT_EQ(l.y2, y2);
  } {
    Vec2<TypeParam> a{x1, y1};
    Line2<TypeParam> l;
    l = {a};
    ASSERT_EQ(l.a, a);
    ASSERT_EQ(l.b, Vec2<TypeParam>());
  } {
    Vec2<TypeParam> a{x1, y1};
    Vec2<TypeParam> b{x2, y2};
    Line2<TypeParam> l;
    l = {a, b, Vec2<TypeParam>()};
    ASSERT_EQ(l.a, a);
    ASSERT_EQ(l.b, b);
  } {
    Line3<TypeParam> l;
    l = {x1};
    ASSERT_EQ(l.x1, x1);
    ASSERT_EQ(l.y1, TypeParam());
    ASSERT_EQ(l.z1, TypeParam());
    ASSERT_EQ(l.x2, TypeParam());
    ASSERT_EQ(l.y2, TypeParam());
    ASSERT_EQ(l.z2, TypeParam());
  } {
    Line3<TypeParam> l;
    l = {x1, y1, z1, x2, y2, z2, TypeParam()};
    ASSERT_EQ(l.x1, x1);
    ASSERT_EQ(l.y1, y1);
    ASSERT_EQ(l.z1, z1);
    ASSERT_EQ(l.x2, x2);
    ASSERT_EQ(l.y2, y2);
    ASSERT_EQ(l.z2, z2);
  } {
    Vec3<TypeParam> a{x1, y1, z1};
    Line3<TypeParam> l;
    l = {a};
    ASSERT_EQ(l.a, a);
    ASSERT_EQ(l.b, Vec3<TypeParam>());
  } {
    Vec3<TypeParam> a{x1, y1, z1};
    Vec3<TypeParam> b{x2, y2, z2};
    Line3<TypeParam> l;
    l = {a, b, Vec3<TypeParam>()};
    ASSERT_EQ(l.a, a);
    ASSERT_EQ(l.b, b);
  }
}

TYPED_TEST(LineTest, ImplicitlyConvertibleFromOtherTypes) {
  const auto x1 = math::Random<>().uniform<TypeParam>();
  const auto y1 = math::Random<>().uniform<TypeParam>();
  const auto z1 = math::Random<>().uniform<TypeParam>();
  const auto x2 = math::Random<>().uniform<TypeParam>();
  const auto y2 = math::Random<>().uniform<TypeParam>();
  const auto z2 = math::Random<>().uniform<TypeParam>();
  {
    Vec2<TypeParam> a(x1, y1);
    Vec2<TypeParam> b(x2, y2);
    Line2<TypeParam> l(a, b);
    Line2<std::int8_t> l_int8(l);
    Line2<std::uint8_t> l_uint8(l);
    Line2<std::int16_t> l_int16(l);
    Line2<std::uint16_t> l_uint16(l);
    Line2<std::int32_t> l_int32(l);
    Line2<std::uint32_t> l_uint32(l);
    Line2<float> l_float(l);
    Line2<double> l_double(l);
    ASSERT_EQ(l_int8.a, Vec2<std::int8_t>(a));
    ASSERT_EQ(l_uint8.a, Vec2<std::uint8_t>(a));
    ASSERT_EQ(l_int16.a, Vec2<std::int16_t>(a));
    ASSERT_EQ(l_uint16.a, Vec2<std::uint16_t>(a));
    ASSERT_EQ(l_int32.a, Vec2<std::int32_t>(a));
    ASSERT_EQ(l_uint32.a, Vec2<std::uint32_t>(a));
    ASSERT_EQ(l_float.a, Vec2<float>(a));
    ASSERT_EQ(l_double.a, Vec2<double>(a));
    ASSERT_EQ(l_int8.b, Vec2<std::int8_t>(b));
    ASSERT_EQ(l_uint8.b, Vec2<std::uint8_t>(b));
    ASSERT_EQ(l_int16.b, Vec2<std::int16_t>(b));
    ASSERT_EQ(l_uint16.b, Vec2<std::uint16_t>(b));
    ASSERT_EQ(l_int32.b, Vec2<std::int32_t>(b));
    ASSERT_EQ(l_uint32.b, Vec2<std::uint32_t>(b));
    ASSERT_EQ(l_float.b, Vec2<float>(b));
    ASSERT_EQ(l_double.b, Vec2<double>(b));
  } {
    Vec3<TypeParam> a(x1, y1, z1);
    Vec3<TypeParam> b(x2, y2, z2);
    Line3<TypeParam> l(a, b);
    Line3<std::int8_t> l_int8(l);
    Line3<std::uint8_t> l_uint8(l);
    Line3<std::int16_t> l_int16(l);
    Line3<std::uint16_t> l_uint16(l);
    Line3<std::int32_t> l_int32(l);
    Line3<std::uint32_t> l_uint32(l);
    Line3<float> l_float(l);
    Line3<double> l_double(l);
    ASSERT_EQ(l_int8.a, Vec3<std::int8_t>(a));
    ASSERT_EQ(l_uint8.a, Vec3<std::uint8_t>(a));
    ASSERT_EQ(l_int16.a, Vec3<std::int16_t>(a));
    ASSERT_EQ(l_uint16.a, Vec3<std::uint16_t>(a));
    ASSERT_EQ(l_int32.a, Vec3<std::int32_t>(a));
    ASSERT_EQ(l_uint32.a, Vec3<std::uint32_t>(a));
    ASSERT_EQ(l_float.a, Vec3<float>(a));
    ASSERT_EQ(l_double.a, Vec3<double>(a));
    ASSERT_EQ(l_int8.b, Vec3<std::int8_t>(b));
    ASSERT_EQ(l_uint8.b, Vec3<std::uint8_t>(b));
    ASSERT_EQ(l_int16.b, Vec3<std::int16_t>(b));
    ASSERT_EQ(l_uint16.b, Vec3<std::uint16_t>(b));
    ASSERT_EQ(l_int32.b, Vec3<std::int32_t>(b));
    ASSERT_EQ(l_uint32.b, Vec3<std::uint32_t>(b));
    ASSERT_EQ(l_float.b, Vec3<float>(b));
    ASSERT_EQ(l_double.b, Vec3<double>(b));
  }
}

}  // namespace math
}  // namespace takram
