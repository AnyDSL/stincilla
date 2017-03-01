wrap_impala_sources(STENCIL_INT_PROGRAM
    FILES stencil_dsl.impala)
add_executable(stencil_dsl ${STENCIL_INT_PROGRAM})
target_link_libraries(stencil_dsl ${IMPALA_RUNTIME_LIBRARIES})
add_test("stencil_dsl" stencil_dsl)

if(NOT (BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx"))
    wrap_impala_sources(MULTI_GPU_PROGRAM
        FILES ../${BACKEND_FILE} ../utils.impala multi_gpu.impala)
    add_executable(multi_gpu ${MULTI_GPU_PROGRAM})
    target_link_libraries(multi_gpu ${IMPALA_RUNTIME_LIBRARIES})
    add_test("multi_gpu" multi_gpu)

    wrap_impala_sources(ALLOC_GPU_PROGRAM
        FILES ../${BACKEND_FILE} alloc_gpu.impala)
    add_executable(alloc_gpu ${ALLOC_GPU_PROGRAM})
    target_link_libraries(alloc_gpu ${IMPALA_RUNTIME_LIBRARIES})
    add_test("alloc_gpu" alloc_gpu)

    wrap_impala_sources(ALLOC_GPU_UNIFIED_PROGRAM
        FILES ../${BACKEND_FILE} alloc_gpu_unified.impala)
    add_executable(alloc_gpu_unified ${ALLOC_GPU_UNIFIED_PROGRAM})
    target_link_libraries(alloc_gpu_unified ${IMPALA_RUNTIME_LIBRARIES})
    add_test("alloc_gpu_unified" alloc_gpu_unified)

    wrap_impala_sources(RESERVE_SHARED_PROGRAM
        FILES ../${BACKEND_FILE} reserve_shared.impala)
    add_executable(reserve_shared ${RESERVE_SHARED_PROGRAM})
    target_link_libraries(reserve_shared ${IMPALA_RUNTIME_LIBRARIES})
    add_test("reserve_shared" reserve_shared)

    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
        wrap_impala_sources(HALF_FLOAT_GPU_PROGRAM
            FILES half_float_gpu.impala)
        add_executable(half_float_gpu ${HALF_FLOAT_GPU_PROGRAM})
        target_link_libraries(half_float_gpu ${IMPALA_RUNTIME_LIBRARIES})
        add_test("half_float_gpu" half_float_gpu)
    endif()
endif()
