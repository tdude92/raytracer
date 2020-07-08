#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
#include "vec3f.hpp"

struct Ray {
    Ray();
    Ray(const Vec3f& origin, const Vec3f& dir);

    Vec3f origin;
    Vec3f dir;

    // Important note: origin is the point a ray is cast from.
};


class Shape {
    public:
        Shape(const Vec3f& colour);

        const Vec3f colour;

        virtual Vec3f* getRayIntersection(const Ray& ray) const = 0;
        virtual Vec3f  getNormal(const Ray& ray, const Vec3f& p) const = 0; // Ray origin point used to calculate direction of normal.
        virtual Vec3f  getPos() const = 0;
};


class LightSource {
    public:
        const Vec3f pos, colour;
        const double intensity;

        // Constructors
        LightSource(const Vec3f& pos, const Vec3f& colour, double intensity);

        virtual Vec3f getColour(const Vec3f& origin, const std::vector<LightSource*>& lightSources, const std::vector<Shape*>& shapes, int samples) const = 0;
};


class PointLightSource : public LightSource {
    public:
        PointLightSource(const Vec3f& pos, const Vec3f& colour, double intensity);
        Vec3f getColour(const Vec3f& origin, const std::vector<LightSource*>& lightSources, const std::vector<Shape*>& shapes, int samples) const;
};

class DirectionalLightSource : public LightSource {
    public:
        DirectionalLightSource(const Vec3f& pos, const Vec3f& colour, const Vec3f& dir, double radius, double intensity);
        Vec3f getColour(const Vec3f& origin, const std::vector<LightSource*>& lightSources, const std::vector<Shape*>& shapes, int samples) const;
    private:
        Vec3f center, dir; // aka the normal
        double radius;
};


class Sphere : public Shape {
    public:
        Sphere(const Vec3f& center,
               double radius,
               const Vec3f& colour);
        
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
                 const Vec3f& colour);
        
        ~Triangle();
        
        Vec3f* getRayIntersection(const Ray& ray) const;
        Vec3f  getNormal(const Ray& ray, const Vec3f& p) const;
        Vec3f  getPos() const;
    private:
        Vec3f* v; // Array of vertices
};

#endif
