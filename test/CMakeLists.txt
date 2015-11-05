thorin_runtime_wrap(STENCIL_INT_PROGRAM
    BACKEND cpu
    FILES stencil_int.impala)
add_executable(stencil_int ${STENCIL_INT_PROGRAM})
target_link_libraries(stencil_int ${THORIN_RUNTIME_LIBRARY} ${THORIN_RUNTIME_LIBRARIES})
add_test("stencil_int" stencil_int)

if(NOT (BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx"))
    thorin_runtime_wrap(MULTI_GPU_PROGRAM
        BACKEND ${BACKEND}
        FILES ../utils.impala multi_gpu.impala)
    add_executable(multi_gpu ${MULTI_GPU_PROGRAM})
    target_link_libraries(multi_gpu ${THORIN_RUNTIME_LIBRARY} ${THORIN_RUNTIME_LIBRARIES})
    add_test("multi_gpu" multi_gpu)

    thorin_runtime_wrap(ALLOC_GPU_PROGRAM
        BACKEND ${BACKEND}
        FILES alloc_gpu.impala)
    add_executable(alloc_gpu ${ALLOC_GPU_PROGRAM})
    target_link_libraries(alloc_gpu ${THORIN_RUNTIME_LIBRARY} ${THORIN_RUNTIME_LIBRARIES})
    add_test("alloc_gpu" alloc_gpu)
endif()
