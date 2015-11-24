#include <algorithm>
#include <iostream>
#include <limits>

#include <thorin_runtime.hpp>

#include "pnm_image.h"

extern "C" void sharpening(short*, short*, int, int);

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    // test image
    int width, height;
    uint8_t *image = read_pnm_image(&width, &height, argc > 1 ? argv[1] : "goldhill.pgm");

    // host memory for image of width x height pixels
    // use thorin::Array from AnyDSL runtime for memory allocation
    thorin::Array<short>  input(width * height);
    thorin::Array<short> output(width * height);

    // initialize data
    for (size_t i=0; i<width*height; ++i) input[i] = (short)image[i];

    sharpening(input.data(), output.data(), width, height);

    // write image
    for (size_t i=0; i<width*height; ++i) image[i] = std::min<short>(std::max<short>(output[i], 0), 255);
    write_pnm_image(image, width, height, "goldhill_out.pgm");

    return EXIT_SUCCESS;
}

