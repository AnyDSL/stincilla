#include <iostream>

#include <anydsl_runtime.hpp>

#include "pnm_image.h"

typedef STINCILLA_DATA_TYPE pixel_t;
extern "C" void harris_corner(pixel_t*, pixel_t*);

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    // Lena test image
    int width, height;
    uint8_t* image = read_pnm_image(&width, &height, argc > 1 ? argv[1] : "lena.pgm");

    // host memory for image of width x height pixels
    // use anydsl::Array from AnyDSL runtime for memory allocation
    anydsl::Array<pixel_t>  input(width * height);
    anydsl::Array<pixel_t> output(width * height);

    // initialize data
    for (size_t i=0; i<width*height; ++i) input[i] = image[i];

    harris_corner(input.data(), output.data());

    // write image
    for (size_t i=0; i<width*height; ++i) image[i] = (uint8_t)output[i];
    //write_pnm_image(image, width, height, "lena_out.pgm");
    write_pnm_image(image, width, height, "lena_out.pgm");
    
    return EXIT_SUCCESS;
}

