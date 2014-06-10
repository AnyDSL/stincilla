CMAKE_MINIMUM_REQUIRED(VERSION 2.8.5 FATAL_ERROR)

PROJECT ( STENCIL_DSL C CXX )

set(CUDA_DIR "/opt/cuda6.0" CACHE STRING "The directory containing the CUDA toolkit")
FIND_PACKAGE ( THORIN REQUIRED )
message("Using THORIN at ${THORIN_RUNTIME_DIR}, CUDA at ${CUDA_DIR}")
include(${THORIN_RUNTIME_DIR}/cmake/ThorinRuntime.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

add_subdirectory(test)
