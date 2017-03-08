#include <iostream>

#include <anydsl_runtime.hpp>

#include "pnm_image.h"

extern "C" void aobench();

extern "C"
void saveppm(uint8_t* img, int width, int height) {
    write_pnm_image(img, width, height, "aobench.ppm", pnm_t::P6);
}

// polyfill of non-standard drand48()
#ifdef _MSC_VER

#include <random>
static std::mt19937_64 std_gen64;
static std::uniform_real_distribution<double> std_dist64(0., 1.);
extern "C" void srand48(int64_t seed) { std_gen64.seed(seed); }
extern "C" double drand48() { return std_dist64(std_gen64); }

static std::uniform_int_distribution<int64_t> std_disti64(-(1 << 31), 1 << 31);
extern "C" int64_t mrand48() { return std_disti64(std_gen64); }

#endif // _MSC_VER

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    std::cout << "Running aobench ..." << std::endl;
    aobench();

    return EXIT_SUCCESS;
}

