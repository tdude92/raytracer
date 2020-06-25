#include <cmath>
#include "vec3f.hpp"

// CLASS Vec3f
// Constructors
Vec3f::Vec3f()
: val(new double[3]()) 
, x(val[0]), y(val[1]), z(val[2]) {}

Vec3f::Vec3f(double x, double y, double z)
: val(new double[3]{x, y, z}) 
, x(val[0]), y(val[1]), z(val[2]) {}


// Destructors
Vec3f::~Vec3f() {
    delete[] val;
}


// Operators
Vec3f& Vec3f::operator=(const Vec3f& vec) {
    if (this != &vec) {
        val[0] = vec.val[0];
        val[1] = vec.val[1];
        val[2] = vec.val[2];
        return *this;
    }
}

Vec3f Vec3f::operator+(const Vec3f& vec) const {
    double x = val[0] + vec.val[0];
    double y = val[0] + vec.val[0];
    double z = val[0] + vec.val[0];
    return Vec3f(x, y, z);
}

Vec3f Vec3f::operator-() const {
    double x = -val[0];
    double y = -val[1];
    double z = -val[2];
    return Vec3f(x, y ,z);
}

Vec3f Vec3f::operator-(const Vec3f& vec) const {
    return *this + (-vec);
}

Vec3f Vec3f::operator*(const Vec3f& vec) const {
    // Element-wise multiplication
    double x = val[0] * vec.val[0];
    double y = val[0] * vec.val[0];
    double z = val[0] * vec.val[0];
    return Vec3f(x, y, z);
}

Vec3f Vec3f::operator*(const double& scalar) const {
    // Scalar multiplication
    double x = val[0] * scalar;
    double y = val[0] * scalar;
    double z = val[0] * scalar;
    return Vec3f(x, y, z);
}

Vec3f Vec3f::operator/(const Vec3f& vec) const {
    // Element-wise division
    double x = val[0] / vec.val[0];
    double y = val[0] / vec.val[0];
    double z = val[0] / vec.val[0];
    return Vec3f(x, y, z);
}

Vec3f Vec3f::operator/(const double& scalar) const {
    // Scalar division
    double x = val[0] / scalar;
    double y = val[0] / scalar;
    double z = val[0] / scalar;
    return Vec3f(x, y, z);
}

// Member Functions
double Vec3f::magnitude() {
    return sqrt(x*x + y*y + z*z);
}

Vec3f Vec3f::direction() {
    return *this / magnitude();
}
