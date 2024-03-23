#!/bin/bash

# Script to create scene .ppm image

# Compile main.cpp with g++ and C++11 support
g++ -std=c++11 main.cpp -o main

# Run the compiled Raytracer executable
./main > output.ppm