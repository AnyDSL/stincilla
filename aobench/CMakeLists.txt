THORIN_RUNTIME_WRAP(AOBENCH_FILES AOBENCH_LIBS
	RTTYPE ${RTTYPE}
	FILES ../extern.impala mapping_${DEVICE}.impala ao.impala)
add_executable(aobench main.cpp ${AOBENCH_FILES})
target_link_libraries(aobench ${AOBENCH_LIBS})
add_test("aobench" aobench)
