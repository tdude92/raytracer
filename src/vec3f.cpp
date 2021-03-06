#include <cmath>
#include "vec3f.hpp"

// CLASS Vec3f
// Constructors
Vec3f::Vec3f()
            : x(0), y(0), z(0) {}

Vec3f::Vec3f(const Vec3f& vec)
            : x(vec.x), y(vec.y), z(vec.z) {}

Vec3f::Vec3f(double x, double y, double z)
            : x(x), y(y), z(z) {}


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
double Vec3f::max() const {
    return fmax(fmax(x, y), z);
}

double Vec3f::magnitude() const {
    return sqrt(x*x + y*y + z*z);
}

Vec3f Vec3f::direction() const {
    // Returns a unit vector in the direction of this.
    return *this / magnitude();
}


// OTHER VECTOR OPERATIONS

Vec3f cross(const Vec3f& v1, const Vec3f& v2) {
    return Vec3f(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

double dot(const Vec3f& v1, const Vec3f& v2) {
    // Dot product of two 3D vectors.
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

double distance(const Vec3f& v1, const Vec3f& v2) {
    // Euclidean distance between two points (represented by vectors.)
    return (v1 - v2).magnitude();
}
