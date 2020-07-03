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

        virtual Vec3f* getRayIntersection(const Ray& ray) const = 0;
        virtual Vec3f  getNormal(const Ray& ray, const Vec3f& p) const = 0; // Ray origin point used to calculate direction of normal.
};


class Sphere : public Shape {
    public:
        Sphere(const Vec3f& center,
               double radius,
               const Vec3f& colour,
               bool diffuse = true,
               bool opaque = true,
               double refractiveIndex = 1.5);
        
        Vec3f* getRayIntersection(const Ray& ray) const;
        Vec3f  getNormal(const Ray& ray, const Vec3f& p) const; // Get the normal vector of a point on the surface of a sphere.
    private:
        Vec3f center;
        double radius;
};


// TODO: Add cubes.


class Triangle : public Shape {
    // For triangle meshes
    public:
        Triangle(Vec3f* vertices, // Array of vertices.
                 const Vec3f& colour,
                 bool diffuse = true,
                 bool opaque = true,
                 double refractiveIndex = 1.5);
        
        ~Triangle();
        
        Vec3f* getRayIntersection(const Ray& ray) const;
        Vec3f  getNormal(const Ray& ray, const Vec3f& p) const;
    private:
        Vec3f* v; // Array of vertices
};

#endif
