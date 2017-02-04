wrap_impala_sources(HARRIS_CORNER_PROGRAM
    BACKEND ${BACKEND}
    FILES ../utils.impala ../mapping_${DEVICE}.impala harris_corner.impala)
add_executable(harris_corner main.cpp ${HARRIS_CORNER_PROGRAM})
target_link_libraries(harris_corner ${IMPALA_RUNTIME_LIBRARIES})
set_target_properties(harris_corner PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("harris_corner" harris_corner)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
