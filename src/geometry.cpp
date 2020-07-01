#include <iostream>
#include <cmath>
#include "geometry.hpp"

// STRUCT RAY
// Constructors
Ray::Ray(const Vec3f& origin, const Vec3f& dir)
          : origin(origin), dir(dir) {}


// CLASS SHAPE
// Constructors
Shape::Shape(const Vec3f& colour, bool diffuse, bool opaque, double refractiveIndex)
            : colour(colour), diffuse(diffuse)
            , opaque(opaque), refractiveIndex(refractiveIndex) {}


// CLASS SPHERE
// Constructors
Sphere::Sphere(const Vec3f& center, double radius, const Vec3f& colour
              , bool diffuse, bool opaque, double refractiveIndex)
              : center(center), radius(radius)
              , Shape(colour, diffuse, opaque, refractiveIndex) {}

// Member functions
Vec3f* Sphere::getRayIntersection(Ray ray) const {
    double discriminant = pow(dot(ray.dir, ray.origin - center), 2) - (pow((ray.origin - center).magnitude(), 2) - radius*radius);
    double d = -dot(ray.dir, ray.origin - center);

    if (discriminant < 0) {
        return nullptr;
    } else if (discriminant == 0) {
        return new Vec3f(ray.origin + ray.dir*d);
    } else {
        Vec3f* intersection = new Vec3f();
        double root1 = sqrt(discriminant), root2 = -sqrt(discriminant);

        if (d + root1 < 0 && d + root2 < 0) {
            // if d < 0, then the point of intersection is in the opposite direction of the ray from the origin.
            // (this is because we represent a ray in the form: x = ray.origin + ray.dir*d, where d is an element
            //  of naturals with zero)
            return nullptr;
        } else if (d + root1 < 0) {
            d += root2;
        } else if (d + root2 < 0) {
            d += root1;
        } else {
            d += fmin(root1, root2);
        }

        *intersection = ray.origin + ray.dir*d;
        return intersection;
    }
}


// CLASS TRIANGLE
// Constructors
Triangle::Triangle(Vec3f* vertices, const Vec3f& colour,
                   bool diffuse, bool opaque, double refractiveIndex)
                  : v(vertices), Shape(colour, diffuse, opaque, refractiveIndex)
                  , normal(cross((v[1] - v[0]), (v[2] - v[0]))) {}

// Member functions
Vec3f* Triangle::getRayIntersection(Ray ray) {
    
}
