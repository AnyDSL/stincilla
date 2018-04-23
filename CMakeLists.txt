cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

project(STINCILLA CXX)
enable_testing()

find_package(AnyDSL_runtime REQUIRED)
include_directories(${AnyDSL_runtime_INCLUDE_DIRS})

set(BACKEND ${BACKEND} CACHE STRING "select the backend from the following: CPU, AVX, NVVM, CUDA, OPENCL, AMDGPU")
if(NOT BACKEND)
    set(BACKEND cpu CACHE STRING "select the backend from the following: CPU, AVX, NVVM, CUDA, OPENCL, AMDGPU" FORCE)
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

set(BACKEND_FILE    ${CMAKE_CURRENT_SOURCE_DIR}/backend_${BACKEND}.impala)
set(PIXEL_TYPE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/pixel_${PIXEL_TYPE}.impala)
set(PIXEL_U8_FILE   ${CMAKE_CURRENT_SOURCE_DIR}/pixel_u8.impala)
set(PIXEL_I32_FILE  ${CMAKE_CURRENT_SOURCE_DIR}/pixel_i32.impala)
set(PIXEL_F32_FILE  ${CMAKE_CURRENT_SOURCE_DIR}/pixel_f32.impala)
set(CONFIG_FILES ${BACKEND_FILE} ${PIXEL_TYPE_FILE})

if(BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx")
    set(DEVICE "cpu")
else()
    set(DEVICE "acc")
endif()

set(CLANG_FLAGS -march=native)
set(IMPALA_FLAGS --log-level info)
set(ANYDSL_RUNTIME_LIBRARIES ${AnyDSL_runtime_LIBRARIES})

set(STINCILLA_COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/common/pnm_image)
include_directories(${STINCILLA_COMMON_INCLUDE_DIRS})

add_subdirectory(aobench)
add_subdirectory(bilateral_grid)
add_subdirectory(halide)
add_subdirectory(harris_corner)
add_subdirectory(test)
add_subdirectory(image_sharpening)
add_subdirectory(sorting_networks)
add_subdirectory(vcycle)

# simple CPU-based examples
anydsl_runtime_wrap(MATMUL_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${BACKEND_FILE} ${PIXEL_F32_FILE} utils.impala matmul.impala)
add_executable(matmul ${MATMUL_PROGRAM})
target_link_libraries(matmul ${ANYDSL_RUNTIME_LIBRARIES})
add_test("matmul" matmul)

# examples based on the "mapping"
anydsl_runtime_wrap(GAUSSIAN_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${CONFIG_FILES} utils.impala stencil_lib.impala mapping_${DEVICE}.impala gaussian.impala)
add_executable(gaussian ${GAUSSIAN_PROGRAM})
target_link_libraries(gaussian ${ANYDSL_RUNTIME_LIBRARIES})
add_test("gaussian" gaussian)

anydsl_runtime_wrap(BILATERAL_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${BACKEND_FILE} ${PIXEL_F32_FILE} utils.impala stencil_lib.impala mapping_${DEVICE}.impala bilateral.impala)
add_executable(bilateral ${BILATERAL_PROGRAM})
target_link_libraries(bilateral ${ANYDSL_RUNTIME_LIBRARIES})
add_test("bilateral" bilateral)

anydsl_runtime_wrap(JACOBI_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${CONFIG_FILES} utils.impala stencil_lib.impala mapping_${DEVICE}.impala jacobi.impala)
add_executable(jacobi ${JACOBI_PROGRAM})
target_link_libraries(jacobi ${ANYDSL_RUNTIME_LIBRARIES})
add_test("jacobi" jacobi)
