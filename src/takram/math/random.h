//
//  takram/math/random.h
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
#ifndef TAKRAM_MATH_RANDOM_H_
#define TAKRAM_MATH_RANDOM_H_

#include <cassert>
#include <limits>
#include <mutex>
#include <random>

#include "takram/math/promotion.h"

namespace takram {
namespace math {

template <class Engine = std::mt19937>
class Random final {
 public:
  using Type = typename Engine::result_type;

 public:
  Random();
  explicit Random(Type seed);

  // Copy semantics
  Random(const Random& other) = default;
  Random& operator=(const Random& other) = default;

  // Random generation
  void seed(Type value);
  void randomize();
  Type next();
  template <class Distribution>
  Type next(Distribution *distribution);

  // Distribution
  template <class T>
  T uniform();
  template <class T>
  T uniform(T max);
  template <class T>
  T uniform(T min, T max);
  template <class T>
  T gaussian();
  template <class T>
  T gaussian(Promote<T> mean, Promote<T> stddev);

 private:
  Engine engine_;
};

#pragma mark -

Random random;

// Uniform distribution ranges from 0 to the max int
random.uniform<int>(std::numeric_limits<int>::max());

// Gaussian (normal) distribution of mean 0 and standard deviation 1
random.gaussian<double>();

template <class Engine>
inline Random<Engine>::Random() : engine_(std::random_device()()) {}

template <class Engine>
inline Random<Engine>::Random(Type seed) : engine_(seed) {}

#pragma mark Random generation

template <class Engine>
inline void Random<Engine>::seed(Type value) {
  engine_.seed(value);
}

template <class Engine>
inline void Random<Engine>::randomize() {
  engine_.seed(std::random_device()());
}

template <class Engine>
inline typename Random<Engine>::Type Random<Engine>::next() {
  return engine_();
}

template <class Engine>
template <class Distribution>
inline typename Random<Engine>::Type Random<Engine>::next(
    Distribution *distribution) {
  assert(distribution);
  return (*distribution)(engine_);
}

#pragma mark Distribution

template <class Engine>
template <class T>
inline T Random<Engine>::uniform() {
  return uniform<T>(std::numeric_limits<T>::min(),
                    std::numeric_limits<T>::max());
}

template <class Engine>
template <class T>
inline T Random<Engine>::uniform(T max) {
  return uniform<T>(T(), max);
}

template <class Engine>
template <class T>
inline T Random<Engine>::uniform(T min, T max) {
  using distribution = typename std::conditional<
      std::is_integral<T>::value,
      std::uniform_int_distribution<T>,
      std::uniform_real_distribution<T>>::type;
  return distribution(min, max)(engine_);
}

template <class Engine>
template <class T>
inline T Random<Engine>::gaussian() {
  return std::normal_distribution<Promote<T>>()(engine_);
}

template <class Engine>
template <class T>
inline T Random<Engine>::gaussian(Promote<T> mean, Promote<T> stddev) {
  return std::normal_distribution<Promote<T>>(mean, stddev)(engine_);
}

}  // namespace math
}  // namespace takram

#endif  // TAKRAM_MATH_RANDOM_H_
