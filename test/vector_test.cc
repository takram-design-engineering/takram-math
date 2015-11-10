//
//  vector_test.cc
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
#include "takram/math/vector.h"

namespace takram {
namespace math {

template <class T>
class VectorTest : public ::testing::Test {};

using Types = ::testing::Types<
  std::int16_t,
  std::uint16_t,
  std::int32_t,
  std::uint32_t,
  float,
  double
>;
TYPED_TEST_CASE(VectorTest, Types);

TEST(VectorTest, Concepts) {
  ASSERT_TRUE(std::is_default_constructible<Vec2d>::value);
  ASSERT_TRUE(std::is_copy_constructible<Vec2d>::value);
  ASSERT_TRUE(std::is_copy_assignable<Vec2d>::value);
  ASSERT_TRUE(std::is_move_constructible<Vec2d>::value);
  ASSERT_TRUE(std::is_move_assignable<Vec2d>::value);
  ASSERT_FALSE(std::has_virtual_destructor<Vec2d>::value);
}

TYPED_TEST(VectorTest, DefaultConstructible) {
  {
    Vec2<TypeParam> v;
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
  } {
    Vec3<TypeParam> v;
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
  } {
    Vec4<TypeParam> v;
    ASSERT_EQ(v.x, TypeParam());
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
    ASSERT_EQ(v.w, TypeParam());
  }
}

TYPED_TEST(VectorTest, ConstructibleWithValue) {
  const auto value = math::Random<>().uniform<TypeParam>();
  {
    Vec2<TypeParam> v(value);
    ASSERT_EQ(v.x, value);
    ASSERT_EQ(v.y, value);
  } {
    Vec3<TypeParam> v(value);
    ASSERT_EQ(v.x, value);
    ASSERT_EQ(v.y, value);
    ASSERT_EQ(v.z, value);
  } {
    Vec4<TypeParam> v(value);
    ASSERT_EQ(v.x, value);
    ASSERT_EQ(v.y, value);
    ASSERT_EQ(v.z, value);
    ASSERT_EQ(v.w, value);
  }
}

TYPED_TEST(VectorTest, ConstructibleWithValues) {
  const auto x = math::Random<>().uniform<TypeParam>();
  const auto y = math::Random<>().uniform<TypeParam>();
  const auto z = math::Random<>().uniform<TypeParam>();
  const auto w = math::Random<>().uniform<TypeParam>();
  {
    Vec2<TypeParam> v(x, y);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vec3<TypeParam> v(x, y, z);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vec4<TypeParam> v(x, y, z, w);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  }
}

TYPED_TEST(VectorTest, ConstructibleWithTuple) {
  const auto x = math::Random<>().uniform<TypeParam>();
  const auto y = math::Random<>().uniform<TypeParam>();
  const auto z = math::Random<>().uniform<TypeParam>();
  const auto w = math::Random<>().uniform<TypeParam>();
  {
    Vec2<TypeParam> v(std::make_tuple(x, y));
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vec3<TypeParam> v(std::make_tuple(x, y, z));
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vec4<TypeParam> v(std::make_tuple(x, y, z, w));
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  }
}

TYPED_TEST(VectorTest, ConstructibleWithInitializerList) {
  const auto x = math::Random<>().uniform<TypeParam>();
  const auto y = math::Random<>().uniform<TypeParam>();
  const auto z = math::Random<>().uniform<TypeParam>();
  const auto w = math::Random<>().uniform<TypeParam>();
  {
    Vec2<TypeParam> v{x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
  } {
    Vec2<TypeParam> v{x, y, TypeParam()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vec3<TypeParam> v{x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
  } {
    Vec3<TypeParam> v{x, y, z, TypeParam()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vec4<TypeParam> v{x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
    ASSERT_EQ(v.w, TypeParam());
  } {
    Vec4<TypeParam> v{x, y, z, w, TypeParam()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  }
}

TYPED_TEST(VectorTest, CopyConstructible) {
  const auto x = math::Random<>().uniform<TypeParam>();
  const auto y = math::Random<>().uniform<TypeParam>();
  const auto z = math::Random<>().uniform<TypeParam>();
  const auto w = math::Random<>().uniform<TypeParam>();
  {
    Vec2<TypeParam> v1(x, y);
    Vec2<TypeParam> v2(v1);
    ASSERT_EQ(v1, v2);
  } {
    Vec3<TypeParam> v1(x, y, z);
    Vec3<TypeParam> v2(v1);
    ASSERT_EQ(v1, v2);
  } {
    Vec4<TypeParam> v1(x, y, z, w);
    Vec4<TypeParam> v2(v1);
    ASSERT_EQ(v1, v2);
  }
}

TYPED_TEST(VectorTest, CopyAssignable) {
  const auto x = math::Random<>().uniform<TypeParam>();
  const auto y = math::Random<>().uniform<TypeParam>();
  const auto z = math::Random<>().uniform<TypeParam>();
  const auto w = math::Random<>().uniform<TypeParam>();
  {
    Vec2<TypeParam> v1(x, y);
    Vec2<TypeParam> v2;
    v2 = v1;
    ASSERT_EQ(v1, v2);
  } {
    Vec3<TypeParam> v1(x, y, z);
    Vec3<TypeParam> v2;
    v2 = v1;
    ASSERT_EQ(v1, v2);
  } {
    Vec4<TypeParam> v1(x, y, z, w);
    Vec4<TypeParam> v2;
    v2 = v1;
    ASSERT_EQ(v1, v2);
  }
}

TYPED_TEST(VectorTest, TupleAssignable) {
  const auto x = math::Random<>().uniform<TypeParam>();
  const auto y = math::Random<>().uniform<TypeParam>();
  const auto z = math::Random<>().uniform<TypeParam>();
  const auto w = math::Random<>().uniform<TypeParam>();
  {
    Vec2<TypeParam> v;
    v = std::make_tuple(x, y);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vec3<TypeParam> v;
    v = std::make_tuple(x, y, z);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vec4<TypeParam> v;
    v = std::make_tuple(x, y, z, w);
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  }
}

TYPED_TEST(VectorTest, InitializerListAssignable) {
  const auto x = math::Random<>().uniform<TypeParam>();
  const auto y = math::Random<>().uniform<TypeParam>();
  const auto z = math::Random<>().uniform<TypeParam>();
  const auto w = math::Random<>().uniform<TypeParam>();
  {
    Vec2<TypeParam> v;
    v = {x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
  } {
    Vec2<TypeParam> v;
    v = {x, y, TypeParam()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
  } {
    Vec3<TypeParam> v;
    v = {x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
  } {
    Vec3<TypeParam> v;
    v = {x, y, z, TypeParam()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
  } {
    Vec4<TypeParam> v;
    v = {x};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, TypeParam());
    ASSERT_EQ(v.z, TypeParam());
    ASSERT_EQ(v.w, TypeParam());
  } {
    Vec4<TypeParam> v;
    v = {x, y, z, w, TypeParam()};
    ASSERT_EQ(v.x, x);
    ASSERT_EQ(v.y, y);
    ASSERT_EQ(v.z, z);
    ASSERT_EQ(v.w, w);
  }
}

TYPED_TEST(VectorTest, ImplicitlyConvertibleFromOtherTypes) {
  const auto x = math::Random<>().uniform<TypeParam>();
  const auto y = math::Random<>().uniform<TypeParam>();
  const auto z = math::Random<>().uniform<TypeParam>();
  const auto w = math::Random<>().uniform<TypeParam>();
  {
    Vec2<TypeParam> v(x, y);
    Vec2<std::int8_t> v_int8(v);
    Vec2<std::uint8_t> v_uint8(v);
    Vec2<std::int16_t> v_int16(v);
    Vec2<std::uint16_t> v_uint16(v);
    Vec2<std::int32_t> v_int32(v);
    Vec2<std::uint32_t> v_uint32(v);
    Vec2<float> v_float(v);
    Vec2<double> v_double(v);
    ASSERT_EQ(v_int8.x, static_cast<std::int8_t>(x));
    ASSERT_EQ(v_uint8.x, static_cast<std::uint8_t>(x));
    ASSERT_EQ(v_int16.x, static_cast<std::int16_t>(x));
    ASSERT_EQ(v_uint16.x, static_cast<std::uint16_t>(x));
    ASSERT_EQ(v_int32.x, static_cast<std::int32_t>(x));
    ASSERT_EQ(v_uint32.x, static_cast<std::uint32_t>(x));
    ASSERT_EQ(v_float.x, static_cast<float>(x));
    ASSERT_EQ(v_double.x, static_cast<double>(x));
    ASSERT_EQ(v_int8.y, static_cast<std::int8_t>(y));
    ASSERT_EQ(v_uint8.y, static_cast<std::uint8_t>(y));
    ASSERT_EQ(v_int16.y, static_cast<std::int16_t>(y));
    ASSERT_EQ(v_uint16.y, static_cast<std::uint16_t>(y));
    ASSERT_EQ(v_int32.y, static_cast<std::int32_t>(y));
    ASSERT_EQ(v_uint32.y, static_cast<std::uint32_t>(y));
    ASSERT_EQ(v_float.y, static_cast<float>(y));
    ASSERT_EQ(v_double.y, static_cast<double>(y));
  } {
    Vec3<TypeParam> v(x, y, z);
    Vec3<std::int8_t> v_int8(v);
    Vec3<std::uint8_t> v_uint8(v);
    Vec3<std::int16_t> v_int16(v);
    Vec3<std::uint16_t> v_uint16(v);
    Vec3<std::int32_t> v_int32(v);
    Vec3<std::uint32_t> v_uint32(v);
    Vec3<float> v_float(v);
    Vec3<double> v_double(v);
    ASSERT_EQ(v_int8.x, static_cast<std::int8_t>(x));
    ASSERT_EQ(v_uint8.x, static_cast<std::uint8_t>(x));
    ASSERT_EQ(v_int16.x, static_cast<std::int16_t>(x));
    ASSERT_EQ(v_uint16.x, static_cast<std::uint16_t>(x));
    ASSERT_EQ(v_int32.x, static_cast<std::int32_t>(x));
    ASSERT_EQ(v_uint32.x, static_cast<std::uint32_t>(x));
    ASSERT_EQ(v_float.x, static_cast<float>(x));
    ASSERT_EQ(v_double.x, static_cast<double>(x));
    ASSERT_EQ(v_int8.y, static_cast<std::int8_t>(y));
    ASSERT_EQ(v_uint8.y, static_cast<std::uint8_t>(y));
    ASSERT_EQ(v_int16.y, static_cast<std::int16_t>(y));
    ASSERT_EQ(v_uint16.y, static_cast<std::uint16_t>(y));
    ASSERT_EQ(v_int32.y, static_cast<std::int32_t>(y));
    ASSERT_EQ(v_uint32.y, static_cast<std::uint32_t>(y));
    ASSERT_EQ(v_float.y, static_cast<float>(y));
    ASSERT_EQ(v_double.y, static_cast<double>(y));
    ASSERT_EQ(v_int8.z, static_cast<std::int8_t>(z));
    ASSERT_EQ(v_uint8.z, static_cast<std::uint8_t>(z));
    ASSERT_EQ(v_int16.z, static_cast<std::int16_t>(z));
    ASSERT_EQ(v_uint16.z, static_cast<std::uint16_t>(z));
    ASSERT_EQ(v_int32.z, static_cast<std::int32_t>(z));
    ASSERT_EQ(v_uint32.z, static_cast<std::uint32_t>(z));
    ASSERT_EQ(v_float.z, static_cast<float>(z));
    ASSERT_EQ(v_double.z, static_cast<double>(z));
  } {
    Vec4<TypeParam> v(x, y, z, w);
    Vec4<std::int8_t> v_int8(v);
    Vec4<std::uint8_t> v_uint8(v);
    Vec4<std::int16_t> v_int16(v);
    Vec4<std::uint16_t> v_uint16(v);
    Vec4<std::int32_t> v_int32(v);
    Vec4<std::uint32_t> v_uint32(v);
    Vec4<float> v_float(v);
    Vec4<double> v_double(v);
    ASSERT_EQ(v_int8.x, static_cast<std::int8_t>(x));
    ASSERT_EQ(v_uint8.x, static_cast<std::uint8_t>(x));
    ASSERT_EQ(v_int16.x, static_cast<std::int16_t>(x));
    ASSERT_EQ(v_uint16.x, static_cast<std::uint16_t>(x));
    ASSERT_EQ(v_int32.x, static_cast<std::int32_t>(x));
    ASSERT_EQ(v_uint32.x, static_cast<std::uint32_t>(x));
    ASSERT_EQ(v_float.x, static_cast<float>(x));
    ASSERT_EQ(v_double.x, static_cast<double>(x));
    ASSERT_EQ(v_int8.y, static_cast<std::int8_t>(y));
    ASSERT_EQ(v_uint8.y, static_cast<std::uint8_t>(y));
    ASSERT_EQ(v_int16.y, static_cast<std::int16_t>(y));
    ASSERT_EQ(v_uint16.y, static_cast<std::uint16_t>(y));
    ASSERT_EQ(v_int32.y, static_cast<std::int32_t>(y));
    ASSERT_EQ(v_uint32.y, static_cast<std::uint32_t>(y));
    ASSERT_EQ(v_float.y, static_cast<float>(y));
    ASSERT_EQ(v_double.y, static_cast<double>(y));
    ASSERT_EQ(v_int8.z, static_cast<std::int8_t>(z));
    ASSERT_EQ(v_uint8.z, static_cast<std::uint8_t>(z));
    ASSERT_EQ(v_int16.z, static_cast<std::int16_t>(z));
    ASSERT_EQ(v_uint16.z, static_cast<std::uint16_t>(z));
    ASSERT_EQ(v_int32.z, static_cast<std::int32_t>(z));
    ASSERT_EQ(v_uint32.z, static_cast<std::uint32_t>(z));
    ASSERT_EQ(v_float.z, static_cast<float>(z));
    ASSERT_EQ(v_double.z, static_cast<double>(z));
    ASSERT_EQ(v_int8.w, static_cast<std::int8_t>(w));
    ASSERT_EQ(v_uint8.w, static_cast<std::uint8_t>(w));
    ASSERT_EQ(v_int16.w, static_cast<std::int16_t>(w));
    ASSERT_EQ(v_uint16.w, static_cast<std::uint16_t>(w));
    ASSERT_EQ(v_int32.w, static_cast<std::int32_t>(w));
    ASSERT_EQ(v_uint32.w, static_cast<std::uint32_t>(w));
    ASSERT_EQ(v_float.w, static_cast<float>(w));
    ASSERT_EQ(v_double.w, static_cast<double>(w));
  }
}

TYPED_TEST(VectorTest, SupportsArithmetic) {
  {
    Vec2<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec2<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand.y);
  } {
    Vec2<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec2<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand.y);
  } {
    Vec2<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec2<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand.y);
  } {
    Vec2<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec2<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand.y);
  } {
    Vec3<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec3<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) + operand.z);
  } {
    Vec3<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec3<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) - operand.z);
  } {
    Vec3<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec3<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand.z);
  } {
    Vec3<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec3<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) / operand.z);
  } {
    Vec4<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec4<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) + operand.z);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) + operand.w);
  } {
    Vec4<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec4<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) - operand.z);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) - operand.w);
  } {
    Vec4<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec4<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand.z);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) * operand.w);
  } {
    Vec4<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    Vec4<TypeParam> operand(math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>(),
                            math::Random<>().uniform<TypeParam>());
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand.x);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand.y);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) / operand.z);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) / operand.w);
  }
}

TYPED_TEST(VectorTest, SupportsScalarArithmetic) {
  {
    Vec2<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand);
  } {
    Vec2<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand);
  } {
    Vec2<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
  } {
    Vec2<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand);
  } {
    Vec2<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = operand * v;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
  } {
    Vec3<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) + operand);
  } {
    Vec3<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) - operand);
  } {
    Vec3<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand);
  } {
    Vec3<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) / operand);
  } {
    Vec3<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = operand * v;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand);
  } {
    Vec4<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v + operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) + operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) + operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) + operand);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) + operand);
  } {
    Vec4<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v - operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) - operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) - operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) - operand);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) - operand);
  } {
    Vec4<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v * operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) * operand);
  } {
    Vec4<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = v / operand;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) / operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) / operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) / operand);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) / operand);
  } {
    Vec4<TypeParam> v(math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>(),
                      math::Random<>().uniform<TypeParam>());
    TypeParam operand = math::Random<>().uniform<TypeParam>();
    auto unary = operand * v;
    ASSERT_EQ(unary.x, Promote<TypeParam>(v.x) * operand);
    ASSERT_EQ(unary.y, Promote<TypeParam>(v.y) * operand);
    ASSERT_EQ(unary.z, Promote<TypeParam>(v.z) * operand);
    ASSERT_EQ(unary.w, Promote<TypeParam>(v.w) * operand);
  }
}

}  // namespace math
}  // namespace takram
