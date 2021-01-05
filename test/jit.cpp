#include <iostream>
#include <string>

#include <anydsl_runtime.h>
#include <anydsl_jit.h>

typedef int(*exec_cpu_fn)();
typedef int(*exec_gpu_fn)();

int main(int argc, const char **argv) {
    std::string program_cpu = "#[export] fn get_42() -> i32 { 42 }";
    std::string program_gpu =
        "#[export] fn get_42() -> i32 {"
        "   let (platform, device, codegen) = (2, 0, opencl);"
        "   /*let (platform, device, codegen) = (1, 0, cuda);*/"
        "   /*let (platform, device, codegen) = (1, 0, nvvm);*/"
        "   /*let (platform, device, codegen) = (3, 1, amdgpu);*/"
        "   let size = sizeof[i32]();"
        "   let dev_cpu  = runtime_device(0, 0);"
        "   let dev_gpu  = runtime_device(platform, device);"
        "   let data_cpu = runtime_alloc(dev_cpu, size);"
        "   let data_gpu = runtime_alloc(dev_gpu, size);"
        "   let ptr_cpu = bitcast[&mut[i32]](data_cpu);"
        "   let ptr_gpu = bitcast[&mut addrspace(1)[i32]](data_gpu);"
        "   ptr_cpu(0) = 0;"
        "   runtime_copy(dev_cpu, data_cpu, 0, dev_gpu, data_gpu, 0, size);"
        "   codegen(device, (1, 1, 1), (1, 1, 1), || { ptr_gpu(0) = 42; });"
        "   runtime_copy(dev_gpu, data_gpu, 0, dev_cpu, data_cpu, 0, size);"
        "   let res = ptr_cpu(0);"
        "   runtime_release(dev_cpu, data_cpu);"
        "   runtime_release(dev_gpu, data_gpu);"
        "   res"
        "}";

    auto key_cpu = anydsl_compile(program_cpu.c_str(), (uint32_t)program_cpu.size(), 3);
    if (auto ptr = anydsl_lookup_function(key_cpu, "get_42")) {
        auto fun = reinterpret_cast<exec_cpu_fn>(ptr);
        auto res = fun();
        std::cout << "Simple CPU jit test: " << res << std::endl;
    } else {
        std::cout << "Compilation failed!" << std::endl;
        return EXIT_FAILURE;
    }

    auto key_gpu = anydsl_compile(program_gpu.c_str(), (uint32_t)program_gpu.size(), 3);
    if (auto ptr = anydsl_lookup_function(key_gpu, "get_42")) {
        auto fun = reinterpret_cast<exec_gpu_fn>(ptr);
        auto res = fun();
        std::cout << "Simple GPU jit test: " << res << std::endl;
    } else {
        std::cout << "Compilation failed!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
