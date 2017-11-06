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
set(PIXEL_TYPE ${PIXEL_TYPE} CACHE STRING "select the pixel type from the following: f32, i32")
if(NOT PIXEL_TYPE)
    set(PIXEL_TYPE f32 CACHE STRING "select the pixel type from the following: f32, i32" FORCE)
endif()
string(TOLOWER "${PIXEL_TYPE}" PIXEL_TYPE)
message(STATUS "Selected pixel type: ${PIXEL_TYPE}")

set(BACKEND_FILE backend_${BACKEND}.impala)
set(PIXEL_TYPE_FILES pixel_${PIXEL_TYPE}.impala)

if(BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx")
    set(DEVICE "cpu")
elseif(BACKEND STREQUAL "aocl" OR BACKEND STREQUAL "hls")
    set(DEVICE "fpga")
    if(BACKEND STREQUAL "aocl")
        set(BACKEND_FILE backend_opencl.impala)
    endif()
else()
    set(DEVICE "acc")
endif()


set(CLANG_FLAGS -march=native)
set(IMPALA_FLAGS --log-level info)

set(STINCILLA_COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/common/pnm_image)
include_directories(${STINCILLA_COMMON_INCLUDE_DIRS})

add_subdirectory(aobench)
add_subdirectory(bilateral_grid)
add_subdirectory(harris_corner)
add_subdirectory(test)
add_subdirectory(image_sharpening)
add_subdirectory(sorting_networks)
add_subdirectory(vcycle)

# simple CPU-based examples
anydsl_runtime_wrap(MATMUL_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${BACKEND_FILE} utils.impala matmul.impala)
add_executable(matmul ${MATMUL_PROGRAM})
target_link_libraries(matmul ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("matmul" matmul)

# examples based on the "mapping"
anydsl_runtime_wrap(GAUSSIAN_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${BACKEND_FILE} ${PIXEL_TYPE_FILES} utils.impala stencil_lib.impala mapping_${DEVICE}.impala gaussian.impala)
add_executable(gaussian ${GAUSSIAN_PROGRAM})
target_link_libraries(gaussian ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("gaussian" gaussian)

anydsl_runtime_wrap(GAUSSIAN_DEBUG_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${BACKEND_FILE} ${PIXEL_TYPE_FILES} utils.impala stencil_lib.impala mapping_${DEVICE}.impala gaussian_debug.impala)
add_executable(gaussian_debug ${GAUSSIAN_DEBUG_PROGRAM})
target_link_libraries(gaussian_debug ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("gaussian_debug" gaussian_debug)

anydsl_runtime_wrap(BILATERAL_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${BACKEND_FILE} utils.impala stencil_lib.impala mapping_${DEVICE}.impala bilateral.impala)
add_executable(bilateral ${BILATERAL_PROGRAM})
target_link_libraries(bilateral ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("bilateral" bilateral)

anydsl_runtime_wrap(JACOBI_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${BACKEND_FILE} utils.impala stencil_lib.impala mapping_${DEVICE}.impala jacobi.impala)
add_executable(jacobi ${JACOBI_PROGRAM})
target_link_libraries(jacobi ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("jacobi" jacobi)
