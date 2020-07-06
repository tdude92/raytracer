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
                    double aspectRatio = 0.75); // (Vertical FOV) / (Horizontal FOV)
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
        double getDepth() const;
        Vec3f getP0() const;

    private:
        int width, height;          // In pixels.
        double horFOV, vertFOV;     // Expressed in radians. horFOV:vertFOV = aspect ratio.
        uint8_t* frameBuffer;       // Stores pixel information.
        double depth;               // Distance between camera origin and frame.
        Vec3f p0;                   // Top left corner of frame.
};


void computeFrameBuffer(FrameBuffer* frameBuffer,
                        const std::vector<LightSource>& lightSources,
                        const std::vector<Shape*>& shapes);

void writeFrameBuffer(const FrameBuffer& frameBuffer);

void freeShapeVector(std::vector<Shape*>* shapes);

#endif
