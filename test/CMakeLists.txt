anydsl_runtime_wrap(STENCIL_INT_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${PIXEL_TYPE_FILE} stencil_dsl.impala)
add_executable(stencil_dsl ${STENCIL_INT_PROGRAM})
target_link_libraries(stencil_dsl ${ANYDSL_RUNTIME_LIBRARIES})
add_test("stencil_dsl" stencil_dsl)

anydsl_runtime_wrap(FLOW_GRAPH_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${PIXEL_TYPE_FILE} flow_graph.impala)
add_executable(flow_graph ${FLOW_GRAPH_PROGRAM})
target_link_libraries(flow_graph ${ANYDSL_RUNTIME_LIBRARIES})
add_test("flow_graph" flow_graph)

if(DEVICE STREQUAL "fpga")
    anydsl_runtime_wrap(FPGA_COPY_PROGRAM
        CLANG_FLAGS ${CLANG_FLAGS}
        IMPALA_FLAGS ${IMPALA_FLAGS}
        FILES ${CONFIG_FILES} ../utils.impala fpga_copy.impala)
    add_executable(fpga_copy ${FPGA_COPY_PROGRAM})
    target_link_libraries(fpga_copy ${ANYDSL_RUNTIME_LIBRARIES})
    add_test("fpga_copy" fpga_copy)
endif()

if(DEVICE STREQUAL "acc")
    anydsl_runtime_wrap(MULTI_GPU_PROGRAM
        CLANG_FLAGS ${CLANG_FLAGS}
        IMPALA_FLAGS ${IMPALA_FLAGS}
        FILES ${CONFIG_FILES} ../utils.impala multi_gpu.impala)
    add_executable(multi_gpu ${MULTI_GPU_PROGRAM})
    target_link_libraries(multi_gpu ${ANYDSL_RUNTIME_LIBRARIES})
    add_test("multi_gpu" multi_gpu)

    anydsl_runtime_wrap(ALLOC_GPU_PROGRAM
        CLANG_FLAGS ${CLANG_FLAGS}
        IMPALA_FLAGS ${IMPALA_FLAGS}
        FILES ${CONFIG_FILES} alloc_gpu.impala)
    add_executable(alloc_gpu ${ALLOC_GPU_PROGRAM})
    target_link_libraries(alloc_gpu ${ANYDSL_RUNTIME_LIBRARIES})
    add_test("alloc_gpu" alloc_gpu)

    anydsl_runtime_wrap(ALLOC_GPU_UNIFIED_PROGRAM
        CLANG_FLAGS ${CLANG_FLAGS}
        IMPALA_FLAGS ${IMPALA_FLAGS}
        FILES ${CONFIG_FILES} alloc_gpu_unified.impala)
    add_executable(alloc_gpu_unified ${ALLOC_GPU_UNIFIED_PROGRAM})
    target_link_libraries(alloc_gpu_unified ${ANYDSL_RUNTIME_LIBRARIES})
    add_test("alloc_gpu_unified" alloc_gpu_unified)

    anydsl_runtime_wrap(RESERVE_SHARED_PROGRAM
        CLANG_FLAGS ${CLANG_FLAGS}
        IMPALA_FLAGS ${IMPALA_FLAGS}
        FILES ${CONFIG_FILES} reserve_shared.impala)
    add_executable(reserve_shared ${RESERVE_SHARED_PROGRAM})
    target_link_libraries(reserve_shared ${ANYDSL_RUNTIME_LIBRARIES})
    add_test("reserve_shared" reserve_shared)

    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
        anydsl_runtime_wrap(HALF_FLOAT_GPU_PROGRAM
            CLANG_FLAGS ${CLANG_FLAGS}
            IMPALA_FLAGS ${IMPALA_FLAGS}
            FILES ${CONFIG_FILES} half_float_gpu.impala)
        add_executable(half_float_gpu ${HALF_FLOAT_GPU_PROGRAM})
        target_link_libraries(half_float_gpu ${ANYDSL_RUNTIME_LIBRARIES})
        add_test("half_float_gpu" half_float_gpu)
    endif()
endif()
