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
    POINTLIGHTSOURCE,
    DIRECTIONALLIGHTSOURCE
};


struct Config {
    int width, height;
    double fov;
    std::vector<Shape*> shapes;
    std::vector<LightSource*> lightSources;
};


struct ObjData {
    rt_object type = OBJ::FRAMEBUFFER;
    Vec3f pos, colour, dir;
    double radius, intensity;
};


void loadConfiguration(const std::string& fileName, Config* cfg);

#endif