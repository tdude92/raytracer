#ifndef CFGPARSER_HPP
#define CFGPARSER_HPP

#include <vector>
#include <string>
#include "geometry.hpp"

typedef int rt_object;

enum OBJ {
    FRAMEBUFFER,
    SPHERE,
    TRIANGLE,
    LIGHTSOURCE
};


struct Config {
    int width, height;
    double fov, aspectRatio;
    std::vector<Shape*> shapes;
    std::vector<LightSource> lightSources;
};


struct ObjData {
    rt_object type = OBJ::FRAMEBUFFER;
    Vec3f pos, colour;
    double radius, brightness;
    bool diffuse;
};


void loadConfiguration(const std::string& fileName, Config* cfg);

#endif