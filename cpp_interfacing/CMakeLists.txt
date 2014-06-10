THORIN_RUNTIME_WRAP(BILATERAL_FILES BILATERAL_LIBS
	RTTYPE cpu
	FILES ../extern.impala ../mapping_cpu.impala bilateral.impala)
add_executable(bilateral main.cpp ${BILATERAL_FILES})
target_link_libraries(bilateral ${BILATERAL_LIBS}) 
