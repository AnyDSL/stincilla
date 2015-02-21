THORIN_RUNTIME_WRAP(MEDIAN_FILES MEDIAN_LIBS
    BACKEND ${BACKEND}
    FILES ../extern.impala mapping_${DEVICE}.impala oddeven.impala median.impala)
add_executable(median main.cpp ${MEDIAN_FILES})
target_link_libraries(median ${MEDIAN_LIBS})
add_test("median" median)
