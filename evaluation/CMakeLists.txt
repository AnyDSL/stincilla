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
set(PIXEL_TYPE ${PIXEL_TYPE} CACHE STRING "select the pixel type from the following: f32, i32, u8")
if(NOT PIXEL_TYPE)
    set(PIXEL_TYPE f32 CACHE STRING "select the pixel type from the following: f32, i32, u8" FORCE)
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

anydsl_runtime_wrap(GAUSSIAN_DEBUG_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala gaussian_debug.impala)
add_executable(gaussian_debug ${GAUSSIAN_DEBUG_PROGRAM})
target_link_libraries(gaussian_debug ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("gaussian_debug" gaussian_debug)

## v=g1
# No border handling at all
anydsl_runtime_wrap(g1CAP_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g1cap.impala)
add_executable(g1cap ${g1CAP_PROGRAM})
target_link_libraries(g1cap ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g1cap" g1cap)

anydsl_runtime_wrap(g1FAC_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g1fac.impala)
add_executable(g1fac ${g1FAC_PROGRAM})
target_link_libraries(g1fac ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g1fac" g1fac)

# Type-0 border handling 
anydsl_runtime_wrap(g1CAP_NOBH_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g1cap_nobh.impala)
add_executable(g1cap_nobh ${g1CAP_NOBH_PROGRAM})
target_link_libraries(g1cap_nobh ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g1cap_nobh" g1cap_nobh)

anydsl_runtime_wrap(g1FAC_NOBH_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g1fac_nobh.impala)
add_executable(g1fac_nobh ${g1FAC_NOBH_PROGRAM})
target_link_libraries(g1fac_nobh ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g1fac_nobh" g1fac_nobh)

anydsl_runtime_wrap(g1CAP_MIRROR_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g1cap_mirror.impala)
add_executable(g1cap_mirror ${g1CAP_MIRROR_PROGRAM})
target_link_libraries(g1cap_mirror ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g1cap_mirror" g1cap_mirror)

anydsl_runtime_wrap(g1FAC_MIRROR_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g1fac_mirror.impala)
add_executable(g1fac_mirror ${g1FAC_MIRROR_PROGRAM})
target_link_libraries(g1fac_mirror ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g1fac_mirror" g1fac_mirror)


## v=g8
# No border handling at all
anydsl_runtime_wrap(g8CAP_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g8cap.impala)
add_executable(g8cap ${g8CAP_PROGRAM})
target_link_libraries(g8cap ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g8cap" g8cap)

anydsl_runtime_wrap(g8FAC_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g8fac.impala)
add_executable(g8fac ${g8FAC_PROGRAM})
target_link_libraries(g8fac ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g8fac" g8fac)

# Type-0 border handling 
anydsl_runtime_wrap(g8CAP_NOBH_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g8cap_nobh.impala)
add_executable(g8cap_nobh ${g8CAP_NOBH_PROGRAM})
target_link_libraries(g8cap_nobh ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g8cap_nobh" g8cap_nobh)

anydsl_runtime_wrap(g8FAC_NOBH_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g8fac_nobh.impala)
add_executable(g8fac_nobh ${g8FAC_NOBH_PROGRAM})
target_link_libraries(g8fac_nobh ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g8fac_nobh" g8fac_nobh)

anydsl_runtime_wrap(g8CAP_MIRROR_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g8cap_mirror.impala)
add_executable(g8cap_mirror ${g8CAP_MIRROR_PROGRAM})
target_link_libraries(g8cap_mirror ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g8cap_mirror" g8cap_mirror)

anydsl_runtime_wrap(g8FAC_MIRROR_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g8fac_mirror.impala)
add_executable(g8fac_mirror ${g8FAC_MIRROR_PROGRAM})
target_link_libraries(g8fac_mirror ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g8fac_mirror" g8fac_mirror)


## v=g16
# No border handling at all
anydsl_runtime_wrap(g16CAP_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g16cap.impala)
add_executable(g16cap ${g16CAP_PROGRAM})
target_link_libraries(g16cap ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g16cap" g16cap)

anydsl_runtime_wrap(g16FAC_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g16fac.impala)
add_executable(g16fac ${g16FAC_PROGRAM})
target_link_libraries(g16fac ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g16fac" g16fac)

# Type-0 border handling 
anydsl_runtime_wrap(g16CAP_NOBH_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g16cap_nobh.impala)
add_executable(g16cap_nobh ${g16CAP_NOBH_PROGRAM})
target_link_libraries(g16cap_nobh ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g16cap_nobh" g16cap_nobh)

anydsl_runtime_wrap(g16FAC_NOBH_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g16fac_nobh.impala)
add_executable(g16fac_nobh ${g16FAC_NOBH_PROGRAM})
target_link_libraries(g16fac_nobh ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g16fac_nobh" g16fac_nobh)

anydsl_runtime_wrap(g16CAP_MIRROR_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g16cap_mirror.impala)
add_executable(g16cap_mirror ${g16CAP_MIRROR_PROGRAM})
target_link_libraries(g16cap_mirror ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g16cap_mirror" g16cap_mirror)

anydsl_runtime_wrap(g16FAC_MIRROR_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g16fac_mirror.impala)
add_executable(g16fac_mirror ${g16FAC_MIRROR_PROGRAM})
target_link_libraries(g16fac_mirror ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g16fac_mirror" g16fac_mirror)


## v=32
# No border handling at all
anydsl_runtime_wrap(g32CAP_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g32cap.impala)
add_executable(g32cap ${g32CAP_PROGRAM})
target_link_libraries(g32cap ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g32cap" g32cap)

anydsl_runtime_wrap(g32FAC_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g32fac.impala)
add_executable(g32fac ${g32FAC_PROGRAM})
target_link_libraries(g32fac ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g32fac" g32fac)

# Type-0 border handling 
anydsl_runtime_wrap(g32CAP_NOBH_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g32cap_nobh.impala)
add_executable(g32cap_nobh ${g32CAP_NOBH_PROGRAM})
target_link_libraries(g32cap_nobh ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g32cap_nobh" g32cap_nobh)

anydsl_runtime_wrap(g32FAC_NOBH_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g32fac_nobh.impala)
add_executable(g32fac_nobh ${g32FAC_NOBH_PROGRAM})
target_link_libraries(g32fac_nobh ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g32fac_nobh" g32fac_nobh)

anydsl_runtime_wrap(g32CAP_MIRROR_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g32cap_mirror.impala)
add_executable(g32cap_mirror ${g32CAP_MIRROR_PROGRAM})
target_link_libraries(g32cap_mirror ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g32cap_mirror" g32cap_mirror)

anydsl_runtime_wrap(g32FAC_MIRROR_PROGRAM
    CLANG_FLAGS ${CLANG_FLAGS}
    IMPALA_FLAGS ${IMPALA_FLAGS}
    FILES ../${BACKEND_FILE} ../${PIXEL_TYPE_FILES} ../utils.impala ../stencil_lib.impala ../mapping_${DEVICE}.impala g32fac_mirror.impala)
add_executable(g32fac_mirror ${g32FAC_MIRROR_PROGRAM})
target_link_libraries(g32fac_mirror ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
add_test("g32fac_mirror" g32fac_mirror)

## v=1
