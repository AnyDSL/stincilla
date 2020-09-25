if(DEVICE STREQUAL "cpu")
    set(DUMMY_BACKEND dummy_gpu.impala)
endif()

anydsl_runtime_wrap(HALIDE_BLUR_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../utils.impala ${DUMMY_BACKEND} schedule.impala blur.impala)
add_executable(blur main.cpp ${HALIDE_BLUR_PROGRAM})
target_link_libraries(blur ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(blur PROPERTIES COMPILE_FLAGS -DSTINCILLA_DATA_TYPE=int)
set_target_properties(blur PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("blur" blur)

anydsl_runtime_wrap(HALIDE_HARRIS_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../utils.impala ${DUMMY_BACKEND} schedule.impala harris.impala)
add_executable(harris main.cpp ${HALIDE_HARRIS_PROGRAM})
target_link_libraries(harris ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(harris PROPERTIES COMPILE_FLAGS -DSTINCILLA_DATA_TYPE=float)
set_target_properties(harris PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("harris" harris)

anydsl_runtime_wrap(HALIDE_SIMPLE_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../utils.impala ${DUMMY_BACKEND} simple.impala)
add_executable(simple main.cpp ${HALIDE_SIMPLE_PROGRAM})
target_link_libraries(simple ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(simple PROPERTIES COMPILE_FLAGS -DSTINCILLA_DATA_TYPE=int)
set_target_properties(simple PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_test("simple" simple)

configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
configure_file(../common/square.pgm ${CMAKE_CURRENT_BINARY_DIR}/square.pgm COPYONLY)
