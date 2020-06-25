#include "catch2/catch.hpp"
#include "vec3f.hpp"

TEST_CASE("Operators work as expected.", "[operators]") {

}

TEST_CASE("Vector operations work as expected", "[operations]") {
    Vec3f case1(1, 1, 1),
          case2(1, 2, 3),
          case5(-4, 1, -10),
          case3(407, 3210, 1124),
          case4(0.01, 0.005, 0.00006),
          case5(0, 0, 0);

    SECTION("vector magnitude") {}
    SECTION("unit vector computation") {}
}