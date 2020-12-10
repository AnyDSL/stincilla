anydsl_runtime_wrap(MEDIAN_PROGRAM
    TARGET_TRIPLE ${ANYDSL_TARGET_TRIPLE}
    TARGET_CPU ${ANYDSL_TARGET_CPU}
    TARGET_FEATURES ${ANYDSL_TARGET_FEATURES}
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala oddeven.impala median.impala)
add_executable(median ${MEDIAN_PROGRAM})
target_link_libraries(median ${ANYDSL_RUNTIME_LIBRARIES})
add_test("median" median)
