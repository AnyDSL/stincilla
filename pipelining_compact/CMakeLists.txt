if(BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx")
    set(DEVICE "cpu")
    set(THIS_MAPPING_FILES ../stencil_lib_img.impala mapping_proc_pipeline.impala)
elseif(BACKEND STREQUAL "aocl" OR BACKEND STREQUAL "hls")
    set(DEVICE "fpga")
    set(THIS_MAPPING_FILES stencil_lib_img_fpga.impala mapping_fpga_pipeline.impala)
else()
    set(DEVICE "acc")
    set(THIS_MAPPING_FILES ../stencil_lib_img.impala mapping_proc_pipeline.impala)
endif()

set(DSL_TYPE_FILES ../utils.impala ../stencil_lib.impala)
set(MAPPING_TYPE_FILES ../mapping_${DEVICE}.impala  ${THIS_MAPPING_FILES})

anydsl_runtime_wrap(HARRIS_CORNER_PIP_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ${DSL_TYPE_FILES} ${MAPPING_TYPE_FILES} mask_${PIXEL_TYPE}.impala harris_corner_pip.impala)
add_executable(harris_corner_pip main.cpp ${HARRIS_CORNER_PIP_PROGRAM})
target_link_libraries(harris_corner_pip ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(harris_corner_pip PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("harris_corner_pip" harris_corner_pip)

anydsl_runtime_wrap(FILTER_CHAIN_PIP_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ${DSL_TYPE_FILES} ${MAPPING_TYPE_FILES} filter_chain_pip.impala)
add_executable(filter_chain_pip ${FILTER_CHAIN_PIP_PROGRAM})
target_link_libraries(filter_chain_pip ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("filter_chain_pip" filter_chain_pip)

anydsl_runtime_wrap(GAUSSIAN_PIP_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ${DSL_TYPE_FILES} ${MAPPING_TYPE_FILES} gaussian_pip.impala)
add_executable(gaussian_pip ${GAUSSIAN_PIP_PROGRAM})
target_link_libraries(gaussian_pip ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("gaussian_pip" gaussian_pip)
