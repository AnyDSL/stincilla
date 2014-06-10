CMAKE_MINIMUM_REQUIRED(VERSION 2.8.5 FATAL_ERROR)

PROJECT ( STENCIL_DSL C CXX )

set(CUDA_DIR "/opt/cuda6.0" CACHE STRING "The directory containing the CUDA toolkit")
FIND_PACKAGE ( THORIN REQUIRED )
message("Using THORIN at ${THORIN_RUNTIME_DIR}, CUDA at ${CUDA_DIR}")
include(${THORIN_RUNTIME_DIR}/cmake/ThorinRuntime.cmake)
include_directories(${THORIN_RUNTIME_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

add_subdirectory(test)
add_subdirectory(cpp_interfacing)

THORIN_RUNTIME_WRAP(GAUSSIAN_FILES GAUSSIAN_LIBS
	RTTYPE nvvm
	MAIN
	FILES extern.impala mapping_nvvm.impala gaussian.impala)
add_executable(gaussian ${GAUSSIAN_FILES})
target_link_libraries(gaussian ${GAUSSIAN_LIBS})

THORIN_RUNTIME_WRAP(JACOBI_FILES JACOBI_LIBS
	RTTYPE nvvm
	MAIN
	FILES extern.impala mapping_nvvm.impala jacobi.impala)
#add_executable(jacobi ${JACOBI_FILES}) # FIXME: loops endless; after removing the @ an assertion fails
#target_link_libraries(jacobi ${JACOBI_LIBS})

THORIN_RUNTIME_WRAP(MATMUL_FILES MATMUL_LIBS
	RTTYPE cpu
	MAIN
	FILES extern.impala matmul.impala)
add_executable(matmul ${MATMUL_FILES}) # FIXME: complains about invalid for
target_link_libraries(matmul ${MATMUL_LIBS})
