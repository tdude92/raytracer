#ifndef VEC3F_HPP
#define VEC3F_HPP

#define DEBUG(x) std::cout << x << std::endl
#define PRINTV(a) std::cout << "(" << a.x << ", " << a.y << ", " << a.z << ")" << std::endl

class Vec3f {
    public:
        double x, y, z;

        // Constructors
        Vec3f();
        Vec3f(const Vec3f& vec);
        Vec3f(double x, double y, double z);

        // Operators
        Vec3f& operator=(const Vec3f& vec);                  // Copy
        Vec3f  operator+(const Vec3f& vec)      const;       // Element-wise addition
        Vec3f  operator-()                      const;       // Negation
        Vec3f  operator-(const Vec3f& vec)      const;       // Element-wise subtraction
        Vec3f  operator*(const Vec3f& vec)      const;       // Element-wise multiplication
        Vec3f  operator*(const double& scalar)  const;       // Scalar multiplication
        Vec3f  operator/(const Vec3f& vec)      const;       // Element-wise division
        Vec3f  operator/(const double& scalar)  const;       // Scalar Division


        // Public Member Functions
        double max() const;
        double magnitude() const;
        Vec3f  direction() const;
};

// Other vector operations.
Vec3f  cross(const Vec3f& v1, const Vec3f& v2);
double dot(const Vec3f& v1, const Vec3f& v2);
double distance(const Vec3f& v1, const Vec3f& v2);

#endif
