THORIN_RUNTIME_WRAP(BILATERAL_FILES BILATERAL_LIBS
	RTTYPE ${RTTYPE}
	FILES ../extern.impala ../mapping_${DEVICE}.impala bilateral.impala)
add_executable(cpp_bilateral main.cpp ${BILATERAL_FILES})
target_link_libraries(cpp_bilateral ${BILATERAL_LIBS})
add_test("cpp_bilateral" cpp_bilateral "${CMAKE_CURRENT_SOURCE_DIR}/lena.pgm")
