cmake_minimum_required (VERSION 3.13)
include (cmake/toolchain.cmake)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set (LANGUAGES C ASM)
project("template_project" ${LANGUAGES})
include (cmake/safeguards.cmake)

foreach (LANGUAGE ${LANGUAGES})
    set (CMAKE_${LANGUAGE}_FLAGS "")
    set (CMAKE_${LANGUAGE}_FLAGS_DEBUG "")
    set (CMAKE_${LANGUAGE}_FLAGS_RELEASE "")
endforeach()

add_compile_options(
    -mthumb
    -mcpu=cortex-m4
    -mfloat-abi=soft
    -ffunction-sections
    -fmerge-all-constants
    -save-temps
    -g3
    -Wall
    )

add_link_options(
    -mthumb
    -mcpu=cortex-m4
    -mfloat-abi=soft
    -ffunction-sections
    -fmerge-all-constants
    -fdata-sections
    -g3
    -Wl,-gc-sections
    --specs=nano.specs
    -Wl,--no-warn-rwx-segments
    )

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
set (OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin CACHE PATH "Output directory")
if(cmake_build_type_tolower STREQUAL "release")
    add_compile_options("-Werror")
endif()

# MCU specific flags
set(TARGET_FLAGS "-mcpu=cortex-m4 ")

include (cmake/optimizations.cmake)
include (cmake/version.cmake)
add_subdirectory (app)
add_subdirectory (lib)
