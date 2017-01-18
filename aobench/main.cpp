#include <iostream>

#include <anydsl_runtime.hpp>

#include "pnm_image.h"

extern "C" void aobench();

extern "C"
void saveppm(uint8_t* img, int width, int height) {
    write_pnm_image(img, width, height, "aobench.ppm", pnm_t::P6);
}

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    std::cout << "Running aobench ..." << std::endl;
    aobench();

    return EXIT_SUCCESS;
}

