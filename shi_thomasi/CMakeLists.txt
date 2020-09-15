if(NOT PIXEL_TYPE STREQUAL "u8")
    anydsl_runtime_wrap(SHI_THOMASI_PROGRAM
        CLANG_FLAGS ${CLANG_FLAGS}
        IMPALA_FLAGS ${IMPALA_FLAGS}
        FILES ${CONFIG_FILES} ../utils.impala ../stencil_lib.impala ../stencil_lib_img_proc.impala ${MAPPING_FILES} mask_${PIXEL_TYPE}.impala shi_thomasi.impala)
    add_executable(shi_thomasi main.cpp ${SHI_THOMASI_PROGRAM})
    target_link_libraries(shi_thomasi ${ANYDSL_RUNTIME_LIBRARIES})
    set_target_properties(shi_thomasi PROPERTIES COMPILE_FLAGS -DSTINCILLA_DATA_TYPE=${STINCILLA_DATA_TYPE})
    set_target_properties(shi_thomasi PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
    add_test("SH_THOMASI" SHI_THOMASI)
    configure_file(../common/lena.pgm ${CMAKE_CURRENT_BINARY_DIR}/lena.pgm COPYONLY)
endif()
