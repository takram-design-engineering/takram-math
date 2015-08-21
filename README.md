Math
====

A collection of C++ classes and functions to compute common mathematical operations and transformations that interoperate with common creative-coding libraries (WIP).

### Classes

- [`takram::math::Random`](src/takram/math/random.h)
- [`takram::math::Vector2`](src/takram/math/vector2.h)
- [`takram::math::Vector3`](src/takram/math/vector3.h)
- [`takram::math::Vector4`](src/takram/math/vector4.h)
- [`takram::math::Size2`](src/takram/math/size2.h)
- [`takram::math::Size3`](src/takram/math/size3.h)
- [`takram::math::Line2`](src/takram/math/line2.h)
- [`takram::math::Line3`](src/takram/math/line3.h)
- [`takram::math::Triangle2`](src/takram/math/triangle2.h)
- [`takram::math::Triangle3`](src/takram/math/triangle3.h)
- [`takram::math::Rect2`](src/takram/math/rectangle2.h)

## Examples

### Random

[Random](src/takram/math/random.h) is a wrapper of STL’s random number library designed for providing a simpler interface.

```cpp
#include <limits>

#include "takram/math/random.h"

takram::Random<> random;

// Uniform distribution ranges from 0 to the max int
random.uniform<int>(std::numeric_limits<int>::max());

// Gaussian (normal) distribution of mean 0 and standard deviation 1
random.gaussian<double>();
```

### Return Type Promotion

All types in this module promote the return type of arithmetic operators in the same way built-in arithmetic types do. Some member functions like `magnitude()` also promote the return type. The magnitude of a vector of integral type is promoted to double, but that of float remains float.

```cpp
#include "takram/math/vector.h"

takram::Vec2i veci;
takram::Vec2d vecd;
takram::Vec2f vecf;

veci + veci;  // Vector2<double>
veci + vecf;  // Vector2<double>
veci + vecd;  // Vector2<double>
vecf + vecf;  // Vector2<float>
vecf + vecd;  // Vector2<double>
```

### Implicit Type Conversions

[Vector](src/takram/math/vector.h), [Size](src/takram/math/size.h) and [Rect](src/takram/math/rect.h) are implicitly convertible to/from corresponding types of OpenCV, openFrameworks and Cinder.

| | OpenCV | openFrameworks | Cinder   
|---------|------------|----------------|----------
| [Vector2](src/takram/math/vector2.h) | cv::Point | ofVec2f | ci::Vec2 
| [Vector3](src/takram/math/vector3.h) | cv::Point3 | ofVec3f | ci::Vec3 
| [Vector4](src/takram/math/vector4.h) | | ofVec4f | ci::Vec4 
| [Size2](src/takram/math/size2.h) | cv::Size   | |          
| [Size3](src/takram/math/size3.h) | | |          
| [Rect2](src/takram/math/rectangle2.h) | cv::Rect | ofRectangle | ci::Rect 

## Setup Guide

Run "setup.sh" inside "script" directory to initialize submodules and build dependant libraries.

### Submodules

- [Google Testing Framework](https://chromium.googlesource.com/external/googletest)

## License

MIT License

Copyright (C) 2015 takram design engineering

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
