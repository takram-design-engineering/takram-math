//
//  math/rect_test.cc
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
#include <type_traits>

#include "gtest/gtest.h"

#include "takram/math/rect.h"

namespace takram {
namespace math {

template <class T>
class RectTest : public ::testing::Test {
 protected:
  void SetUp() override {
    engine_ = std::default_random_engine(random_device_());
  }

  T Random() {
    if (std::is_integral<T>::value) {
      std::uniform_int_distribution<T> distribution(
          std::numeric_limits<T>::min(),
          std::numeric_limits<T>::max());
      return distribution(engine_);
    } else if (std::is_floating_point<T>::value) {
      std::uniform_real_distribution<T> distribution(
          std::numeric_limits<T>::min(),
          std::numeric_limits<T>::max());
      return distribution(engine_);
    }
  }

 private:
  std::random_device random_device_;
  std::default_random_engine engine_;
};

using Types = ::testing::Types<
  bool,
  char,
  std::int8_t,
  std::uint8_t,
  std::int16_t,
  std::uint16_t,
  std::int32_t,
  std::uint32_t,
  float,
  double
>;
TYPED_TEST_CASE(RectTest, Types);

TYPED_TEST(RectTest, DefaultConstructible) {
  Rect<TypeParam> r;
  ASSERT_EQ(r.x, TypeParam());
  ASSERT_EQ(r.y, TypeParam());
  ASSERT_EQ(r.width, TypeParam());
  ASSERT_EQ(r.height, TypeParam());
}

TYPED_TEST(RectTest, ConstructibleWithValues) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto width = this->Random();
  const auto height = this->Random();

  Rect<TypeParam> r(x, y, width, height);
  ASSERT_EQ(r.x, x);
  ASSERT_EQ(r.y, y);
  ASSERT_EQ(r.width, width);
  ASSERT_EQ(r.height, height);
}

TYPED_TEST(RectTest, ConstructibleWithOriginAndSize) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto width = this->Random();
  const auto height = this->Random();

  Rect<TypeParam> r(Vector2<TypeParam>(x, y), Size2<TypeParam>(width, height));
  ASSERT_EQ(r.x, x);
  ASSERT_EQ(r.y, y);
  ASSERT_EQ(r.width, width);
  ASSERT_EQ(r.height, height);
}

TYPED_TEST(RectTest, ConstructibleWithValuesAndSize) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto width = this->Random();
  const auto height = this->Random();

  Rect<TypeParam> r(x, y, Size2<TypeParam>(width, height));
  ASSERT_EQ(r.x, x);
  ASSERT_EQ(r.y, y);
  ASSERT_EQ(r.width, width);
  ASSERT_EQ(r.height, height);
}

TYPED_TEST(RectTest, ConstructibleWithOriginAndValues) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto width = this->Random();
  const auto height = this->Random();

  Rect<TypeParam> r(Vector2<TypeParam>(x, y), width, height);
  ASSERT_EQ(r.x, x);
  ASSERT_EQ(r.y, y);
  ASSERT_EQ(r.width, width);
  ASSERT_EQ(r.height, height);
}

TYPED_TEST(RectTest, CopyConstructible) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto width = this->Random();
  const auto height = this->Random();

  Rect<TypeParam> r1(x, y, width, height);
  Rect<TypeParam> r2(r1);
  ASSERT_EQ(r1, r2);
}

TYPED_TEST(RectTest, CopyAssignable) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto width = this->Random();
  const auto height = this->Random();

  Rect<TypeParam> r1(x, y, width, height);
  Rect<TypeParam> r2;
  r2 = r1;
  ASSERT_EQ(r1, r2);
}

TYPED_TEST(RectTest, ImplicitlyConvertibleFromOtherTypes) {
  const auto x = this->Random();
  const auto y = this->Random();
  const auto width = this->Random();
  const auto height = this->Random();

  Rect<TypeParam> r(x, y, width, height);
  Rect<bool> r_bool(r);
  Rect<char> r_char(r);
  Rect<std::int8_t> r_int8(r);
  Rect<std::uint8_t> r_uint8(r);
  Rect<std::int16_t> r_int16(r);
  Rect<std::uint16_t> r_uint16(r);
  Rect<std::int32_t> r_int32(r);
  Rect<std::uint32_t> r_uint32(r);
  Rect<float> r_float(r);
  Rect<double> r_double(r);
  ASSERT_EQ(r_bool.x, static_cast<bool>(x));
  ASSERT_EQ(r_char.x, static_cast<char>(x));
  ASSERT_EQ(r_int8.x, static_cast<std::int8_t>(x));
  ASSERT_EQ(r_uint8.x, static_cast<std::uint8_t>(x));
  ASSERT_EQ(r_int16.x, static_cast<std::int16_t>(x));
  ASSERT_EQ(r_uint16.x, static_cast<std::uint16_t>(x));
  ASSERT_EQ(r_int32.x, static_cast<std::int32_t>(x));
  ASSERT_EQ(r_uint32.x, static_cast<std::uint32_t>(x));
  ASSERT_EQ(r_float.x, static_cast<float>(x));
  ASSERT_EQ(r_double.x, static_cast<double>(x));
  ASSERT_EQ(r_bool.y, static_cast<bool>(y));
  ASSERT_EQ(r_char.y, static_cast<char>(y));
  ASSERT_EQ(r_int8.y, static_cast<std::int8_t>(y));
  ASSERT_EQ(r_uint8.y, static_cast<std::uint8_t>(y));
  ASSERT_EQ(r_int16.y, static_cast<std::int16_t>(y));
  ASSERT_EQ(r_uint16.y, static_cast<std::uint16_t>(y));
  ASSERT_EQ(r_int32.y, static_cast<std::int32_t>(y));
  ASSERT_EQ(r_uint32.y, static_cast<std::uint32_t>(y));
  ASSERT_EQ(r_float.y, static_cast<float>(y));
  ASSERT_EQ(r_double.y, static_cast<double>(y));
  ASSERT_EQ(r_bool.width, static_cast<bool>(width));
  ASSERT_EQ(r_char.width, static_cast<char>(width));
  ASSERT_EQ(r_int8.width, static_cast<std::int8_t>(width));
  ASSERT_EQ(r_uint8.width, static_cast<std::uint8_t>(width));
  ASSERT_EQ(r_int16.width, static_cast<std::int16_t>(width));
  ASSERT_EQ(r_uint16.width, static_cast<std::uint16_t>(width));
  ASSERT_EQ(r_int32.width, static_cast<std::int32_t>(width));
  ASSERT_EQ(r_uint32.width, static_cast<std::uint32_t>(width));
  ASSERT_EQ(r_float.width, static_cast<float>(width));
  ASSERT_EQ(r_double.width, static_cast<double>(width));
  ASSERT_EQ(r_bool.height, static_cast<bool>(height));
  ASSERT_EQ(r_char.height, static_cast<char>(height));
  ASSERT_EQ(r_int8.height, static_cast<std::int8_t>(height));
  ASSERT_EQ(r_uint8.height, static_cast<std::uint8_t>(height));
  ASSERT_EQ(r_int16.height, static_cast<std::int16_t>(height));
  ASSERT_EQ(r_uint16.height, static_cast<std::uint16_t>(height));
  ASSERT_EQ(r_int32.height, static_cast<std::int32_t>(height));
  ASSERT_EQ(r_uint32.height, static_cast<std::uint32_t>(height));
  ASSERT_EQ(r_float.height, static_cast<float>(height));
  ASSERT_EQ(r_double.height, static_cast<double>(height));
}

}  // namespace math
}  // namespace takram
