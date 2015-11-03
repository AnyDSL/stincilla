thorin_runtime_wrap(BILATERAL_GRID_PROGRAM
    BACKEND ${BACKEND}
    FILES ../utils.impala mapping_${DEVICE}.impala bilateral_grid.impala)
add_executable(bilateral_grid main.cpp ${BILATERAL_GRID_PROGRAM})
target_link_libraries(bilateral_grid ${THORIN_RUNTIME_LIBRARY} ${THORIN_RUNTIME_LIBRARIES})
add_test("bilateral_grid" bilateral_grid)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
