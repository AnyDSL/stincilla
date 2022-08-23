anydsl_runtime_wrap(SHARPENING_PROGRAM
    FRONTEND "artic"
    CLANG_FLAGS ${CLANG_FLAGS}
    ARTIC_FLAGS ${ARTIC_FLAGS}
    FILES ../${BACKEND_FILE} ../utils.impala ../stencil_lib.impala ../sorting_networks/bitonic.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala sharpening.impala)
add_executable(sharpening main.cpp ${SHARPENING_PROGRAM})
target_link_libraries(sharpening ${AnyDSL_runtime_LIBRARIES})
set_target_properties(sharpening PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("sharpening" sharpening)
configure_file(goldhill.pgm ${CMAKE_CURRENT_BINARY_DIR}/goldhill.pgm COPYONLY)
