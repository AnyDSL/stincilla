anydsl_runtime_wrap(HARRIS_CORNER_PROGRAM
    FRONTEND "artic"
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala harris_corner.impala)
add_executable(harris_corner main.cpp ${HARRIS_CORNER_PROGRAM})
target_link_libraries(harris_corner ${AnyDSL_runtime_LIBRARIES})
set_target_properties(harris_corner PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("harris_corner" harris_corner)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
