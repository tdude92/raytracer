#define _USE_MATH_DEFINES

#include <cstdint>
#include <cmath>
#include <limits>
#include <algorithm>
#include <cstdint>
#include <vector>
#include "stb/stb_image_write.h"
#include "vec3f.hpp"
#include "geometry.hpp"
#include "engine.hpp"

#define RAY_SAMPLES 100
#define OBJECT_COLOUR_BLEND_FACTOR 0.25

// CLASS FRAMEBUFFER
// Constructors
FrameBuffer::FrameBuffer(int w, int h,
                         double fov)
                        : width(w), height(h)
                        , horFOV(fov * M_PI/180), vertFOV(2*atan((h/w)*tan(horFOV/2)))
                        , frameBuffer(new uint8_t[w * h * 3])
                        , depth(w/(2*tan(horFOV/2)))
                        , p0(Vec3f(-w/2 + 0.5, -h/2 + 0.5, depth)) {
                        }

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
        depth = fb.depth;
        p0 = fb.p0;
    }
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

double FrameBuffer::getDepth() const {
    return depth;
}

Vec3f FrameBuffer::getP0() const {
    return p0;
}


// Functions
Vec3f rayTrace(const Ray& ray, const LightSource* target, const std::vector<LightSource*>& lightSources, const std::vector<Shape*>& shapes, bool bounceRay) {
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

    if (closestIntersection == nullptr && target != nullptr) {
        // No intersections with any objects and
        // ray is pointed towards a light source.
        double distanceMultiplier = target->intensity/(4*M_PI*(ray.origin - target->pos).magnitude());
        return target->colour * distanceMultiplier;
    } else if (closestIntersection != nullptr && !bounceRay) {
        // There is an intersection between a primary ray and a point on a shape.
        Vec3f sum = Vec3f();
        for (int i = 0; i < lightSources.size(); ++i)
            sum = sum + lightSources[i]->getColour(*closestIntersection, lightSources, shapes, RAY_SAMPLES);
            
        sum = sum / lightSources.size();
        if (sum.magnitude() > 0)
            return (sum*(1 - OBJECT_COLOUR_BLEND_FACTOR) + closestIntersectionShape->colour*(OBJECT_COLOUR_BLEND_FACTOR));
    } else if (closestIntersection != nullptr) {
        return closestIntersectionShape->colour*0.05;
    }
    
    // Or ray is not targetting a light source and has no intersections.
    return Vec3f(5, 5, 22);
}

void computeFrameBuffer(FrameBuffer* frameBuffer, const std::vector<LightSource*>& lightSources, const std::vector<Shape*>& shapes) {
    Vec3f p0 = frameBuffer->getP0();
    for (int i = 0; i < frameBuffer->getWidth()*frameBuffer->getHeight()*3; i += 3) {
        int y = i / 3 / frameBuffer->getWidth();
        int x = i / 3 % frameBuffer->getWidth();
        
        Vec3f colour = rayTrace(Ray(Vec3f(0, 0, 0), (p0 + Vec3f(x, y, 0)).direction()), nullptr, lightSources, shapes);

        frameBuffer->frameBuffer[i]     = (uint8_t)(unsigned int)colour.x;
        frameBuffer->frameBuffer[i + 1] = (uint8_t)(unsigned int)colour.y;
        frameBuffer->frameBuffer[i + 2] = (uint8_t)(unsigned int)colour.z;
    }
}

void writeFrameBuffer(const FrameBuffer& frameBuffer) {
    stbi_write_jpg("output.jpg", frameBuffer.getWidth(),
                   frameBuffer.getHeight(), 3, frameBuffer.frameBuffer, 100);
}

void freeShapeVector(std::vector<Shape*>* shapes) {
    for (int i = 0; i < shapes->size(); ++i)
        delete (*shapes)[i];
    shapes->resize(0);
}

void freeLightSourceVector(std::vector<LightSource*>* lightSources) {
    for (int i = 0; i < lightSources->size(); ++i)
        delete (*lightSources)[i];
    lightSources->resize(0);
}
