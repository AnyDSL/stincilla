cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

project(STINCILLA CXX)
enable_testing()

find_package(AnyDSL_runtime REQUIRED)
include_directories(${AnyDSL_runtime_INCLUDE_DIRS})

set(BACKEND "cpu" CACHE STRING "select the backend from the following: CPU, AVX, NVVM, CUDA, OPENCL, AMDGPU")
set_property(CACHE BACKEND PROPERTY STRINGS cpu avx nvvm cuda opencl amdgpu)
string(TOLOWER ${BACKEND} BACKEND)
message(STATUS "Selected backend: ${BACKEND}")

set(BACKEND_FILE backend_${BACKEND}.impala)

if(BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx")
    set(DEVICE "cpu")
else()
    set(DEVICE "acc")
endif()

set(CLANG_FLAGS -march=native)
set(IMPALA_FLAGS --log-level info)

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
    FILES ${BACKEND_FILE} utils.impala matmul.impala)
add_executable(matmul ${MATMUL_PROGRAM})
target_link_libraries(matmul ${AnyDSL_runtime_LIBRARIES})
add_test("matmul" matmul)

# examples based on the "mapping"
anydsl_runtime_wrap(GAUSSIAN_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${BACKEND_FILE} utils.impala stencil_lib.impala mapping_${DEVICE}.impala gaussian.impala)
add_executable(gaussian ${GAUSSIAN_PROGRAM})
target_link_libraries(gaussian ${AnyDSL_runtime_LIBRARIES})
add_test("gaussian" gaussian)

anydsl_runtime_wrap(BILATERAL_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${BACKEND_FILE} utils.impala stencil_lib.impala mapping_${DEVICE}.impala bilateral.impala)
add_executable(bilateral ${BILATERAL_PROGRAM})
target_link_libraries(bilateral ${AnyDSL_runtime_LIBRARIES})
add_test("bilateral" bilateral)

anydsl_runtime_wrap(JACOBI_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ${BACKEND_FILE} utils.impala stencil_lib.impala mapping_${DEVICE}.impala jacobi.impala)
add_executable(jacobi ${JACOBI_PROGRAM})
target_link_libraries(jacobi ${AnyDSL_runtime_LIBRARIES})
add_test("jacobi" jacobi)
