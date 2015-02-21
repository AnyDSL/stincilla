# simple CPU-based examples
THORIN_RUNTIME_WRAP(STENCIL_INT_FILES STENCIL_INT_LIBS
    BACKEND cpu
    MAIN
    FILES stencil_int.impala)
add_executable(stencil_int ${STENCIL_INT_FILES})
target_link_libraries(stencil_int ${STENCIL_INT_LIBS}) 

add_test("stencil_int" stencil_int)
