anydsl_runtime_wrap(HALIDE_BLUR_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../utils.impala blur.impala)
add_executable(blur blur.cpp ${HALIDE_BLUR_PROGRAM})
target_link_libraries(blur ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("blur" blur)
configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
