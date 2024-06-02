set(TARGET cmsis)
add_library(${TARGET} INTERFACE)

file(GLOB_RECURSE HEADERS "*.h")
target_sources(${TARGET} INTERFACE ${HEADERS})

target_include_directories(${TARGET} INTERFACE .)
