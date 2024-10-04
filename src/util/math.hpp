#ifndef MATH_HPP
#define MATH_HPP

// Dependencies 
#include "../typedef.hpp"
#include <cmath>

// Dot product for Vec2
template <typename Type>
GLASS_EXPORT Type operator*(gs::Vec2<Type> p1, gs::Vec2<Type> p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

// Dot product for Vec3
template <typename Type>
Type operator*(gs::Vec3<Type> p1, gs::Vec3<Type> p2) {
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

namespace gs {
  namespace util {
  /// Constant for pi. 
  GLASS_EXPORT static const float PI = 3.141592653589793;
  /// Constant for tau or 2pi. 
  GLASS_EXPORT static const float TAU = 6.28318530717959;
  // Clamp function
  template <typename Type>
    GLASS_EXPORT Type clamp(Type value, Type min, Type max) {
        return std::max(min, std::min(value, max));
    }

    // Clamp function with pointer
    template <typename Type>
    GLASS_EXPORT void clamp(Type* value, Type min, Type max) {
        *value = std::max(min, std::min(*value, max));
    }

    // Distance function for Vec2
    template <typename Type>
    GLASS_EXPORT Type distance(gs::Vec2<Type> p1, gs::Vec2<Type> p2) {
        return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
    }

    // Distance function for Vec3
    template <typename Type>
    GLASS_EXPORT Type distance(gs::Vec3<Type> p1, gs::Vec3<Type> p2) {
        return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z));
    }

    // Approach function
    template <typename Type>
    GLASS_EXPORT Type approach(Type base, Type destination, Type percentage) {
        return base + (destination - base) * percentage;
    }

    // Approach function with pointer
    template <typename Type>
    GLASS_EXPORT void approach(Type* base, Type destination, Type percentage) {
        *base += (*base - destination) * percentage;
    }

    // Sign function
    template <typename Type>
    GLASS_EXPORT Type sign(Type value) {
        return (Type(0) < value) - (value < Type(0));
    }

    // InBound function
    template <typename Type>
    GLASS_EXPORT bool inBound(Type value, Type upperBound, Type lowerBound) {
        return (lowerBound <= value) && (value <= upperBound);
    }

    // Mod function
    // FIXME: WHY THE FUCK THIS FUNCTION HAS NON INTEGER PARAMETERS!
    template <typename Type>
    GLASS_EXPORT Type mod(Type value, Type divisor) {
        return ((int)value % (int)divisor + (int)divisor) % (int)divisor;
    }

    // ToDegrees function
    template <typename Type>
    GLASS_EXPORT Type toDegrees(Type radians) {
        return radians * (180.0 / PI);
    }

    // ToRadians function
    template <typename Type>
    GLASS_EXPORT Type toRadians(Type degrees) {
        return degrees * (PI / 180.0);
    }

    // AngleBetween function
    template <typename Type>
    GLASS_EXPORT Type angleBetween(gs::Vec2<Type> p1, gs::Vec2<Type> p2, bool inDegrees) {
        Type angle = std::atan2(p2.y - p1.y, p2.x - p1.x);
        return inDegrees ? toDegrees(angle) : angle;
    }

    // PolarToCartesian function
    template <typename Type>
    GLASS_EXPORT gs::Vec2<Type> polarToCartesian(gs::Vec2<Type> polarCoordinate, bool inDegrees) {
        Type angle = inDegrees ? toRadians(polarCoordinate.y) : polarCoordinate.y;
        return gs::Vec2<Type>(polarCoordinate.x * std::cos(angle), polarCoordinate.x * std::sin(angle));
    }

    // CartesianToPolar function
    template <typename Type>
    GLASS_EXPORT gs::Vec2<Type> cartesianToPolar(gs::Vec2<Type> cartesianCoordinate, bool inDegrees) {
        Type radius = std::sqrt(cartesianCoordinate.x * cartesianCoordinate.x + cartesianCoordinate.y * cartesianCoordinate.y);
        Type angle = std::atan2(cartesianCoordinate.y, cartesianCoordinate.x);
        return gs::Vec2<Type>(radius, inDegrees ? toDegrees(angle) : angle);
    }
  }
}

#endif
