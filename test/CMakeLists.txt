# simple CPU-based examples
thorin_runtime_wrap(STENCIL_INT_FILES STENCIL_INT_LIBS
    BACKEND cpu
    MAIN
    FILES stencil_int.impala)
add_executable(stencil_int ${STENCIL_INT_FILES})
target_link_libraries(stencil_int ${STENCIL_INT_LIBS}) 
add_test("stencil_int" stencil_int)

if(NOT (BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx"))
    thorin_runtime_wrap(MULTI_GPU_FILES MULTI_GPU_LIBS
        BACKEND ${BACKEND}
        MAIN
        FILES ../extern.impala multi_gpu.impala)
    add_executable(multi_gpu ${MULTI_GPU_FILES})
    target_link_libraries(multi_gpu ${MULTI_GPU_LIBS})
    add_test("multi_gpu" multi_gpu)
endif()
