#include <iostream>
#include <thorin_runtime.h>

#include "pnm_image.h"

extern "C" void thorin_ao();

extern "C"
void saveppm(uint8_t *img, int width, int height) {
    write_pnm_image(img, width, height, "ao.ppm", pnm_t::P6);
}

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    // initialize AnyDSL runtime
    thorin_init();

    std::cout << "Calculating aobench in AnyDSL ..." << std::endl;
    thorin_ao();
    thorin_print_total_timing();

    return EXIT_SUCCESS;
}

