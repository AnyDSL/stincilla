cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(STINCILLA CXX)
enable_testing()

find_package(AnyDSL-runtime REQUIRED)
include(${ANYDSL_RUNTIME_CMAKE_DIR}/Runtime.cmake)
include_directories(${ANYDSL_RUNTIME_DIR}/src)

set(BACKEND ${BACKEND} CACHE STRING "select the backend from the following: CPU, AVX, NVVM, CUDA, OPENCL, AMDGPU, AOCL, HLS")
if(NOT BACKEND)
    set(BACKEND cpu CACHE STRING "select the backend from the following: CPU, AVX, NVVM, CUDA, OPENCL, AMDGPU, AOCL, HLS" FORCE)
endif()
string(TOLOWER "${BACKEND}" BACKEND)
message(STATUS "Selected backend: ${BACKEND}")
set(PIXEL_TYPE ${PIXEL_TYPE} CACHE STRING "select the pixel type from the following: f32, i32, u8")
if(NOT PIXEL_TYPE)
    set(PIXEL_TYPE f32 CACHE STRING "select the pixel type from the following: f32, i32, u8" FORCE)
endif()
string(TOLOWER "${PIXEL_TYPE}" PIXEL_TYPE)
message(STATUS "Selected pixel type: ${PIXEL_TYPE}")
if(PIXEL_TYPE STREQUAL "i32")
    set(STINCILLA_DATA_TYPE int)
elseif(PIXEL_TYPE STREQUAL "u8")
    set(STINCILLA_DATA_TYPE uchar)
else()
    set(STINCILLA_DATA_TYPE float)
endif()

set(BACKEND_FILE ${CMAKE_CURRENT_SOURCE_DIR}/backend_${BACKEND}.impala)
set(PIXEL_TYPE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pixel_${PIXEL_TYPE}.impala)

if(BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx")
    set(DEVICE "cpu")
    set(MAPPING_FILES ${CMAKE_CURRENT_SOURCE_DIR}/mapping_${DEVICE}.impala)
elseif(BACKEND STREQUAL "aocl" OR BACKEND STREQUAL "hls")
    set(DEVICE "fpga")
    if(BACKEND STREQUAL "hls")
        set(MAPPING_FILES ${CMAKE_CURRENT_SOURCE_DIR}/mapping_${DEVICE}.impala ${CMAKE_CURRENT_SOURCE_DIR}/mapping_fpga_img_proc_hls.impala)
    else()
        set(MAPPING_FILES ${CMAKE_CURRENT_SOURCE_DIR}/mapping_${DEVICE}.impala ${CMAKE_CURRENT_SOURCE_DIR}/mapping_fpga_img_proc_aocl.impala)
    endif()
else()
    set(DEVICE "acc")
    set(MAPPING_FILES ${CMAKE_CURRENT_SOURCE_DIR}/mapping_${DEVICE}.impala)
endif()


set(CLANG_FLAGS -march=native)
set(IMPALA_FLAGS --log-level info)

set(STINCILLA_COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/common/pnm_image)
include_directories(${STINCILLA_COMMON_INCLUDE_DIRS})

#add_subdirectory(aobench)
#add_subdirectory(bilateral_grid)
#add_subdirectory(halide)
add_subdirectory(test)
#add_subdirectory(image_sharpening)
#add_subdirectory(sorting_networks)
#add_subdirectory(vcycle)
add_subdirectory(apps)
add_subdirectory(harris_corner)

set(DSL_TYPE_FILES utils.impala stencil_lib.impala stencil_lib_img_proc.impala)

# #simple CPU-based examples
# anydsl_runtime_wrap(MATMUL_PROGRAM
#     CLANG_FLAGS ${CLANG_FLAGS}
#     IMPALA_FLAGS ${IMPALA_FLAGS}
#     FILES ${BACKEND_FILE} utils.impala matmul.impala)
# add_executable(matmul ${MATMUL_PROGRAM})
# target_link_libraries(matmul ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
# add_test("matmul" matmul)
