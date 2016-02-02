#include <iostream>

#include <thorin_runtime.hpp>

#include "pnm_image.h"

extern "C" void bilateral_grid(float*, int, int);

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    // Lena test image
    int width, height;
    uint8_t* image = read_pnm_image(&width, &height, argc > 1 ? argv[1] : "lena.pgm");

    // host memory for image of width x height pixels
    // use thorin::Array from AnyDSL runtime for memory allocation
    thorin::Array<float> float_image(width * height);

    // initialize data
    for (size_t i=0; i<width*height; ++i) float_image[i] = image[i]/255.0f;

    bilateral_grid(float_image.data(), width, height);

    // write image
    for (size_t i=0; i<width*height; ++i) image[i] = (uint8_t)(float_image[i]*255.0f);
    write_pnm_image(image, width, height, "lena_out.pgm");

    return EXIT_SUCCESS;
}

