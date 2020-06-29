#include <iostream>
#include "vec3f.hpp"
#include "stb/stb_image_write.h"

void printv(const Vec3f& v) {
    std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}

int main() {
    Vec3f x(1, 2, 3123), y(1, 0.0003, 2);
    Vec3f a = x + y;
    printv(a);
    printv(x - y);
    printv(-x);
    printv(x * 2);
    printv(x * y);
    printv(x / 3);
    printv(x / y);
    std::cout << x.magnitude() << std::endl;
    printv(x.direction());

    return 0;
}