anydsl_runtime_wrap(HARRIS_CORNER_PIPELINED_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ${MAPPING_FILES} mask_${PIXEL_TYPE}.impala harris_corner_pipelined.impala)
add_executable(harris_corner_pipelined main.cpp ${HARRIS_CORNER_PIPELINED_PROGRAM})
target_link_libraries(harris_corner_pipelined ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(harris_corner_pipelined PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("harris_corner_pipelined" harris_corner_pipelined)
configure_file(../common/lena1024.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
