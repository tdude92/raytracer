#include <cmath>
#include "vec3f.hpp"

// CLASS Vec3f
// Constructors
Vec3f::Vec3f(): x(0), y(0), z(0) {}
Vec3f::Vec3f(double x, double y, double z): x(x), y(y), z(z) {}


// Operators
Vec3f& Vec3f::operator=(const Vec3f& vec) {
    if (this != &vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    }
}

Vec3f Vec3f::operator+(const Vec3f& vec) const {
    double new_x = x + vec.x;
    double new_y = y + vec.y;
    double new_z = z + vec.z;
    return Vec3f(new_x, new_y, new_z);
}

Vec3f Vec3f::operator-() const {
    double new_x = -x;
    double new_y = -y;
    double new_z = -z;
    return Vec3f(new_x, new_y, new_z);
}

Vec3f Vec3f::operator-(const Vec3f& vec) const {
    return *this + (-vec);
}

Vec3f Vec3f::operator*(const Vec3f& vec) const {
    // Element-wise multiplication
    double new_x = x * vec.x;
    double new_y = y * vec.y;
    double new_z = z * vec.z;
    return Vec3f(new_x, new_y, new_z);
}

Vec3f Vec3f::operator*(const double& scalar) const {
    // Scalar multiplication
    double new_x = x * scalar;
    double new_y = y * scalar;
    double new_z = z * scalar;
    return Vec3f(new_x, new_y, new_z);
}

Vec3f Vec3f::operator/(const Vec3f& vec) const {
    // Element-wise division
    double new_x = x / vec.x;
    double new_y = y / vec.y;
    double new_z = z / vec.z;
    return Vec3f(new_x, new_y, new_z);
}

Vec3f Vec3f::operator/(const double& scalar) const {
    // Scalar division
    double new_x = x / scalar;
    double new_y = y / scalar;
    double new_z = z / scalar;
    return Vec3f(new_x, new_y, new_z);
}


// Member Functions
double Vec3f::magnitude() const {
    return sqrt(x*x + y*y + z*z);
}

Vec3f Vec3f::direction() const {
    return *this / magnitude();
}
