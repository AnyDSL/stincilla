add_test_sample(vcycle ${BACKEND}
    CXX main.cpp
    IMPALA ../utils.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala vcycle.impala)
set_target_properties(vcycle PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
