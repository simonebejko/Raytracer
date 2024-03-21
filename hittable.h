#ifndef HITTABLE_H
#define HITTABLE_H

#include "utils.h"

class material;

class hit_record {
    public:
        point3 p;                   // The point at which the ray hits the object
        vec3 normal;                // The normal vector at the hit point
        shared_ptr<material> mat;   // Pointer to the material of the object hit
        double t;                   // The parameter t from the ray equation that gives the hit point
        bool front_face;            // True if the ray hits the front face of the object

        /*
         *  Sets the hit record's normal vector and `front_face` flag
         *  NOTE: the parameter `outward_normal` is assumed to have unit length
         */
        void set_face_normal(const ray &r, const vec3 &outward_normal) {
            // Determine if the ray hits the surface from outside or inside
            front_face = dot(r.direction(), outward_normal) < 0;
            // Adjust normal to always point against ray direction
            normal = front_face ? outward_normal : -outward_normal;
        }
};

// Abstract base class for hittable objects
class hittable {
    public:
        // Virtual destructor for safe polymorphic deletion
        virtual ~hittable() = default;


        // Pure virtual method for determining if an object-ray intersection happens within the interval
        virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;
};

#endif