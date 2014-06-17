CMAKE_MINIMUM_REQUIRED(VERSION 2.8.5 FATAL_ERROR)

PROJECT ( STENCIL_DSL C CXX )

set(CUDA_DIR "/opt/cuda6.0" CACHE STRING "The directory containing the CUDA toolkit")
FIND_PACKAGE ( THORIN REQUIRED )
message("Using THORIN at ${THORIN_RUNTIME_DIR}, CUDA at ${CUDA_DIR}")
include(${THORIN_RUNTIME_DIR}/cmake/ThorinRuntime.cmake)
include_directories(${THORIN_RUNTIME_INCLUDE_DIR})

set(TESTS_RTTYPE "nvvm" CACHE STRING "The runtime-type of the tests")
message("Using runtime-type ${TESTS_RTTYPE}")
set(DEVICE "acc" CACHE STRING "mapping for target device")
if(TESTS_RTTYPE STREQUAL "cpu")
    set(DEVICE "cpu")
endif()
if(TESTS_RTTYPE STREQUAL "avx")
    set(DEVICE "avx")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

add_subdirectory(test)
add_subdirectory(cpp_interfacing)

# simple CPU-based examples
THORIN_RUNTIME_WRAP(MATMUL_FILES MATMUL_LIBS
	RTTYPE cpu
	MAIN
	FILES extern.impala matmul.impala)
add_executable(matmul ${MATMUL_FILES})
target_link_libraries(matmul ${MATMUL_LIBS})

# examples based on the "mapping"
THORIN_RUNTIME_WRAP(GAUSSIAN_FILES GAUSSIAN_LIBS
	RTTYPE ${TESTS_RTTYPE}
	MAIN
	FILES extern.impala mapping_${DEVICE}.impala gaussian.impala)
add_executable(gaussian ${GAUSSIAN_FILES})
target_link_libraries(gaussian ${GAUSSIAN_LIBS})

THORIN_RUNTIME_WRAP(BILATERAL_FILES BILATERAL_LIBS
	RTTYPE ${TESTS_RTTYPE}
	MAIN
	FILES extern.impala mapping_${DEVICE}.impala bilateral.impala)
add_executable(bilateral ${BILATERAL_FILES})
target_link_libraries(bilateral ${BILATERAL_LIBS})

THORIN_RUNTIME_WRAP(JACOBI_FILES JACOBI_LIBS
	RTTYPE ${TESTS_RTTYPE}
	MAIN
	FILES extern.impala mapping_${DEVICE}.impala jacobi.impala)
add_executable(jacobi ${JACOBI_FILES})
target_link_libraries(jacobi ${JACOBI_LIBS})
