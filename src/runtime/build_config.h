#pragma once

#include <stdint.h>

typedef uint8_t byte;
typedef int8_t sbyte;

#define BUILD_CONFIG_INCLUDED 1
#define SUPPORT_UNALIGNED_ACCESS 1

#if UINTPTR_MAX == 0xFFFFFFFF
#define LEANCLR_ARCH_32BIT 1
#else
#define LEANCLR_ARCH_64BIT 1
#endif

#if defined(__GNUC__) || defined(__clang__)
// #define USE_COMPUTED_GOTO_DISPATCHER 1
#define USE_COMPUTED_GOTO_DISPATCHER 0
#else
#define USE_COMPUTED_GOTO_DISPATCHER 0
#endif

#if !NDEBUG
#define ENABLE_TEST_PINVOKES 1
#define ENABLE_TEST_INTRINSICS 1
#define ENABLE_TEST_INTERNAL_CALLS 1
#endif
