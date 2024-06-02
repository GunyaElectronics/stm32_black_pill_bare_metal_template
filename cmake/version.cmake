# Evaluate version commit hash
execute_process(COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE VERSION_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT VERSION_TYPE)
    # Version type is not specified - evaluate it based on the git status
    execute_process(COMMAND git status --porcelain
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_STATUS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if(GIT_STATUS)
        # There are not commited changes - consider dirty build
        set (VERSION_TYPE "dirt")
    else()
        # Everything is commited - consider pure local build
        set (VERSION_TYPE "locl")
    endif()
endif()
