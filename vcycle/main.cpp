#include <cfloat>
#include <iostream>
#include <thorin_runtime.h>

#include "pnm_image/pnm_image.h"

extern "C" void thorin_vcycle(float *, float *, int, int);

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    // initialize AnyDSL runtime
    thorin_init();

    // Lena test image
    int width, height;
    uint8_t *image = read_pnm_image(&width, &height, argc > 1 ? argv[1] : "lena.pgm");

    // host memory for image of width x height pixels
    // use thorin_malloc from AnyDSL runtime for memory allocation
    float *input  = (float *)thorin_malloc(width * height * sizeof(float));
    float *output = (float *)thorin_malloc(width * height * sizeof(float));

    // initialize data
    for (size_t i=0; i<width*height; ++i) input[i] = (float)image[i];

    std::cout << "Calculating V-Cycle in AnyDSL ..." << std::endl;
    thorin_vcycle(input, output, width, height);
    thorin_print_total_timing();

    // compute offset to shift image range
    float min = FLT_MAX;
    uint8_t offset = 0;
    for (size_t i=0; i<width*height; ++i) if (output[i] < min) min = output[i];
    if (min < 0) offset = -min;

    // write image
    for (size_t i=0; i<width*height; ++i) image[i] = (uint8_t)output[i] + offset;
    write_pnm_image(image, width, height, "lena_out.pgm");

    // memory cleanup
    thorin_free(input);
    thorin_free(output);

    return EXIT_SUCCESS;
}

