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

template GLASS_EXPORT std::ostream& operator<<(std::ostream&, gs::Vec2<int>);
template GLASS_EXPORT std::ostream& operator<<(std::ostream&, gs::Vec2<unsigned>);
template GLASS_EXPORT std::ostream& operator<<(std::ostream&, gs::Vec2<float>);
template GLASS_EXPORT std::ostream& operator<<(std::ostream&, gs::Vec2<double>);
template GLASS_EXPORT std::ostream& operator<<(std::ostream&, gs::Vec3<int>);
template GLASS_EXPORT std::ostream& operator<<(std::ostream&, gs::Vec3<unsigned>);
template GLASS_EXPORT std::ostream& operator<<(std::ostream&, gs::Vec3<float>);
template GLASS_EXPORT std::ostream& operator<<(std::ostream&, gs::Vec3<double>);
