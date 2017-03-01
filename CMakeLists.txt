cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(STINCILLA CXX)
enable_testing()

find_package(IMPALA REQUIRED)

set(BACKEND ${BACKEND} CACHE STRING "select the backend from the following: CPU, AVX, NVVM, CUDA, OPENCL")
if(NOT BACKEND)
    set(BACKEND cpu CACHE STRING "select the backend from the following: CPU, AVX, NVVM, CUDA, OPENCL" FORCE)
endif()
string(TOLOWER "${BACKEND}" BACKEND)
message(STATUS "Selected backend: ${BACKEND}")

set(BACKEND_FILE ${CMAKE_CURRENT_SOURCE_DIR}/intrinsics_${BACKEND}.impala)

if(BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx")
    set(DEVICE "cpu")
else()
    set(DEVICE "acc")
endif()

set(STINCILLA_COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/common/pnm_image)
include_directories(${STINCILLA_COMMON_INCLUDE_DIRS})

function (add_test_sample _name)
    CMAKE_PARSE_ARGUMENTS ( "PARGS" "" "" "CXX;IMPALA" ${ARGN} )
    set(_infiles ${PARGS_IMPALA})
    set(_cxxfiles ${PARGS_CXX})
    if (NOT (_infiles OR _cxxfiles))
        set(_infiles ${PARGS_UNPARSED_ARGUMENTS})
    endif()
    set(_backend_file ${BACKEND_FILE})
    source_group("Impala Files" REGULAR_EXPRESSION "[.]impala$")
    wrap_impala_sources(_outfiles OUTPUT_NAME ${_name} FILES ${_infiles} ${_backend_file})
    add_executable(${_name} ${_outfiles} ${_infiles} ${_backend_file} ${_cxxfiles})
    target_link_libraries(${_name} ${IMPALA_RUNTIME_LIBRARIES})
    add_test("${_name}" ${_name})
endfunction()

add_subdirectory(aobench)
add_subdirectory(bilateral_grid)
add_subdirectory(harris_corner)
add_subdirectory(test)
add_subdirectory(image_sharpening)
add_subdirectory(sorting_networks)
add_subdirectory(vcycle)

# simple CPU-based examples
add_test_sample(matmul utils.impala matmul.impala)

# examples based on the "mapping"
add_test_sample(gaussian utils.impala stencil_lib.impala mapping_${DEVICE}.impala gaussian.impala)
add_test_sample(bilateral utils.impala stencil_lib.impala mapping_${DEVICE}.impala bilateral.impala)
add_test_sample(jacobi utils.impala stencil_lib.impala mapping_${DEVICE}.impala jacobi.impala)
