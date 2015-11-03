#include <iostream>

#include <thorin_runtime.hpp>

extern "C" int main_impala();

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    std::cout << "Calculating median in AnyDSL ..." << std::endl;
    return main_impala();
}

