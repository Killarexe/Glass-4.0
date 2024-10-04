#ifndef OUTPUT_HPP
#define OUTPUT_HPP

// Dependencies 
#include "../typedef.hpp"
#include <iostream>

template <typename T>
GLASS_EXPORT std::ostream& operator<<(std::ostream& os, const gs::Vec2<T> vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

template <typename T>
GLASS_EXPORT std::ostream& operator<<(std::ostream& os, const gs::Vec3<T> vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

GLASS_EXPORT static std::ostream& operator<<(std::ostream& os, const gs::Color color) {
    os << "RGB(" << static_cast<int>(color.r) << ", " 
                 << static_cast<int>(color.g) << ", " 
                 << static_cast<int>(color.b) << ")";
    return os;
}

#endif
