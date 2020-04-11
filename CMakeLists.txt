cmake_minimum_required(VERSION 3.5)
project(Grey
        VERSION 0.1.0
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
    add_compile_definitions(GREY_UINTBITS=${GREY_UINTBITS})
endif ()


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
