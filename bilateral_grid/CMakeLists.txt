THORIN_RUNTIME_WRAP(BILATERAL_GRID_FILES BILATERAL_GRID_LIBS
    BACKEND ${BACKEND}
    FILES ../extern.impala bilateral_grid.impala)
add_executable(bilateral_grid main.cpp ${BILATERAL_GRID_FILES})
target_link_libraries(bilateral_grid ${BILATERAL_GRID_LIBS})
add_test("bilateral_grid" bilateral_grid)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
