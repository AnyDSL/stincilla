if(BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx")
    set(DEVICE "cpu")
    set(THIS_MAPPING_FILES mapping_proc_virtual_img.impala)
elseif(BACKEND STREQUAL "aocl" OR BACKEND STREQUAL "hls")
    set(DEVICE "fpga")
    if(BACKEND STREQUAL "hls")
        set(THIS_MAPPING_FILES mapping_fpga_virtual_img_hls.impala ../mapping_fpga_img_hls.impala)
    else()
        set(THIS_MAPPING_FILES mapping_fpga_virtual_img.impala ../mapping_fpga_img.impala)
    endif()
else()
    set(DEVICE "acc")
    set(THIS_MAPPING_FILES mapping_proc_virtual_img.impala)
endif()

set(DSL_TYPE_FILES ../utils.impala ../stencil_lib.impala ../stencil_lib_img.impala)
set(MAPPING_TYPE_FILES ../mapping_${DEVICE}.impala  ${THIS_MAPPING_FILES})

anydsl_runtime_wrap(HARRIS_CORNER_PIPELINE_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ${DSL_TYPE_FILES} ${MAPPING_TYPE_FILES} mask_${PIXEL_TYPE}.impala harris_corner_pipeline.impala)
add_executable(harris_corner_pipeline main.cpp ${HARRIS_CORNER_PIPELINE_PROGRAM})
target_link_libraries(harris_corner_pipeline ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(harris_corner_pipeline PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("harris_corner_pipeline" harris_corner_pipeline)

anydsl_runtime_wrap(FILTER_CHAIN_PIPELINE_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ${DSL_TYPE_FILES} ${MAPPING_TYPE_FILES} filter_chain_pipeline.impala)
add_executable(filter_chain_pipeline ${FILTER_CHAIN_PIPELINE_PROGRAM})
target_link_libraries(filter_chain_pipeline ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("filter_chain_pipeline" filter_chain_pipeline)

anydsl_runtime_wrap(GAUSSIAN_PIPELINE_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ${DSL_TYPE_FILES} ${MAPPING_TYPE_FILES} gaussian_pipeline.impala)
add_executable(gaussian_pipeline ${GAUSSIAN_PIPELINE_PROGRAM})
target_link_libraries(gaussian_pipeline ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("gaussian_pipeline" gaussian_pipeline)
