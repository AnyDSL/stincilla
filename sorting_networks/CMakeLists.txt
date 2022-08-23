anydsl_runtime_wrap(MEDIAN_PROGRAM
    FRONTEND "artic"
    CLANG_FLAGS ${CLANG_FLAGS}
    ARTIC_FLAGS ${ARTIC_FLAGS}
    FILES ../${BACKEND_FILE} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala oddeven.impala median.impala)
add_executable(median ${MEDIAN_PROGRAM})
target_link_libraries(median ${AnyDSL_runtime_LIBRARIES})
add_test("median" median)
