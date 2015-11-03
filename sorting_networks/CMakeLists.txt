thorin_runtime_wrap(MEDIAN_PROGRAM
    BACKEND ${BACKEND}
    FILES ../utils.impala mapping_${DEVICE}.impala oddeven.impala median.impala)
add_executable(median main.cpp ${MEDIAN_PROGRAM})
target_link_libraries(median ${THORIN_RUNTIME_LIBRARY} ${THORIN_RUNTIME_LIBRARIES})
add_test("median" median)
