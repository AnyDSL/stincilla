add_stincilla_test(bilateral_grid main.cpp "../utils.impala;mapping_${DEVICE}.impala;bilateral_grid.impala")
file(COPY ../common/lena.pgm DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
