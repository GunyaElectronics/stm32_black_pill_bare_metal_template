#ifndef COMPILER_H_
#define COMPILER_H_

#include <stdint.h>

// -----------------------------------------------------------------------------
// GLOBAL MACROS
// -----------------------------------------------------------------------------
#define NO_RETURN                       __attribute__((__noreturn__))
#define NO_DISCARD                      __attribute__((warn_unused_result))
#define FALL_THROUGH                    __attribute__((fallthrough))
#define ALIGN_OF(typeId)                _Alignof(typeId)
#define SIZE_OF_FIELD(typeId, member)   (sizeof(((typeId *) 0)->member))
#define OFFSET_OF(typeId, member)       __builtin_offsetof(typeId, member)

// -----------------------------------------------------------------------------
// GLOBAL FUNCTIONS
// -----------------------------------------------------------------------------
__attribute__((always_inline)) static inline
    void JumpToAddress(uint32_t address)
{
    __asm volatile("bx %0\n" : : "r" (address));
}

#endif // COMPILER_H_
