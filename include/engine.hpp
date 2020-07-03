#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <cstdint>
#include <vector>
#include "vec3f.hpp"
#include "geometry.hpp"

class FrameBuffer {
    public:
        // Constructors
        FrameBuffer(int w, int h,
                    double fov = 90, // 180 < fov < 0
                    double aspectRatio = 0.75, // (Vertical FOV) / (Horizontal FOV)
                    const Vec3f& pos = Vec3f(0, 0, 0),
                    const Vec3f& dir = Vec3f(0, 0, -1)); // Use right hand rule to get direction of positive axes.
        
        // Destructors
        ~FrameBuffer();

        // Operators
        FrameBuffer& operator=(const FrameBuffer& fb);
        uint8_t* operator[](int i); // Returns pointer to first element in an RGB subarray for a pixel.
                                    // frameBuff[2][0], frameBuff[2][1], frameBuff[2][2] (3rd pixel R, G, B)
        
        // Getters
        const uint8_t* getFrameBuffer() const;
        int getWidth() const;
        int getHeight() const;
        double getHorFOV() const;
        double getVertFOV() const;
        Vec3f getPos() const;
        Vec3f getDir() const;
    private:
        uint8_t* frameBuffer;       // Stores pixel information.
        int width, height;          // In pixels.
        double horFOV, vertFOV;     // Expressed in radians. horFOV:vertFOV = aspect ratio.
        Vec3f pos, dir;             // Vector for camera position, unit vector for camera orientation.
};


struct LightSource {
    LightSource(const Vec3f& pos, const Vec3f& colour, double brightness);
    const Vec3f pos, colour;
    double brightness; // Factor used to control brightness of a light source.
};


void computeFrameBuffer(FrameBuffer* frameBuffer,
                        const std::vector<LightSource>& lightSources,
                        const std::vector<Shape*>& shapes);

void writeFrameBuffer(const FrameBuffer& frameBuffer);

void freeShapeVector(std::vector<Shape*>* shapes);

#endif
