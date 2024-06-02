set (TARGET "template_project.elf")
set (LINKERSCRIPT "system/STM32F411CEUx_FLASH.ld")
set (APP_DEFS "" CACHE STRING "Additional app defenitions")

string(REPLACE ".elf" ".map" MAP ${TARGET})
string(REPLACE ".elf" ".hex" IHEX ${TARGET})
string(REPLACE ".elf" ".bin" BINARY ${TARGET})
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE_DEFENITION)

add_executable(${TARGET}
    ${LINKERSCRIPT}
    config.h
    constants.h
    main.c
    bsp/wdt.c
    bsp/wdt.h
    bsp/time.c
    bsp/time.h
    bsp/private/time_private.h
    system/system.c
    system/system.h
    system/stm32f4xx_it.c
    business/template.c
    business/template.h
    middleware/soft_timer/soft_timer.c
    middleware/soft_timer/soft_timer.h
    middleware/soft_timer/soft_timer_private_config.h
    version/version.c
    version/version.h
)

set_target_properties(${TARGET}
PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)

target_include_directories(${TARGET} PUBLIC
    .
)

target_compile_definitions(${TARGET} PUBLIC
    "${BUILD_TYPE_DEFENITION}"
    ${APP_DEFS}
)

set_source_files_properties("version/version.c" PROPERTIES COMPILE_FLAGS "-DCONFIG_VERSION_COMMIT_HASH=\\\"${VERSION_COMMIT_HASH}\\\" -DCONFIG_VERSION_TYPE_STR=\\\"${VERSION_TYPE}\\\"")
# Force reconfiguring and thus regeneration of the version info on any
# change of the target sources
get_target_property(TARGET_SOURCES ${TARGET} SOURCES)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${TARGET_SOURCES})

target_link_libraries(${TARGET}
    stm32f4_hal
    stm32f411ce
    tools_cm4_gcc
)

target_compile_options(${TARGET} PRIVATE
    $<$<CONFIG:DEBUG>: -O0>
    $<$<CONFIG:RELEASE>: -Os>
    -Wall
    -Wextra
)

target_link_options(${TARGET} PRIVATE
    "-Wl,--defsym=${BUILD_TYPE_DEFENITION}=0"
    "-Wl,--cref"
    "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${MAP}"
    "-T${CMAKE_CURRENT_SOURCE_DIR}/${LINKERSCRIPT}"
)

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMENT "Size:"
    COMMAND ${CMAKE_OBJSIZE} "-B" ${TARGET}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMENT "Generating ${BINARY}"
    COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET} ${BINARY}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMENT "Generating ${IHEX}"
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET} ${IHEX}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
