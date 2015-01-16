#include <algorithm>
#include <iostream>
#include <limits>
#include <thorin_runtime.h>

#include "pnm_image/pnm_image.h"

extern "C" void thorin_sharpening(short *, short *, int, int);

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    // initialize AnyDSL runtime
    thorin_init();

    // test image
    int width, height;
    uint8_t *image = read_pnm_image(&width, &height, argc > 1 ? argv[1] : "goldhill.pgm");

    // host memory for image of width x height pixels
    // use thorin_malloc from AnyDSL runtime for memory allocation
    short *input  = (short *)thorin_malloc(width * height * sizeof(short));
    short *output = (short *)thorin_malloc(width * height * sizeof(short));

    // initialize data
    for (size_t i=0; i<width*height; ++i) input[i] = (short)image[i];

    // write image
    for (size_t i = 0; i<width*height; ++i) image[i] = std::min<short>(std::max<short>(input[i], 0), 255);
    write_pnm_image(image, width, height, "goldhill_a.pgm", pnm_t::P5);

    std::cout << "Calculating sharpening filter in AnyDSL ..." << std::endl;
    thorin_sharpening(input, output, width, height);
    thorin_print_total_timing();
    // write image
    for (size_t i = 0; i<width*height; ++i) image[i] = std::min<short>(std::max<short>(input[i], 0), 255);
    write_pnm_image(image, width, height, "goldhill_b.pgm");

    // write image
    for (size_t i=0; i<width*height; ++i) image[i] = std::min<short>(std::max<short>(output[i], 0), 255);
    write_pnm_image(image, width, height, "goldhill_out.pgm");

    // memory cleanup
    thorin_free(input);
    thorin_free(output);

    return EXIT_SUCCESS;
}

