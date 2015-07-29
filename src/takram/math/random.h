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

#include <atomic>
#include <cassert>
#include <cstdlib>
#include <limits>
#include <memory>
#include <mutex>
#include <random>

#include "takram/math/promotion.h"

namespace takram {
namespace math {

#pragma mark -

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

  // Shared instance
  static Random& shared();

  // Random generation
  void seed(Type value);
  void randomize();
  Type next();

  // Random engine
  Engine& engine() { return engine_; }
  const Engine& engine() const { return engine_; }

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
  static void delete_shared();

 private:
  Engine engine_;
  static std::atomic<Random *> shared_;
  static std::mutex shared_mutex_;
  static bool shared_deleted_;

 private:
  friend int atexit(void (*)(void));
};

template <class Engine>
std::atomic<Random<Engine> *> Random<Engine>::shared_;
template <class Engine>
std::mutex Random<Engine>::shared_mutex_;
template <class Engine>
bool Random<Engine>::shared_deleted_;

#pragma mark -

template <class Engine>
inline Random<Engine>::Random() : engine_(std::random_device()()) {}

template <class Engine>
inline Random<Engine>::Random(Type seed) : engine_(seed) {}

#pragma mark Shared instance

template <class Engine>
inline Random<Engine>& Random<Engine>::shared() {
  auto shared = shared_.load(std::memory_order_consume);
  if (!shared) {
    std::lock_guard<std::mutex> lock(shared_mutex_);
    shared = shared_.load(std::memory_order_consume);
    if (!shared) {
      assert(!shared_deleted_);
      shared = new Random;
      shared_.store(shared, std::memory_order_release);
      std::atexit(&delete_shared);
    }
  }
  return *shared;
}

template <class Engine>
inline void Random<Engine>::delete_shared() {
  std::lock_guard<std::mutex> lock(shared_mutex_);
  delete shared_.exchange(nullptr);
  shared_deleted_ = true;
}

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

using math::Random;

}  // namespace takram

#endif  // TAKRAM_MATH_RANDOM_H_
