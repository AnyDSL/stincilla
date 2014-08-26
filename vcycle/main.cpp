#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <thorin_runtime.h>

#include "pgm_image.h"

extern "C" void thorin_vcycle(float *, float *, int, int);

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    // initialize AnyDSL runtime
    thorin_init();

    // Lena test image
    int width, height;
    uint8_t *image = read_pgm_image(&width, &height, argc > 1 ? argv[1] : "lena.pgm");

    // host memory for image of width x height pixels
    // use thorin_malloc from AnyDSL runtime for memory allocation
    float *input  = (float *)thorin_malloc(width * height * sizeof(float));
    float *output = (float *)thorin_malloc(width * height * sizeof(float));

    // initialize data
    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            input[y*width + x] = (float)image[y*width + x];
        }
    }

    fprintf(stderr, "Calculating V-Cycle in AnyDSL ...\n");
    thorin_vcycle(input, output, width, height);
    thorin_print_total_timing();

    // write image
    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            image[y*width + x] = (uint8_t)output[y*width + x];
        }
    }
    write_pgm_image(image, width, height, "lena_out.pgm");

    // memory cleanup
    thorin_free(input);
    thorin_free(output);

    return EXIT_SUCCESS;
}

