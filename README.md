## About
A simple raytracer written in pure C++ that generates a .ppm image depicting a scene of spheres with camera perspectives, surface normals, and various implemented techniques such as material simulations, antialiasing, and defocus blur.

**Disclaimer**: This raytracer is primarily an educational project. It may not encompass all the features or optimizations found in professional raytracing software.

## Getting Started
### Prerequisites
- C++ compiler (e.g., g++, clang++)
- Git (for cloning the repository)

### Installation
To get started, clone the repository to your local machine using the following command:
```
git clone https://github.com/simonebejko/raytracer.git
```

## Usage
To execute the Raytracer, navigate to the project directory in your terminal and run the provided shell script:
```
./run_raytracer.sh
```
The rendered image will be created as `output.ppm` and will be located within the project folder.
It will not be fully rendered until the rendering process is complete - you can track the progress through the terminal output, which displays the number of scanlines remaining. 

You can view the rendered image using any image viewer that supports the PPM format or by converting it to a more common image format such as PNG.


**Note**: The image generation process may take several minutes, if not hours, depending on the value of `samples_per_pixel` (found in `main.cpp`) and your PC's hardware.
By default, the value is set to 500, which produces high-quality images but results in very long rendering times. Consider adjusting this value to a lower number such as 100 or even 10 for quicker results.


## Roadmap
- [X] Streamline running the raytracer with a shell script
- [ ] Improve performance (by parallelization using C++ CPU features, or by integrating CUDA)
- [ ] Update the output image format from .ppm to a more commonly used format (such as .png)

## Acknowledgments
I would like to express my gratitude to Peter Shirley for his valuable ebook 'Raytracer in a Weekend', which served as my guide for developing this project.