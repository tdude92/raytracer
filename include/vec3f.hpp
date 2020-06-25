#ifndef VEC3F_HPP
#define VEC3F_HPP

class Vec3f {
    public:
        double &x, &y, &z;

        // Constructors
        Vec3f();
        Vec3f(double x, double y, double z);

        // Destructors
        ~Vec3f();

        // Operators
        Vec3f& operator=(const Vec3f& vec);
        Vec3f  operator+(const Vec3f& vec) const;       // Element-wise addition
        Vec3f  operator-() const;                       // Negation
        Vec3f  operator-(const Vec3f& vec) const;       // Element-wise subtraction
        Vec3f  operator*(const Vec3f& vec) const;       // Element-wise multiplication
        Vec3f  operator*(const double& scalar) const;   // Scalar multiplication
        Vec3f  operator/(const Vec3f& vec) const;       // Element-wise division
        Vec3f  operator/(const double& scalar) const;   // Scalar Division

        // Public Member Functions
        double magnitude();
        Vec3f direction();

    private:
        double* val;
};

#endif