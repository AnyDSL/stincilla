add_executable(jit jit.cpp)
target_link_libraries(jit ${AnyDSL_runtime_IMPALA_JIT_LIBRARIES})
set_target_properties(jit PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("jit" jit)

add_stincilla_test(stencil_dsl "" stencil_dsl.impala)

if(NOT (BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx"))
    add_stincilla_test(multi_gpu "" "../utils.impala;multi_gpu.impala")
    add_stincilla_test(alloc_gpu "" alloc_gpu.impala)

    if(BACKEND STREQUAL "cuda" OR BACKEND STREQUAL "nvvm")
        add_stincilla_test(print_gpu "" print_gpu.impala)
    endif()

    add_stincilla_test(alloc_gpu_unified "" alloc_gpu_unified.impala)
    add_stincilla_test(reserve_shared "" reserve_shared.impala)

    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
        add_stincilla_test(half_float_gpu "" half_float_gpu.impala)
    endif()
endif()
