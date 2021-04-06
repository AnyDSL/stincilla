add_stincilla_test(harris_corner main.cpp "../utils.impala;../stencil_lib.impala;../mapping_${DEVICE}.impala;harris_corner.impala")
file(COPY ../common/lena.pgm DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
