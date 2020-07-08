#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "vec3f.hpp"

struct Ray {
    Ray(const Vec3f& origin, const Vec3f& dir);

    Vec3f origin;
    Vec3f dir;

    // Important note: origin is the point a ray is cast from.
};


struct LightSource {
    LightSource(const Vec3f& pos, const Vec3f& colour, double brightness);
    const Vec3f pos, colour;
    double brightness; // Factor used to control brightness of a light source.
};


class Shape {
    public:
        Shape(const Vec3f& colour, bool diffuse);

        const Vec3f colour;
        const bool diffuse;

        virtual Vec3f* getRayIntersection(const Ray& ray) const = 0;
        virtual Vec3f  getNormal(const Ray& ray, const Vec3f& p) const = 0; // Ray origin point used to calculate direction of normal.
        virtual Vec3f  getPos() const = 0;
};


class Sphere : public Shape {
    public:
        Sphere(const Vec3f& center,
               double radius,
               const Vec3f& colour,
               bool diffuse = true);
        
        Vec3f* getRayIntersection(const Ray& ray) const;
        Vec3f  getNormal(const Ray& ray, const Vec3f& p) const; // Get the normal vector of a point on the surface of a sphere.
        Vec3f  getPos() const;
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
                 bool diffuse = true);
        
        ~Triangle();
        
        Vec3f* getRayIntersection(const Ray& ray) const;
        Vec3f  getNormal(const Ray& ray, const Vec3f& p) const;
        Vec3f  getPos() const;
    private:
        Vec3f* v; // Array of vertices
};

#endif
