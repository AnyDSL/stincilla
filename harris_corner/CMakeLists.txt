add_test_sample(harris_corner
    CXX main.cpp
    IMPALA ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala harris_corner.impala)
set_target_properties(harris_corner PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
