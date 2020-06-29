#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "vec3f.hpp"

class FrameBuffer {
    public:
        const int width, height;      // In pixels.
        const double horFOV, vertFOV; // Expressed in radians. horFOV:vertFOV = aspect ratio.
        const Vec3f pos, dir;         // Vector for camera position, unit vector for camera orientation.

        // Constructors
        FrameBuffer();
        FrameBuffer(int w, int h,
                    double fov = 90,
                    double aspectRatio = 0.75,
                    Vec3f pos = Vec3f(0, 0, 0),
                    Vec3f dir = Vec3f(0, 0, -1)); // Use right hand rule to get direction of positive axes.
        
        // Destructors
        ~FrameBuffer();
    private:
        u_int8_t* frameBuffer;       // Stores pixel information.
};

#endif