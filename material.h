#ifndef MATERIAL_H
#define MATERIAL_H

#include "utils.h"
#include "color.h"
#include "hittable.h"

class hit_record;

// Abstract base class for materials
class material {
    public:
        virtual ~material() = default; // Virtual destructor for safe polymorphic deletion

        // Pure virtual method for scattering rays off the material
        virtual bool scatter(
            const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const = 0;
};

// Lambertian material (perfect matte surface)
class lambertian : public material {
    public:
        lambertian(const color &a) : albedo(a) {}

        // Scatters rays in random directions with no reflection
        bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered)
        const override {
            auto scatter_direction = rec.normal + random_unit_vector();

            // Catch degenerate scatter direction
            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;

            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo; // Attenuate ray with albedo color
            return true;
        }

    private:
        color albedo; // Base color
};


// Metal material (reflective)
class metal : public material {
    public:
        metal(const color &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        // Reflects rays with possible fuzziness
        bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered)
        const override {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal); // Perfect reflection
            scattered = ray(rec.p, reflected + fuzz * random_unit_vector()); // Add fuzz
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0); // Scatter if the dot product is positive
        }

    private:
        color albedo;
        double fuzz;
};

// Dielectric material (transparent)
class dielectric : public material {
    public:
        dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        // Handles refraction and reflection based on the index of refraction
        bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered)
        const override {
            attenuation = color(1.0, 1.0, 1.0); // Full transmission with no attenuation
            double refraction_ratio = rec.front_face ? (1.0 / ir) : ir; // Adjust refraction ratio

            vec3 unit_direction = unit_vector(r_in.direction()); 
            double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0; // Total internal reflection check
            vec3 direction;

            // Choose reflection or refraction based on Schlick's approximation
            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
                direction = reflect(unit_direction, rec.normal);
            else
                direction = refract(unit_direction, rec.normal, refraction_ratio);

            scattered = ray(rec.p, direction);
            return true;
        }

    private:
        double ir; // Index of refraction

        // Schlick's approximation for reflectance
        static double reflectance(double cosine, double ref_idx) {
            auto r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0 * r0;
            return r0 + (1 - r0) * pow((1 - cosine), 5);
        }
};

#endif