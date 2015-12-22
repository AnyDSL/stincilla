thorin_runtime_wrap(SHARPENING_PROGRAM
    BACKEND ${BACKEND}
    FILES ../utils.impala ../mapping_${DEVICE}.impala mapping_${DEVICE}.impala sharpening.impala)
if(NOT MSVC)
    set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS "-std=c++11")
endif()
add_executable(sharpening main.cpp ${SHARPENING_PROGRAM})
target_link_libraries(sharpening ${THORIN_RUNTIME_LIBRARY} ${THORIN_RUNTIME_LIBRARIES})
add_test("sharpening" sharpening)
configure_file(goldhill.pgm ${CMAKE_CURRENT_BINARY_DIR}/goldhill.pgm COPYONLY)
