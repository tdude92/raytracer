#include <cstdint>
#include <cmath>
#include <limits>
#include <algorithm>
#include "stb_image_write.h"
#include "vec3f.hpp"
#include "geometry.hpp"
#include "engine.hpp"

#define OBJECT_COLOUR_BLEND_FACTOR 0.75
#define RECURSION_LIMIT 4

// CLASS FRAMEBUFFER
// Constructors
FrameBuffer::FrameBuffer(int w, int h,
                         double fov,
                         double aspectRatio,
                         const Vec3f& pos,
                         const Vec3f& dir)
                        : width(w), height(h)
                        , horFOV(fov), vertFOV(fov * aspectRatio)
                        , pos(pos), dir(dir), frameBuffer(new uint8_t[w * h * 3]) {}

// Destructors
FrameBuffer::~FrameBuffer() {
    delete[] frameBuffer;
}

// Operators
FrameBuffer& FrameBuffer::operator=(const FrameBuffer& fb) {
    if (this != &fb) {
        delete[] frameBuffer;
        frameBuffer = new uint8_t[fb.width * fb.height * 3];
        std::copy(fb.frameBuffer, fb.frameBuffer + fb.width * fb.height * 3, frameBuffer);

        width = fb.width;
        height = fb.height;
        horFOV = fb.horFOV;
        vertFOV = fb.vertFOV;
        pos = fb.pos;
        dir = fb.dir;
    }
}

uint8_t* FrameBuffer::operator[](int i) {
    return frameBuffer + i/3;
}

// Getters
const uint8_t* FrameBuffer::getFrameBuffer() const {
    return frameBuffer;
}

int FrameBuffer::getWidth() const {
    return width;
}

int FrameBuffer::getHeight() const {
    return height;
}

double FrameBuffer::getHorFOV() const {
    return horFOV;
}

double FrameBuffer::getVertFOV() const {
    return vertFOV;
}

Vec3f FrameBuffer::getPos() const {
    return pos;
}

Vec3f FrameBuffer::getDir() const {
    return dir;
}


// STRUCT LIGHTSOURCE
LightSource::LightSource(const Vec3f& pos, const Vec3f& colour, double brightness)
                        : pos(pos), colour(colour), brightness(brightness) {}


// Functions
Vec3f rayTrace(const Ray& ray, const LightSource* target, const std::vector<LightSource>& lightSources, const std::vector<Shape*>& shapes, bool shadowRay = false) {
    Shape* closestIntersectionShape;
    Vec3f* closestIntersection = nullptr;
    double closestIntersectionDist = std::numeric_limits<double>::max();

    Vec3f* intersection;
    for (int i = 0; i < shapes.size(); ++i) {
        intersection = shapes[i]->getRayIntersection(ray);

        if (intersection && (*intersection - ray.origin).magnitude() < closestIntersectionDist) {
            closestIntersection = intersection;
            closestIntersectionShape = shapes[i];
            closestIntersectionDist = (*intersection - ray.origin).magnitude();
        } else {
            delete intersection;
        }
    }

    if (closestIntersection == nullptr) {
        // No intersections with any objects.
        if (target)
            // If ray is pointed towards a light source.
            return target->colour * target->brightness;
        else {
            // If ray is not directed towards a light source.
            return Vec3f(0, 0, 0);
        }
    } else {
        // There is an intersection with an object.
        if (shadowRay) {
            return Vec3f(0, 0, 0);
        } else if (closestIntersectionShape->diffuse) {
            // If the object has a diffuse surface.
            Vec3f sum;
            for (int i = 0; i < lightSources.size(); ++i)
                sum = sum + rayTrace(Ray(*closestIntersection, (lightSources[i].pos - *closestIntersection).direction()),
                                     &lightSources[i], lightSources, shapes, true);
            sum = sum * 255/sum.max();
            return (sum*(1 - OBJECT_COLOUR_BLEND_FACTOR) + closestIntersectionShape->colour*(OBJECT_COLOUR_BLEND_FACTOR));
        } else {
            // If the object has a reflective surface.

            // Compute colour from reflections.
            Vec3f normal = closestIntersectionShape->getNormal(ray, *closestIntersection);
            Vec3f reflection = rayTrace(Ray(*closestIntersection, ray.dir - normal*dot(ray.dir, normal)*2), nullptr, lightSources, shapes, false);
            
            // Compute colours from light sources.
            Vec3f sum;
            for (int i = 0; i < lightSources.size(); ++i)
                sum = sum + rayTrace(Ray(*closestIntersection, (lightSources[i].pos - *closestIntersection).direction()),
                                     &lightSources[i], lightSources, shapes, true);
            sum = sum * 255/sum.max();
            
            return closestIntersectionShape->colour*(OBJECT_COLOUR_BLEND_FACTOR) + sum*0.25*(1 - OBJECT_COLOUR_BLEND_FACTOR) + reflection*0.75*(1 - OBJECT_COLOUR_BLEND_FACTOR);
        }
    }
}

void computeFrameBuffer(FrameBuffer* frameBuffer, const std::vector<LightSource>& lightSources, const std::vector<Shape*>& shapes) {

}

void writeFrameBuffer(const FrameBuffer& frameBuffer) {
    stbi_write_jpg("output.jpg", frameBuffer.getWidth(),
                   frameBuffer.getHeight(), 3, frameBuffer.getFrameBuffer(), 100);
}

void freeShapeVector(std::vector<Shape*>* shapes) {
    for (int i = 0; i < shapes->size(); ++i)
        delete (*shapes)[i];
    shapes->resize(0);
}
