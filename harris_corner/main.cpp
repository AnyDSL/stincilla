#include <iostream>

#include <thorin_runtime.hpp>

#include "pnm_image.h"

extern "C" void thorin_harris_corner(float*, float*, int, int);

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    // Lena test image
    int width, height;
    uint8_t* image = read_pnm_image(&width, &height, argc > 1 ? argv[1] : "lena.pgm");

    // host memory for image of width x height pixels
    // use thorin::Array from AnyDSL runtime for memory allocation
    thorin::Array<float>  input(width * height);
    thorin::Array<float> output(width * height);

    // initialize data
    for (size_t i=0; i<width*height; ++i) input[i] = image[i];

    std::cout << "Running Harris corner ..." << std::endl;
    thorin_harris_corner(input.data(), output.data(), width, height);

    // write image
    for (size_t i=0; i<width*height; ++i) image[i] = (uint8_t)output[i];
    write_pnm_image(image, width, height, "lena_out.pgm");

    return EXIT_SUCCESS;
}

