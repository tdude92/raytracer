#include <iostream>
#include <cmath>
#include <ctime>
#include "vec3f.hpp"
#include "engine.hpp"
#include "cfgparser.hpp"

int main(int argc, char** argv) {
    srand(time(NULL));

    // Takes .cfg filename as system argument.
    Config cfg;
    loadConfiguration(argv[1], &cfg);

    FrameBuffer fb(cfg.width, cfg.height, cfg.fov);
    computeFrameBuffer(&fb, cfg.lightSources, cfg.shapes);
    writeFrameBuffer(fb);
    freeShapeVector(&cfg.shapes);
    freeLightSourceVector(&cfg.lightSources);

    return 0;
}