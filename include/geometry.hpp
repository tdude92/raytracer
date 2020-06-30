#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "vec3f.hpp"

struct Ray {
    Ray(const Vec3f& origin, const Vec3f& dir);

    Vec3f origin;
    Vec3f dir;

    // Important note: origin is the point a ray is cast from.
};


class Shape {
    public:
        Shape(const Vec3f& colour, bool diffuse, bool opaque, double refractiveIndex);

        const Vec3f colour;
        const bool diffuse, opaque;
        const double refractiveIndex;
};


class Sphere : public Shape {
    public:
        Sphere(const Vec3f& colour,
               const Vec3f& center,
               double radius,
               bool diffuse = true,
               bool opaque = true,
               double refractiveIndex = 1.5);
        
        Vec3f* getRayIntersection(Ray ray) const;
    private:
        Vec3f center;
        double radius;
};


// TODO: Add cubes.


class Triangle : public Shape {
    // For triangle meshes
    public:
        Vec3f getRayIntersection(Ray ray);
};

#endif
