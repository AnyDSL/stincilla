#include <iostream>

#include <thorin_runtime.h>

#include "pnm_image.h"

extern "C" void thorin_bilateral_grid(float *, float *, int, int);

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
    for (size_t i=0; i<width*height; ++i) input[i] = image[i]/255.0f;

    std::cout << "Running bilateral grid ..." << std::endl;
    thorin_bilateral_grid(input, output, width, height);

    // write image
    for (size_t i=0; i<width*height; ++i) image[i] = (uint8_t)(output[i]*255.0f);
    write_pnm_image(image, width, height, "lena_out.pgm");

    // memory cleanup
    thorin_free(input);
    thorin_free(output);

    return EXIT_SUCCESS;
}

