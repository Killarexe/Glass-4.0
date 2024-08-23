#include "output.hpp"
#include <iostream>

template <typename Type>
std::ostream& operator<<(std::ostream& os, gs::Vec2<Type> vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

template <typename Type>
std::ostream& operator<<(std::ostream& os, gs::Vec3<Type> vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, gs::Color color) {
    os << "RGB(" << static_cast<int>(color.r) << ", " 
                 << static_cast<int>(color.g) << ", " 
                 << static_cast<int>(color.b) << ")";
    return os;
}
