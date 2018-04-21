anydsl_runtime_wrap(MEDIAN_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${CONFIG_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala oddeven.impala median.impala)
add_executable(median ${MEDIAN_PROGRAM})
target_link_libraries(median ${ANYDSL_RUNTIME_LIBRARIES})
add_test("median" median)
