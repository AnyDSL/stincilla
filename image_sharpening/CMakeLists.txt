anydsl_runtime_wrap(SHARPENING_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../utils.impala ../stencil_lib.impala ../sorting_networks/bitonic.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala stencil_lib_i16.impala sharpening.impala)
add_executable(sharpening main.cpp ${SHARPENING_PROGRAM})
target_link_libraries(sharpening ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(sharpening PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("sharpening" sharpening)
configure_file(goldhill.pgm ${CMAKE_CURRENT_BINARY_DIR}/goldhill.pgm COPYONLY)
