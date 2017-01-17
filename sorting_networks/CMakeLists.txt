runtime_wrap(MEDIAN_PROGRAM
    BACKEND ${BACKEND}
    FILES ../utils.impala mapping_${DEVICE}.impala oddeven.impala median.impala)
add_executable(median ${MEDIAN_PROGRAM})
target_link_libraries(median ${RUNTIME_LIBRARY} ${RUNTIME_LIBRARIES})
add_test("median" median)
