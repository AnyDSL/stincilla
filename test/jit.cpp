#include <iostream>
#include <string>

#define RUNTIME_ENABLE_JIT
#include <anydsl_runtime.h>

typedef int(*exec_cpu_fn)();

int main(int argc, const char **argv) {
    std::string cpu_program = "extern fn get_42() -> i32 { 42 }";

    auto key = anydsl_compile(cpu_program.c_str(), (uint32_t)cpu_program.size(), 3);
    if (auto ptr = anydsl_lookup_function(key, "get_42")) {
        auto fun = reinterpret_cast<exec_cpu_fn>(ptr);
        auto res = fun();
        std::cerr << "Simple CPU jit test: " << res << std::endl;
    } else {
        std::cerr << "Compilation failed!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
