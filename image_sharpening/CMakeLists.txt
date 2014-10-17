THORIN_RUNTIME_WRAP(SHARPENING_FILES SHARPENING_LIBS
	RTTYPE ${RTTYPE}
	FILES ../extern.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala sharpening.impala)
add_executable(sharpening main.cpp ${SHARPENING_FILES})
target_link_libraries(sharpening ${SHARPENING_LIBS})
add_test("sharpening" sharpening)
configure_file(goldhill.pgm ${CMAKE_CURRENT_BINARY_DIR}/goldhill.pgm COPYONLY)
