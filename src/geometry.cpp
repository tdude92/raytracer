#include <cmath>
#include "geometry.hpp"
#include "engine.hpp"

// TODO: Complete Triangle::getRayIntersection() and Triangle::getNormal() and Triangle::~Triangle().
// TODO: Return >1 intersections if possible. (Might not be necessary)
//       (During refraction ray cast from first intersection of circle to second intersection
//        )

// STRUCT RAY
// Constructors
Ray::Ray()
        : origin(Vec3f()), dir(Vec3f()) {}

Ray::Ray(const Vec3f& origin, const Vec3f& dir)
          : origin(origin), dir(dir) {}


// CLASS LIGHTSOURCE
LightSource::LightSource(const Vec3f& pos, const Vec3f& colour, double intensity)
                        : pos(pos), colour(colour), intensity(intensity) {}


// CLASS POINTLIGHTSOURCE
// Constructors
PointLightSource::PointLightSource(const Vec3f& pos, const Vec3f& colour, double intensity)
                                  : LightSource(pos, colour, intensity) {}

// Member Functions
Vec3f PointLightSource::getColour(const Vec3f& origin, const std::vector<LightSource*>& lightSources, const std::vector<Shape*>& shapes, int samples) const {
    return colour;
}


// CLASS DIRECTIONALLIGHTSOURCE
// Constructors
DirectionalLightSource::DirectionalLightSource(const Vec3f& pos, const Vec3f& colour, const Vec3f& dir,  double radius, double intensity)
                                              : dir(dir.direction()), radius(radius), LightSource(pos, colour, intensity) {}

// Member Functions
Vec3f DirectionalLightSource::getColour(const Vec3f& origin, const std::vector<LightSource*>& lightSources, const std::vector<Shape*>& shapes, int samples) const {
    // TODO: MAKE IT ACTUALLY DIRECTIONAL. DOT PRODUCT STUFF WITH RAY DIR AND NORMAL.
    Vec3f sum = Vec3f();

    Vec3f basisX = Vec3f(dir.z, 0, -dir.x).direction();
    Vec3f basisY = cross(dir, basisX);

    Ray ray;
    Vec3f sampledPoint;
    double rR, rTheta; // Random numbers.
    for (int i = 0; i < samples; ++i) {
        rR = ((double)rand()/RAND_MAX);
        rTheta = ((double)rand()/RAND_MAX);
        sampledPoint = pos + (basisX*cos(rTheta) + basisY*sin(rTheta)) * radius * rR;

        ray.origin = origin;
        ray.dir = (sampledPoint - origin).direction();

        sum = sum + rayTrace(ray, this, lightSources, shapes, true);
    }
    return sum / samples;
}


// CLASS SHAPE
// Constructors
Shape::Shape(const Vec3f& colour)
            : colour(colour) {}


// CLASS SPHERE
// Constructors
Sphere::Sphere(const Vec3f& center, double radius, const Vec3f& colour)
              : center(center), radius(radius)
              , Shape(colour) {}

// Member functions
Vec3f* Sphere::getRayIntersection(const Ray& ray) const {
    double discriminant = pow(dot(ray.dir, ray.origin - center), 2) - (pow((ray.origin - center).magnitude(), 2) - radius*radius);
    double d = -dot(ray.dir, ray.origin - center);

    if (discriminant < 0) {
        return nullptr;
    } else if (discriminant == 0) {
        return new Vec3f(ray.origin + ray.dir*d);
    } else {
        Vec3f* intersection = new Vec3f();
        double root1 = sqrt(discriminant), root2 = -sqrt(discriminant);

        if (d + root1 < 0 && d + root2 < 0) {
            // if d <= 0, then the point of intersection is in the opposite direction of the ray from the origin.
            // (this is because we represent a ray in the form: x = ray.origin + ray.dir*d, where d is an element
            //  of naturals with zero)
            return nullptr;
        } else if (d + root1 < 0) {
            d += root2;
        } else if (d + root2 < 0) {
            d += root1;
        } else {
            d += fmin(root1, root2) - 1e-5;
        }

        *intersection = ray.origin + ray.dir*d;
        return intersection;
    }
}

Vec3f Sphere::getNormal(const Ray& ray, const Vec3f& p) const {
    // p is the point of intersection between the previous ray and the sphere.
    Vec3f normal = (center - p).direction();
    if (dot(normal, p - ray.origin) <= 0)
        normal = -normal;
    
    return normal;
}

Vec3f Sphere::getPos() const {
    return center;
}


// CLASS TRIANGLE
// Constructors
Triangle::Triangle(Vec3f* vertices, const Vec3f& colour)
                  : v(vertices), Shape(colour) {}

// Destructors
Triangle::~Triangle() {}

// Member functions
Vec3f* Triangle::getRayIntersection(const Ray& ray) const {}
Vec3f Triangle::getNormal(const Ray& ray, const Vec3f& p) const {}
Vec3f Triangle::getPos() const {}
