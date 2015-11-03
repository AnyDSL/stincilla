thorin_runtime_wrap(VCYCLE_PROGRAM
    BACKEND ${BACKEND}
    FILES ../utils.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala vcycle.impala)
add_executable(vcycle main.cpp ${VCYCLE_PROGRAM})
target_link_libraries(vcycle ${THORIN_RUNTIME_LIBRARY} ${THORIN_RUNTIME_LIBRARIES})
add_test("vcycle" vcycle)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
