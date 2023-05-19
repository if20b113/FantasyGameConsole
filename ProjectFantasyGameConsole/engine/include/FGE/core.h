#pragma once

#ifdef _WIN32
#  define FGE_API __declspec(dllexport)
#else
#  define FGE_API
#endif

#include <cstdint>

namespace FGE {

    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    typedef int8_t i8;
    typedef int16_t i16;
    typedef int32_t i32;
    typedef int64_t i64;
    
}