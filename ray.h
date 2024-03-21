#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        ray() {} // Default constructor

        ray(const point3 &origin, const vec3 &direction) : orig(origin), dir(direction) {} // Parametrized constructor

        point3 origin() const { return orig; } // Gets the ray's origin
        vec3 direction() const { return dir; } // Gets the ray's direction

        /*
         * Computes and returns a point along the ray at parameter t.
         * The point is calculated as origin + t * dir, which scales the direction
         * vector by t and adds it to the origin, moving the point along the ray
         */
        point3 at(double t) const {
            return orig + t * dir;
        }

    private:
        point3 orig;
        vec3 dir;
    };

#endif