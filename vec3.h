#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
    public:
        double e[3]; // Array to store the three components of the vector

        vec3() : e{0, 0, 0} {} // Default constructor

        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {} // Parametrized constructor

        // Member functions for accessing elements
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // Unary minus operator (returns the negation of the vector)
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

        // Subscript operators for element access
        double operator[](int i) const { return e[i]; }
        double &operator[](int i) { return e[i]; }

        // Adds the given vector to this vector (compound assignment operator)
        vec3 &operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        // Multiplies this vector by a given scalar (compound assignment operator)
        vec3 &operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        // Divides this vector by a given scalar (compound assignment operator)
        vec3 &operator/=(double t) {
            return *this *= 1 / t;
        }

        // Returns the length (magnitude) of the vector
        double length() const {
            return sqrt(length_squared());
        }

        // Returns the square of the length (magnitude) of the vector
        double length_squared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        // Returns true if the vector is close to zero in all dimensions
        bool near_zero() const {
            auto s = 1e-8;
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }

        // Generates a random vector with components in range [0,1)
        static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        // Generates a random vector with components in range [min,max)
        static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
};

// Alias for vec3
using point3 = vec3;

/*
 * Vector utility functions
 */

// Output vector components
inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Adds two vectors component-wise
inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// Subtracts vector v from vector u component-wise
inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// Multiplies two vectors component-wise
inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// Multiplies a vector by a scalar
inline vec3 operator*(double t, const vec3 &v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

// Multiplies a vector by a scalar (alternative syntax)
inline vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}

// Divides a vector by a scalar
inline vec3 operator/(vec3 v, double t)
{
    return (1 / t) * v;
}

// Calculates the dot product of two vectors
inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// Calculates the cross product of two vectors
inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// Returns a unit vector in the direction of the vector v
inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

// Generates a random point inside a unit disk
inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}

// Generates a random point inside a unit sphere
inline vec3 random_in_unit_sphere(){
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() < 1)
            return p;
    }
}

// Generates a random unit vector
inline vec3 random_unit_vector(){
    return unit_vector(random_in_unit_sphere());
}

// Generates a random vector on the hemisphere around a normal
inline vec3 random_on_hemisphere(const vec3 &normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

// Reflects a vector v around the normal n
vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2 * dot(v, n) * n;
}

// Refracts a vector uv according to Snell's law, given the normal n and the ratio of indices of refraction
inline vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif