#ifndef VERSION_H_
#define VERSION_H_

#include <stdint.h>
#include <stddef.h>

// -----------------------------------------------------------------------------
// GLOBAL CONSTANTS
// -----------------------------------------------------------------------------
#define VERSION_TYPE_STR_LENGTH         4U
#define VERSION_COMMIT_HASH_STR_LENGTH  8U

extern const volatile uint8_t Version_App_major;
extern const volatile uint8_t Version_App_minor;
extern const volatile uint8_t Version_App_patch;

// -----------------------------------------------------------------------------
// GLOBAL FUNCTIONS
// -----------------------------------------------------------------------------
const char (*Version_App_GetTypeStr(void))[VERSION_TYPE_STR_LENGTH];
const char (*Version_App_GetCommitHashStr(void))[
    VERSION_COMMIT_HASH_STR_LENGTH];

#endif // VERSION_H_
