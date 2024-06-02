#ifndef CONFIG_H_
#define CONFIG_H_

// -----------------------------------------------------------------------------
// GLOBAL CONSTANTS
// -----------------------------------------------------------------------------
// Additional options ----------------------------------------------------------

// Versioning configuration ----------------------------------------------------
#ifndef CONFIG_VERSION_TYPE_STR
// Default version type string used if the proper value is not passed during the
// build
#define CONFIG_VERSION_TYPE_STR                     "????"
#endif // CONFIG_VERSION_TYPE_STR
#ifndef CONFIG_VERSION_COMMIT_HASH
// Default version commit hash used if the proper value is not passed during the
// build
#define CONFIG_VERSION_COMMIT_HASH                  "unknown"
#endif // CONFIG_VERSION_COMMIT_HASH

// Note: the following constants may be:
// - hardcoded manually immediatelly below
// - passed as a build parameters (e.g. by build server)
// - injected into built binary (e.g.during a signing process using some git
//   commit data) - using a linker sections defined in version.c
// Anyway, it is strongly recommended not to use these macros directly but
// instead use a values exposed by version.h
#ifndef CONFIG_VERSION_MAJOR
// Version - major
#define CONFIG_VERSION_MAJOR                        0U
#endif // CONFIG_VERSION_MAJOR
#ifndef CONFIG_VERSION_MINOR
// Version - minor
#define CONFIG_VERSION_MINOR                        1U
#endif // CONFIG_VERSION_MINOR
#ifndef CONFIG_VERSION_PATCH
// Version - patch
#define CONFIG_VERSION_PATCH                        0U
#endif // CONFIG_VERSION_PATCH

#endif // CONFIG_H_
