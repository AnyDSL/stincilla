cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(STINCILLA CXX)
enable_testing()

find_package(AnyDSL-runtime REQUIRED)
include(${ANYDSL_RUNTIME_CMAKE_DIR}/Runtime.cmake)
include_directories(${ANYDSL_RUNTIME_DIR}/src)

if(BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx")
    set(DEVICE "cpu")
else()
    set(DEVICE "acc")
endif()

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
    BACKEND cpu
    FILES utils.impala matmul.impala)
add_executable(matmul ${MATMUL_PROGRAM})
target_link_libraries(matmul ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("matmul" matmul)

# examples based on the "mapping"
anydsl_runtime_wrap(GAUSSIAN_PROGRAM
    BACKEND ${BACKEND}
    FILES utils.impala mapping_${DEVICE}.impala gaussian.impala)
add_executable(gaussian ${GAUSSIAN_PROGRAM})
target_link_libraries(gaussian ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("gaussian" gaussian)

anydsl_runtime_wrap(BILATERAL_PROGRAM
    BACKEND ${BACKEND}
    FILES utils.impala mapping_${DEVICE}.impala bilateral.impala)
add_executable(bilateral ${BILATERAL_PROGRAM})
target_link_libraries(bilateral ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("bilateral" bilateral)

anydsl_runtime_wrap(JACOBI_PROGRAM
    BACKEND ${BACKEND}
    FILES utils.impala mapping_${DEVICE}.impala jacobi.impala)
add_executable(jacobi ${JACOBI_PROGRAM})
target_link_libraries(jacobi ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("jacobi" jacobi)
