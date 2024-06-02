#ifndef ASSERT_H_
#define ASSERT_H_

#include "compiler.h"
#include_next <assert.h>
#include <stdint.h>

// -----------------------------------------------------------------------------
// GLOBAL MACROS
// -----------------------------------------------------------------------------
#define ASSERT(cond, ...)                                                      \
    do {                                                                       \
        if ((cond) == 0) {                                                     \
            uint32_t pc;                                                       \
            __asm volatile ("mov %0, pc\n" : "=r" (pc));                       \
            Assert_Ext_ProcessFailure(pc);                                     \
        }                                                                      \
    } while (0)

#define STATIC_ASSERT(cond, ...)        static_assert(cond, __VA_ARGS__)

// -----------------------------------------------------------------------------
// GLOBAL FUNCTIONS
// -----------------------------------------------------------------------------
NO_RETURN void Assert_Ext_ProcessFailure(uint_fast32_t pc);

#endif // ASSERT_H_
