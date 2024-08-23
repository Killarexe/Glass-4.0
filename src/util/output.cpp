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

// Explicit template instantiations
template std::ostream& operator<<(std::ostream&, gs::Vec2<int>);
template std::ostream& operator<<(std::ostream&, gs::Vec2<unsigned>);
template std::ostream& operator<<(std::ostream&, gs::Vec2<float>);
template std::ostream& operator<<(std::ostream&, gs::Vec2<double>);
template std::ostream& operator<<(std::ostream&, gs::Vec3<int>);
template std::ostream& operator<<(std::ostream&, gs::Vec3<unsigned>);
template std::ostream& operator<<(std::ostream&, gs::Vec3<float>);
template std::ostream& operator<<(std::ostream&, gs::Vec3<double>);
