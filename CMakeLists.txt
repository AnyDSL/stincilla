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

get_filename_component(BACKEND_FILE backend_${BACKEND}.impala ABSOLUTE CACHE)
if(BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx")
    set(DEVICE "cpu")
else()
    set(DEVICE "acc")
endif()

set(CLANG_FLAGS -march=native)
set(IMPALA_FLAGS --log-level info)
set(ANYDSL_RUNTIME_LIBRARIES ${AnyDSL_runtime_LIBRARIES})
option(EMIT_C "Emit the host code as C code instead of LLVM IR" OFF)

set(STINCILLA_COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/common/pnm_image)
include_directories(${STINCILLA_COMMON_INCLUDE_DIRS})

function(add_stincilla_test name cpp_files impala_files)
    if (EMIT_C)
        anydsl_runtime_wrap(${name}_objs
            EMIT_C
            CLANG_FLAGS ${CLANG_FLAGS}
            IMPALA_FLAGS ${IMPALA_FLAGS}
            FILES ${BACKEND_FILE} ${impala_files})
    else()
        anydsl_runtime_wrap(${name}_objs
            CLANG_FLAGS ${CLANG_FLAGS}
            IMPALA_FLAGS ${IMPALA_FLAGS}
            FILES ${BACKEND_FILE} ${impala_files})
    endif()
    add_executable(${name} "${cpp_files};${${name}_objs}")
    set_target_properties(${name} PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
    target_link_libraries(${name} ${ANYDSL_RUNTIME_LIBRARIES})
    add_test(${name} ${name})
endfunction()

add_subdirectory(aobench)
add_subdirectory(bilateral_grid)
add_subdirectory(halide)
add_subdirectory(harris_corner)
add_subdirectory(test)
add_subdirectory(image_sharpening)
add_subdirectory(sorting_networks)
add_subdirectory(vcycle)

add_stincilla_test(matmul "" "utils.impala;matmul.impala")
add_stincilla_test(gaussian "" "utils.impala;stencil_lib.impala;mapping_${DEVICE}.impala;gaussian.impala")
add_stincilla_test(bilateral "" "utils.impala;stencil_lib.impala;mapping_${DEVICE}.impala;bilateral.impala")
add_stincilla_test(jacobi "" "utils.impala;stencil_lib.impala;mapping_${DEVICE}.impala;jacobi.impala")
