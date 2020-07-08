#include <iostream>
#include "vec3f.hpp"
#include "engine.hpp"
#include "cfgparser.hpp"

int main(int argc, char** argv) {
    // Takes .cfg filename as system argument.
    Config cfg;
    loadConfiguration(argv[1], &cfg);

    FrameBuffer fb(cfg.width, cfg.height, cfg.fov, cfg.aspectRatio);
    computeFrameBuffer(&fb, cfg.lightSources, cfg.shapes);
    writeFrameBuffer(fb);
    freeShapeVector(&cfg.shapes);

    return 0;
}