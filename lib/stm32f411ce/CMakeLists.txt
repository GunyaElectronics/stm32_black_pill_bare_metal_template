set(TARGET stm32f411ce)

add_library(${TARGET})

file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SOURCES "*.c" "*.s")

target_sources(${TARGET} PRIVATE ${HEADERS} ${SOURCES})

target_include_directories(${TARGET} PUBLIC .)

target_link_libraries(${TARGET} PUBLIC
    cmsis
    stm32f4_hal
)

target_compile_definitions(${TARGET} PUBLIC
    "${BUILD_TYPE_DEFENITION}"
    HSE_VALUE=25000000UL
    USE_HAL_DRIVER
    STM32F4
    STM32F411xE
)
