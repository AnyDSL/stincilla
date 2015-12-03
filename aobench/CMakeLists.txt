thorin_runtime_wrap(AOBENCH_FILES AOBENCH_LIBS
    BACKEND ${BACKEND}
    FILES ../utils.impala mapping_${DEVICE}.impala ao.impala)
if(NOT MSVC)
    set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS "-std=c++11")
endif()
add_executable(aobench main.cpp ${AOBENCH_FILES})
target_link_libraries(aobench ${AOBENCH_LIBS})
add_test("aobench" aobench)
