THORIN_RUNTIME_WRAP(STENCIL_INT_FILES STENCIL_INT_LIBS
	RTTYPE plain
	MAIN
	FILES stencil_int.impala)
message("Files: ${STENCIL_INT_FILES}, Libs: ${STENCIL_INT_LIBS}")
add_executable(stencil_int ${STENCIL_INT_FILES})
target_link_libraries(stencil_int ${STENCIL_INT_LIBS}) 
