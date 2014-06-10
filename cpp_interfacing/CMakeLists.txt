THORIN_RUNTIME_WRAP(BILATERAL_FILES BILATERAL_LIBS
	RTTYPE nvvm
	FILES ../extern.impala ../mapping_nvvm.impala bilateral.impala)
add_executable(bilateral main.cpp ${BILATERAL_FILES})
target_link_libraries(bilateral ${BILATERAL_LIBS}) 
