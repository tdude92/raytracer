#include <iostream>
#include "vec3f.hpp"
#include "engine.hpp"
#include "cfgparser.hpp"
#include "stb/stb_image_write.h"

void printv(const Vec3f& v) {
    std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}

int main(int argc, char** argv) {
    // Takes .cfg filename as system argument.
    Config cfg;
    loadConfiguration(argv[1], &cfg);

    std::cout << cfg.width << std::endl;
    std::cout << cfg.height << std::endl;
    std::cout << cfg.fov << std::endl;
    std::cout << cfg.aspectRatio << std::endl;

    for (auto itr = cfg.shapes.begin(); itr != cfg.shapes.end(); ++itr)
        printv((*itr)->colour);
    
    for (auto itr = cfg.lightSources.begin(); itr != cfg.lightSources.end(); ++itr)
        printv(itr->pos);

    return 0;
}