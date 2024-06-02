#ifndef LINKAGE_H_
#define LINKAGE_H_

// -----------------------------------------------------------------------------
// GLOBAL MACROS
// -----------------------------------------------------------------------------
#if defined(__GNUC__) && !defined(__ARMCC_VERSION)
// Macro for placing a symbol in linker section sect
#define LINKAGE_SECTION(sect)  __attribute__((section(sect)))
#else // __GNUC__ && ! __ARMCC_VERSION
#error "This compiler is not supported"
#endif // __GNUC__ && ! __ARMCC_VERSION

#endif // LINKAGE_H_
