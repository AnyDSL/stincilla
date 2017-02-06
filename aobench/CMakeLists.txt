add_test_sample(aobench ${BACKEND}
    CXX main.cpp
    IMPALA ../utils.impala mapping_${DEVICE}.impala aobench.impala)
set_target_properties(aobench PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
