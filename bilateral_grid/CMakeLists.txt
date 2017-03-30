add_test_sample(bilateral_grid
    CXX main.cpp
    IMPALA ../utils.impala mapping_${DEVICE}.impala bilateral_grid.impala)
set_target_properties(bilateral_grid PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
