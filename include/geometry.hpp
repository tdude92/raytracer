#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "vec3f.hpp"

class Shape {
    public:
        const Vec3f colour;
        const bool diffuse, opaque;
        const double refractionIndex;
    protected:
        Vec3f& pos();
        Vec3f& dir();
    private:
        Vec3f pos, dir;
};

class Sphere : public Shape {};

class Cube : public Shape {};

class Triangle : public Shape {
    // For triangle meshes

};

#endif