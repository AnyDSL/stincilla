thorin_runtime_wrap(HARRIS_CORNER_PROGRAM
    BACKEND ${BACKEND}
    FILES ../utils.impala ../mapping_${DEVICE}.impala harris_corner.impala)
if(NOT MSVC)
    set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS "-std=c++11")
endif()
add_executable(harris_corner main.cpp ${HARRIS_CORNER_PROGRAM})
target_link_libraries(harris_corner ${THORIN_RUNTIME_LIBRARY} ${THORIN_RUNTIME_LIBRARIES})
add_test("harris_corner" harris_corner)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
