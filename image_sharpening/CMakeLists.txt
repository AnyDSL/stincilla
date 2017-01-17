thorin_runtime_wrap(SHARPENING_PROGRAM
    BACKEND ${BACKEND}
    FILES ../utils.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala sharpening.impala)
add_executable(sharpening main.cpp ${SHARPENING_PROGRAM})
target_link_libraries(sharpening ${THORIN_RUNTIME_LIBRARY} ${THORIN_RUNTIME_LIBRARIES})
set_target_properties(sharpening PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("sharpening" sharpening)
configure_file(goldhill.pgm ${CMAKE_CURRENT_BINARY_DIR}/goldhill.pgm COPYONLY)
