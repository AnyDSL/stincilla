cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(DSL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(APPS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# mapping
if(BACKEND STREQUAL "aocl" OR BACKEND STREQUAL "hls")
    set(DEVICE "fpga")
    set(DEVICE_SPECIFIC_FILES ${DSL_SOURCE_DIR}/mapping_fpga_img_${BACKEND}.impala ${DSL_SOURCE_DIR}/stencil_lib_img_fpga.impala)
    set(DISABLE_PIPELINE_DEVICE_SPECIFIC_FILES ${DSL_SOURCE_DIR}/mapping_fpga_img_proc_${BACKEND}.impala ${DSL_SOURCE_DIR}/mapping_proc_img.impala ${DSL_SOURCE_DIR}/stencil_lib_img_proc.impala)
else()
    if(BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx")
        set(DEVICE "cpu")
    else()
        set(DEVICE "acc")
    endif()
    set(DEVICE_SPECIFIC_FILES ${DSL_SOURCE_DIR}/mapping_proc_img.impala ${DSL_SOURCE_DIR}/stencil_lib_img_proc.impala)
    set(DISABLE_PIPELINE_DEVICE_SPECIFIC_FILES ${DEVICE_SPECIFIC_FILES})
endif()

#set(BACKEND_FILE ${DSL_SOURCE_DIR}/backend_${BACKEND}.impala)
set(MAPPING_FILE ${DSL_SOURCE_DIR}/mapping_${DEVICE}.impala)
set(DSL_FILES ${DSL_SOURCE_DIR}/utils.impala ${DSL_SOURCE_DIR}/stencil_lib.impala)
set(PIXEL_TYPE_FILE ${DSL_SOURCE_DIR}/pixel_${PIXEL_TYPE}.impala)
set(PIXEL_TYPE_FLOAT_FILE ${DSL_SOURCE_DIR}/pixel_f32.impala)
set(PIXEL_TYPE_UCHAR_FILE ${DSL_SOURCE_DIR}/pixel_u8.impala)

# common DSL files for all applications applications
set(COMMON_FILES ${DSL_FILES} ${DEVICE_SPECIFIC_FILES} ${BACKEND_FILE} ${PIXEL_TYPE_FILE} ${MAPPING_FILE})
set(COMMON_FILES_F32 ${DSL_FILES} ${DEVICE_SPECIFIC_FILES} ${BACKEND_FILE} ${PIXEL_TYPE_FLOAT_FILE} ${MAPPING_FILE})
set(COMMON_FILES_U8  ${DSL_FILES} ${DEVICE_SPECIFIC_FILES} ${BACKEND_FILE} ${PIXEL_TYPE_UCHAR_FILE} ${MAPPING_FILE})
set(COMMON_DISABLE_PIPELINE_FILES_F32 ${DSL_FILES} ${DISABLE_PIPELINE_DEVICE_SPECIFIC_FILES} ${BACKEND_FILE} ${PIXEL_TYPE_FLOAT_FILE} ${MAPPING_FILE})
set(COMMON_DISABLE_PIPELINE_FILES     ${DSL_FILES} ${DISABLE_PIPELINE_DEVICE_SPECIFIC_FILES} ${BACKEND_FILE} ${PIXEL_TYPE_FILE} ${MAPPING_FILE})

# application sources and benchmarks 
set (GAUSSIAN_DIR       ${APPS_DIR}/gaussian)
set (JACOBI_DIR         ${APPS_DIR}/jacobi)
set (BILATERAL_DIR      ${APPS_DIR}/bilateral)
set (BOX_FILTER_DIR     ${APPS_DIR}/box_filter)
set (FILTER_CHAIN_DIR   ${APPS_DIR}/filter_chain)
set (HARRIS_CORNER_DIR  ${APPS_DIR}/harris_corner)

set(BILATERAL_FILES     ${BILATERAL_DIR}/bilateral.impala)
set(BOX_FILTER_FILES    ${BOX_FILTER_DIR}/box_filter.impala)
set(BOX_FILTER_CONST_FILES ${BOX_FILTER_DIR}/box_filter_const.impala)
set(GAUSSIAN_FILES      ${GAUSSIAN_DIR}/mask_${PIXEL_TYPE}.impala ${GAUSSIAN_DIR}/gaussian.impala)
set(JACOBI_FILES        ${JACOBI_DIR}/mask_${PIXEL_TYPE}.impala ${JACOBI_DIR}/jacobi.impala)
set(FILTER_CHAIN_FILES  ${FILTER_CHAIN_DIR}/mask_${PIXEL_TYPE}.impala ${FILTER_CHAIN_DIR}/filter_chain.impala)
set(HARRIS_CORNER_FILES ${HARRIS_CORNER_DIR}/mask_${PIXEL_TYPE}.impala ${HARRIS_CORNER_DIR}/harris_corner.impala)

# for optional config files
set(APPS_CONFIG_FILES "")

anydsl_runtime_wrap(BILATERAL_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${APPS_CONFIG_FILES} ${COMMON_FILES_F32} ${BILATERAL_FILES})
add_executable(bilateral ${BILATERAL_PROGRAM})
target_link_libraries(bilateral ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("bilateral" bilateral)

anydsl_runtime_wrap(BOX_FILTER_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${APPS_CONFIG_FILES} ${COMMON_FILES} ${BOX_FILTER_FILES})
add_executable(box_filter ${BOX_FILTER_PROGRAM})
target_link_libraries(box_filter ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("box_filter" box_filter)

anydsl_runtime_wrap(GAUSSIAN_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${APPS_CONFIG_FILES} ${COMMON_FILES} ${GAUSSIAN_FILES})
add_executable(gaussian ${GAUSSIAN_PROGRAM})
target_link_libraries(gaussian ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("gaussian" gaussian)

anydsl_runtime_wrap(JACOBI_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${APPS_CONFIG_FILES} ${COMMON_FILES} ${JACOBI_FILES})
add_executable(jacobi ${JACOBI_PROGRAM})
target_link_libraries(jacobi ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("jacobi" jacobi)

anydsl_runtime_wrap(FILTER_CHAIN_PIPE_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${APPS_CONFIG_FILES} ${COMMON_FILES} ${FILTER_CHAIN_FILES})
add_definitions(-DSTINCILLA_DATA_TYPE=${STINCILLA_DATA_TYPE})
add_executable(filter_chain_pipe ${FILTER_CHAIN_PIPE_PROGRAM})
target_link_libraries(filter_chain_pipe ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(filter_chain_pipe PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

anydsl_runtime_wrap(HARRIS_CORNER_PIPE_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${APPS_CONFIG_FILES} ${COMMON_FILES} ${HARRIS_CORNER_FILES})
add_definitions(-DSTINCILLA_DATA_TYPE=${STINCILLA_DATA_TYPE})
add_executable(harris_corner_pipe "${HARRIS_CORNER_DIR}/main.cpp" ${HARRIS_CORNER_PIPE_PROGRAM})
target_link_libraries(harris_corner_pipe ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(harris_corner_pipe PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

anydsl_runtime_wrap(FILTER_CHAIN_PROC_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${APPS_CONFIG_FILES} ${COMMON_DISABLE_PIPELINE_FILES} ${FILTER_CHAIN_FILES})
add_definitions(-DSTINCILLA_DATA_TYPE=${STINCILLA_DATA_TYPE})
add_executable(filter_chain_proc ${FILTER_CHAIN_PROC_PROGRAM})
target_link_libraries(filter_chain_proc ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(filter_chain_proc PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

anydsl_runtime_wrap(HARRIS_CORNER_PROC_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${APPS_CONFIG_FILES} ${COMMON_DISABLE_PIPELINE_FILES} ${HARRIS_CORNER_FILES})
add_definitions(-DSTINCILLA_DATA_TYPE=${STINCILLA_DATA_TYPE})
add_executable(harris_corner_proc "${HARRIS_CORNER_DIR}/main.cpp" ${HARRIS_CORNER_PROC_PROGRAM})
target_link_libraries(harris_corner_proc ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(harris_corner_proc PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
