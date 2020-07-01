#include <iostream>
#include "vec3f.hpp"
#include "geometry.hpp"
#include "stb/stb_image_write.h"

void printv(const Vec3f& v) {
    std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}

int main() {
    Ray ray(Vec3f(0, 0, 0), Vec3f(0, 0, 1).direction());
    Sphere x(Vec3f(0, 12, 3), 12, Vec3f(255, 255, 255));
    Shape* sphere = &x;
    Vec3f* intersection = sphere->getRayIntersection(ray);

    printv(*intersection);

    return 0;
}