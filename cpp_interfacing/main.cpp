#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "pgm_image.h"
#include "cu_runtime.h"

extern "C" void thorin_bilateral(float *, float *, int, int);

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    // initialize AnyDSL runtime
    thorin_init();

    // Lena test image
    short int *image;
    int width, height;
    image = read_image(&width, &height, "lena.pgm");

    // host memory for image of width x height pixels
    // use thorin_malloc from AnyDSL runtime for memory allocation
    float *input = (float *)thorin_malloc(width * height * sizeof(float));
    float *output = (float *)thorin_malloc(width * height * sizeof(float));

    // initialize data
    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            input[y*width + x] = (float)image[y*width + x];
        }
    }

    fprintf(stderr, "Calculating filter in AnyDSL ...\n");
    thorin_bilateral(input, output, width, height);

    // write image
    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            image[y*width + x] = (short int)output[y*width + x];
        }
    }
    write_image(image, width, height, "lena_out.pgm");

    // memory cleanup
    thorin_free(input);
    thorin_free(output);

    return EXIT_SUCCESS;
}

