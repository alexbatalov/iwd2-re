# T1/T2 unit tests. Link the game library and run without game data.

# Layout test: generated from header offset annotations at build time.
find_package(Python3 COMPONENTS Interpreter REQUIRED)
file(GLOB_RECURSE IWD2RE_HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.h")
set(LAYOUT_TEST "${CMAKE_CURRENT_BINARY_DIR}/test_layout.cpp")
add_custom_command(
    OUTPUT "${LAYOUT_TEST}"
    COMMAND Python3::Interpreter -I "${PROJECT_SOURCE_DIR}/tools/gen_layout_asserts.py" --out "${LAYOUT_TEST}"
    DEPENDS
        "${PROJECT_SOURCE_DIR}/tools/gen_layout_asserts.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/layout/known_mismatches.txt"
        ${IWD2RE_HEADERS}
    COMMENT "Generating layout test"
)

add_executable(iwd2-tests
    "unit/main.cpp"
    "unit/test.h"
    "unit/test_resref.cpp"
    "${LAYOUT_TEST}"
)
target_include_directories(iwd2-tests PRIVATE "${PROJECT_SOURCE_DIR}/third_party/doctest" "unit")
target_link_libraries(iwd2-tests PRIVATE iwd2-core)
target_compile_options(iwd2-tests PRIVATE /bigobj)
add_test(NAME unit COMMAND iwd2-tests)

# The original was built with 2-byte struct packing (annotated offsets put
# ints on 2-byte boundaries). Measure offsets the same way. MFC and Windows
# headers set their own packing, so their types are unaffected.
set_source_files_properties("${LAYOUT_TEST}" PROPERTIES COMPILE_OPTIONS "/Zp2")
