#ifndef INTERVAL_H
#define INTERVAL_H

#include "utils.h"

class interval {
    public:
        double min, max;

        interval() : min(+infinity), max(-infinity) {} // Default constructor

        interval(double _min, double _max) : min(_min), max(_max) {} // Parametrized constructor

        // Checks if the interval contains a given value (inclusive of the bounds)
        bool contains(double x) const {
            return min <= x && x <= max;
        }

        // Checks if the interval surrounds a given value (exclusive of the bounds)
        bool surrounds(double x) const {
            return min < x && x < max;
        }

        // Clamps a given value to be within the interval's bounds
        double clamp(double x) const {
            if (x < min)
                return min;
            if (x > max)
                return max;
            return x;
        }

        static const interval empty, universe;
};

// Static interval objects definitions
const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);

#endif