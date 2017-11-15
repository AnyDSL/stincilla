#include <iostream>

#include <anydsl_runtime.hpp>

#include "pnm_image.h"

extern "C" void run_halide(int*, int, int);

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    // Lena test image
    int width, height;
    std::string filename(argc > 1 ? argv[1] : "lena.pgm");
    std::string out(argc > 2 ? argv[2] : filename.c_str());
    out.insert(out.find_last_of('.'), "_out");
    out.replace(0, out.find_last_of('/') + 1, "", 0);
    uint8_t* image = read_pnm_image(&width, &height, filename.c_str());

    // host memory for image of width x height pixels
    // use anydsl::Array from AnyDSL runtime for memory allocation
    anydsl::Array<int> int_image(width * height);

    // initialize data
    for (size_t i=0; i<width*height; ++i)
        int_image[i] = image[i];

    run_halide(int_image.data(), width, height);

    // write image
    for (size_t i=0; i<width*height; ++i)
        image[i] = (uint8_t)int_image[i];
    write_pnm_image(image, width, height, out.c_str());

    return EXIT_SUCCESS;
}

