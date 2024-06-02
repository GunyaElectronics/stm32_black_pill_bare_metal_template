#include "version.h"
#include "config.h"
#include "assert.h"
#include "linkage.h"

// -----------------------------------------------------------------------------
// GLOBAL CONSTANTS
// -----------------------------------------------------------------------------
LINKAGE_SECTION(".app_version_major")
    const volatile uint8_t Version_App_major = CONFIG_VERSION_MAJOR;
LINKAGE_SECTION(".app_version_minor")
    const volatile uint8_t Version_App_minor = CONFIG_VERSION_MINOR;
LINKAGE_SECTION(".app_version_patch")
    const volatile uint8_t Version_App_patch = CONFIG_VERSION_PATCH;

// -----------------------------------------------------------------------------
// LOCAL CONSTANTS
// -----------------------------------------------------------------------------
LINKAGE_SECTION(".app_version_type_str")
    static volatile const char appTypeStr[VERSION_TYPE_STR_LENGTH] =
        CONFIG_VERSION_TYPE_STR;
STATIC_ASSERT(
    sizeof(CONFIG_VERSION_TYPE_STR) <=
        (sizeof(appTypeStr) + sizeof((char) '\0')),
        "Implementation has length constraints for CONFIG_VERSION_TYPE_STR");

LINKAGE_SECTION(".app_version_commit_hash")
    static volatile const char appCommitHashStr[
        VERSION_COMMIT_HASH_STR_LENGTH] =
        CONFIG_VERSION_COMMIT_HASH;
STATIC_ASSERT(
    sizeof(CONFIG_VERSION_COMMIT_HASH) <=
        (sizeof(appCommitHashStr) + sizeof((char) '\0')),
        "Implementation has length constraints for CONFIG_VERSION_COMMIT_HASH");

// -----------------------------------------------------------------------------
// FUNCTIONS IMPLEMENTATION
// -----------------------------------------------------------------------------
const char (*Version_App_GetTypeStr(void))[VERSION_TYPE_STR_LENGTH]
{
    return (const char (*)[VERSION_TYPE_STR_LENGTH]) &appTypeStr;
}

const char (*Version_App_GetCommitHashStr(void))[VERSION_COMMIT_HASH_STR_LENGTH]
{
    return (const char (*)[VERSION_COMMIT_HASH_STR_LENGTH]) &appCommitHashStr;
}
