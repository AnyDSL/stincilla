anydsl_runtime_wrap(STENCIL_INT_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES stencil_dsl.impala)
add_executable(stencil_dsl ${STENCIL_INT_PROGRAM})
target_link_libraries(stencil_dsl ${AnyDSL_runtime_LIBRARIES})
add_test("stencil_dsl" stencil_dsl)
set_target_properties(stencil_dsl PROPERTIES LINKER_LANGUAGE CXX)

if(AnyDSL_runtime_HAS_JIT_SUPPORT)
    add_executable(jit jit.cpp)
    target_link_libraries(jit ${AnyDSL_runtime_IMPALA_JIT_LIBRARIES})
    set_target_properties(jit PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
    add_test("jit" jit)
endif()

if(NOT (BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx"))
    anydsl_runtime_wrap(MULTI_GPU_PROGRAM
        CLANG_FLAGS ${CLANG_FLAGS}
        IMPALA_FLAGS ${IMPALA_FLAGS}
        FILES ../${BACKEND_FILE} ../utils.impala multi_gpu.impala)
    add_executable(multi_gpu ${MULTI_GPU_PROGRAM})
    target_link_libraries(multi_gpu ${AnyDSL_runtime_LIBRARIES})
    add_test("multi_gpu" multi_gpu)

    anydsl_runtime_wrap(ALLOC_GPU_PROGRAM
        CLANG_FLAGS ${CLANG_FLAGS}
        IMPALA_FLAGS ${IMPALA_FLAGS}
        FILES ../${BACKEND_FILE} alloc_gpu.impala)
    add_executable(alloc_gpu ${ALLOC_GPU_PROGRAM})
    target_link_libraries(alloc_gpu ${AnyDSL_runtime_LIBRARIES})
    add_test("alloc_gpu" alloc_gpu)

    if(BACKEND STREQUAL "cuda" OR BACKEND STREQUAL "nvvm")
        anydsl_runtime_wrap(PRINT_GPU_PROGRAM
            CLANG_FLAGS ${CLANG_FLAGS}
            IMPALA_FLAGS ${IMPALA_FLAGS}
            FILES ../${BACKEND_FILE} print_gpu.impala)
        add_executable(print_gpu ${PRINT_GPU_PROGRAM})
        target_link_libraries(print_gpu ${AnyDSL_runtime_LIBRARIES})
        add_test("print_gpu" print_gpu)
        set_target_properties(print_gpu PROPERTIES LINKER_LANGUAGE CXX)
    endif()

    anydsl_runtime_wrap(ALLOC_GPU_UNIFIED_PROGRAM
        CLANG_FLAGS ${CLANG_FLAGS}
        IMPALA_FLAGS ${IMPALA_FLAGS}
        FILES ../${BACKEND_FILE} alloc_gpu_unified.impala)
    add_executable(alloc_gpu_unified ${ALLOC_GPU_UNIFIED_PROGRAM})
    target_link_libraries(alloc_gpu_unified ${AnyDSL_runtime_LIBRARIES})
    add_test("alloc_gpu_unified" alloc_gpu_unified)

    anydsl_runtime_wrap(RESERVE_SHARED_PROGRAM
        CLANG_FLAGS ${CLANG_FLAGS}
        IMPALA_FLAGS ${IMPALA_FLAGS}
        FILES ../${BACKEND_FILE} reserve_shared.impala)
    add_executable(reserve_shared ${RESERVE_SHARED_PROGRAM})
    target_link_libraries(reserve_shared ${AnyDSL_runtime_LIBRARIES})
    add_test("reserve_shared" reserve_shared)

    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
        anydsl_runtime_wrap(HALF_FLOAT_GPU_PROGRAM
            CLANG_FLAGS ${CLANG_FLAGS}
            IMPALA_FLAGS ${IMPALA_FLAGS}
            FILES ../${BACKEND_FILE} half_float_gpu.impala)
        add_executable(half_float_gpu ${HALF_FLOAT_GPU_PROGRAM})
        target_link_libraries(half_float_gpu ${AnyDSL_runtime_LIBRARIES})
        add_test("half_float_gpu" half_float_gpu)
        set_target_properties(half_float_gpu PROPERTIES LINKER_LANGUAGE CXX)
    endif()

    set_target_properties(
        multi_gpu
        alloc_gpu
        reserve_shared
        alloc_gpu_unified
        PROPERTIES LINKER_LANGUAGE CXX)
endif()
