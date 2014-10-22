#include <iostream>
#include <thorin_runtime.h>

extern "C" int main_impala();

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    // initialize AnyDSL runtime
    thorin_init();

    std::cout << "Calculating median in AnyDSL ..." << std::endl;
    auto ret = main_impala();
    thorin_print_total_timing();

    return ret;
}

