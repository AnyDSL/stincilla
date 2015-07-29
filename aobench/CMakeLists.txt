thorin_runtime_wrap(AOBENCH_FILES AOBENCH_LIBS
    BACKEND ${BACKEND}
    FILES ../extern.impala mapping_${DEVICE}.impala ao.impala)
add_executable(aobench main.cpp ${AOBENCH_FILES})
target_link_libraries(aobench ${AOBENCH_LIBS})
add_test("aobench" aobench)
