set(TARGET tools_cm4_gcc)
add_library(${TARGET} INTERFACE)

target_sources(${TARGET} INTERFACE
    assert.h
    compiler.h
    linkage.h
)

target_include_directories(${TARGET} INTERFACE .)
