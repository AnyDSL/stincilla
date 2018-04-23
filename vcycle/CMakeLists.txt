anydsl_runtime_wrap(VCYCLE_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${BACKEND_FILE} ${PIXEL_F32_FILE} ../utils.impala ../stencil_lib.impala ../stencil_lib_img_proc.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala vcycle.impala)
add_executable(vcycle main.cpp ${VCYCLE_PROGRAM})
target_link_libraries(vcycle ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(vcycle PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("vcycle" vcycle)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
