cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(STINCILLA CXX)
enable_testing()

find_package(IMPALA REQUIRED)

if(NOT BACKEND)
    set(BACKEND cpu)
endif()

if(BACKEND STREQUAL "cpu" OR BACKEND STREQUAL "avx")
    set(DEVICE "cpu")
else()
    set(DEVICE "acc")
endif()

set(STINCILLA_COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/common/pnm_image)
include_directories(${STINCILLA_COMMON_INCLUDE_DIRS})

function (add_test_sample _name _backend)
    CMAKE_PARSE_ARGUMENTS ( "PARGS" "" "" "CXX;IMPALA" ${ARGN} )
    set(_infiles ${PARGS_IMPALA})
    set(_cxxfiles ${PARGS_CXX})
    if (NOT (_infiles OR _cxxfiles))
        set(_infiles ${PARGS_UNPARSED_ARGUMENTS})
    endif()
    source_group("Impala Files" REGULAR_EXPRESSION "[.]impala$")
    wrap_impala_sources(_outfiles BACKEND ${_backend} OUTPUT_NAME ${_name} FILES ${_infiles})
    add_executable(${_name} ${_outfiles} ${_infiles} ${_cxxfiles})
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
add_test_sample(matmul cpu utils.impala matmul.impala)

# examples based on the "mapping"
add_test_sample(gaussian ${BACKEND} utils.impala mapping_${DEVICE}.impala gaussian.impala)
add_test_sample(bilateral ${BACKEND} utils.impala mapping_${DEVICE}.impala bilateral.impala)
add_test_sample(jacobi ${BACKEND} utils.impala mapping_${DEVICE}.impala jacobi.impala)
