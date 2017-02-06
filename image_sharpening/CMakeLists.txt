add_test_sample(sharpening ${BACKEND}
    CXX main.cpp
    IMPALA ../utils.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala sharpening.impala)
set_target_properties(sharpening PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
configure_file(goldhill.pgm ${CMAKE_CURRENT_BINARY_DIR}/goldhill.pgm COPYONLY)
