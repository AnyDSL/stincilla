add_stincilla_test(vcycle main.cpp
    "../utils.impala;../stencil_lib.impala;../mapping_${DEVICE}.impala;mapping_${DEVICE}.impala;vcycle.impala")
file(COPY ../common/lena.pgm DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
