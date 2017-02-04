wrap_impala_sources(MEDIAN_PROGRAM
    BACKEND ${BACKEND}
    FILES ../utils.impala mapping_${DEVICE}.impala oddeven.impala median.impala)
add_executable(median ${MEDIAN_PROGRAM})
target_link_libraries(median ${IMPALA_RUNTIME_LIBRARIES})
add_test("median" median)
