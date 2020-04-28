cmake_minimum_required(VERSION 3.5)
project(Grey
        VERSION 1.0.0
        LANGUAGES C
        DESCRIPTION
        "Simple Grey codes a.k.a. Reflected Binary Codes library.")

# Unless specified, by default create Release builds
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
# Change this parameter to 64, 32, 16, 8 to use uint64_t, uint32_t, uint16
# or uint8_t respectively as underlying integer to hold Grey codes and their
# values.
# Unless specified, use 64 bits.
if (NOT GREY_UINTBITS)
    set(GREY_UINTBITS 64)
endif ()
add_compile_definitions(GREY_UINTBITS=${GREY_UINTBITS})


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 99)
# Activate a million warnings to have the cleanest possible code
set(FLAGS_WARNINGS -Wall -Wextra -pedantic -Wconversion -Wdouble-promotion
        -Wswitch-default -Wswitch-enum -Wuninitialized -Wno-unused-variable
        -Wpacked -Wpadded -Wshadow -Wformat-security -Wlogical-not-parentheses
        -Waggregate-return -Wmissing-declarations -Wmissing-declarations)
# Debug build: compile with no optimisation, debug info and printing
set(CMAKE_C_FLAGS_DEBUG "${WARNING_FLAGS} -g -O0 -DDEBUG")
# Append sanitiser flags on non-Windows systems
if (NOT WIN32 AND NOT CYGWIN AND NOT MSYS)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} \
            -fsanitize=address,undefined -static-libsan")
endif ()

# Mini-sized release build: compile with optimisation for size
# convert warnings into errors and some other optimisations
set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} \
        ${WARNING_FLAGS} \
        -Os -Werror -fomit-frame-pointer -march=native -mtune=native")

# Performance-oriented release build: compile with optimisation for speed
# convert warnings into errors and some other optimisations
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} \
        ${WARNING_FLAGS} \
        -O3 -Werror -fomit-frame-pointer -march=native -mtune=native \
        -funroll-loops")

include_directories(inc/)
set(LIB_FILES src/grey.c)
include_directories(tst/ tst/atto/)
set(TEST_FILES tst/test.c tst/atto/atto.c)

add_library("grey${BITS}" SHARED ${LIB_FILES})
add_library("greystatic${BITS}" STATIC ${LIB_FILES})
add_executable("test_grey${BITS}" ${LIB_FILES} ${TEST_FILES})

# Doxygen documentation builder
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # Cmake's wrapper of Doxygen, constructing a doxyfile from the
    # DOXYGEN_* variables, which are mapped to the Doxygen variables.
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN YES)
    set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
    set(DOXYGEN_SORT_MEMBER_DOCS NO)
    set(DOXYGEN_ALIASES license="**License:**")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    doxygen_add_docs(doxygen
            ALL # Build doxygen on make-all
            # List of input files for Doxygen
            ${PROJECT_SOURCE_DIR}/inc/grey.h
            ${PROJECT_SOURCE_DIR}/LICENSE.md
            ${PROJECT_SOURCE_DIR}/README.md
            ${PROJECT_SOURCE_DIR}/CHANGELOG.md)
else (DOXYGEN_FOUND)
    message(WARNING "Doxygen not found. Cannot generate documentation.")
endif (DOXYGEN_FOUND)
