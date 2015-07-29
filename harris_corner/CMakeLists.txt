thorin_runtime_wrap(HARRIS_CORNER_FILES HARRIS_CORNER_LIBS
    BACKEND ${BACKEND}
    FILES ../extern.impala ../mapping_${DEVICE}.impala harris_corner.impala)
add_executable(harris_corner main.cpp ${HARRIS_CORNER_FILES})
target_link_libraries(harris_corner ${HARRIS_CORNER_LIBS})
add_test("harris_corner" harris_corner)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
