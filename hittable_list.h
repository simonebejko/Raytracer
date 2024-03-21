#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
    public:
        // Container for holding shared pointers to hittable objects
        std::vector<shared_ptr<hittable>> objects;

        // Default constructor
        hittable_list() {}

        // Constructor that takes hittable object and adds it to the list
        hittable_list(shared_ptr<hittable> object) { add(object); }

        // Clears list
        void clear() { objects.clear(); }

        // Adds new object to list
        void add(shared_ptr<hittable> object) {
            objects.push_back(object);
        }

        // Checks if a ray hits any object in the list
        bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_t.max;

            for (const auto &object : objects) {
                if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
};

#endif