wrap_impala_sources(VCYCLE_PROGRAM
    BACKEND ${BACKEND}
    FILES ../utils.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala vcycle.impala)
add_executable(vcycle main.cpp ${VCYCLE_PROGRAM})
target_link_libraries(vcycle ${IMPALA_RUNTIME_LIBRARIES})
set_target_properties(vcycle PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("vcycle" vcycle)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
