thorin_runtime_wrap(VCYCLE_FILES VCYCLE_LIBS
    BACKEND ${BACKEND}
    FILES ../extern.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala vcycle.impala)
add_executable(vcycle main.cpp ${VCYCLE_FILES})
target_link_libraries(vcycle ${VCYCLE_LIBS})
add_test("vcycle" vcycle)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
