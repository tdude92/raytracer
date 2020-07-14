#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <cstdint>
#include <vector>
#include "vec3f.hpp"
#include "geometry.hpp"

class FrameBuffer {
    public:
        // Constructors
        FrameBuffer(int w, int h,
                    double fov = 90); // 180 < fov < 0
        // Destructors
        ~FrameBuffer();

        // Operators
        FrameBuffer& operator=(const FrameBuffer& fb);
        
        // Getters
        int getWidth() const;
        int getHeight() const;
        double getHorFOV() const;
        double getVertFOV() const;
        double getDepth() const;
        Vec3f getP0() const;

        uint8_t* frameBuffer;       // Stores pixel information.
    private:
        int width, height;          // In pixels.
        double horFOV, vertFOV;     // Expressed in radians. horFOV:vertFOV = aspect ratio.
        double depth;               // Distance between camera origin and frame.
        Vec3f p0;                   // Top left corner of frame.
};


Vec3f rayTrace(const Ray& ray, const LightSource* target, const std::vector<LightSource*>& lightSources, const std::vector<Shape*>& shapes, bool bounceRay = false);

void computeFrameBuffer(FrameBuffer* frameBuffer,
                        const std::vector<LightSource*>& lightSources,
                        const std::vector<Shape*>& shapes);

void writeFrameBuffer(const FrameBuffer& frameBuffer);

void freeShapeVector(std::vector<Shape*>* shapes);
void freeLightSourceVector(std::vector<LightSource*>* lightSources);

#endif
