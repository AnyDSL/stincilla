wrap_impala_sources(STENCIL_INT_PROGRAM
    FILES stencil_dsl.impala)
add_executable(stencil_dsl ${STENCIL_INT_PROGRAM})
target_link_libraries(stencil_dsl ${IMPALA_RUNTIME_LIBRARIES})
add_test("stencil_dsl" stencil_dsl)

if(NOT (BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx"))
    add_test_sample(multi_gpu ../utils.impala multi_gpu.impala)

    add_test_sample(alloc_gpu alloc_gpu.impala)

    add_test_sample(alloc_gpu_unified alloc_gpu_unified.impala)

    add_test_sample(reserve_shared reserve_shared.impala)

    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
        # wrap_impala_sources(HALF_FLOAT_GPU_PROGRAM
            # FILES ../${BACKEND_FILE} half_float_gpu.impala)
        # add_executable(half_float_gpu ${HALF_FLOAT_GPU_PROGRAM})
        # target_link_libraries(half_float_gpu ${IMPALA_RUNTIME_LIBRARIES})
        # add_test("half_float_gpu" half_float_gpu)
        add_test_sample(half_float_gpu half_float_gpu.impala)
    endif()
endif()
