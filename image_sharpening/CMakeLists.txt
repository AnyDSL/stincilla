add_stincilla_test(sharpening main.cpp
    "../utils.impala;../stencil_lib.impala;../sorting_networks/bitonic.impala;../mapping_${DEVICE}.impala;mapping_${DEVICE}.impala;stencil_lib_i16.impala;sharpening.impala")
file(COPY goldhill.pgm DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
