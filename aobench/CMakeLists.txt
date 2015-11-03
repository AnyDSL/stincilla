thorin_runtime_wrap(AOBENCH_PROGRAM
    BACKEND ${BACKEND}
    FILES ../utils.impala mapping_${DEVICE}.impala aobench.impala)
add_executable(aobench main.cpp ${AOBENCH_PROGRAM})
target_link_libraries(aobench ${THORIN_RUNTIME_LIBRARY} ${THORIN_RUNTIME_LIBRARIES})
add_test("aobench" aobench)
