#pragma once

#include "deps/std.hpp"

#ifndef ENUM_AS_SIZE
#define ENUM_AS_SIZE(x) static_cast<size_t>(x)
#endif

#ifndef SIZE_AS_ENUM
#define SIZE_AS_ENUM(name, x) static_cast<name>(x)
#endif

#ifndef AND_ENUMS
#define AND_ENUMS(name, a, b) (ENUM_AS_SIZE(a) & ENUM_AS_SIZE(b))
#endif

#ifndef XOR_ENUMS
#define XOR_ENUMS(name, a, b) (ENUM_AS_SIZE(a) ^ ENUM_AS_SIZE(b))
#endif

#ifndef OR_ENUMS
#define OR_ENUMS(name, a, b) (ENUM_AS_SIZE(a) | ENUM_AS_SIZE(b))
#endif

template<typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
bool operator&(Enum a, Enum b) { return AND_ENUMS(Enum, a, b); }

template<typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
bool operator^(Enum a, Enum b) { return XOR_ENUMS(Enum, a, b); }

template<typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
bool operator|(Enum a, Enum b) { return OR_ENUMS(Enum, a, b); }

template<typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
Enum& operator&=(Enum& a, Enum b) { return a = SIZE_AS_ENUM(Enum, AND_ENUMS(Enum, a, b)); }

template<typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
Enum& operator^=(Enum& a, Enum b) { return a = SIZE_AS_ENUM(Enum, XOR_ENUMS(Enum, a, b)); }

template<typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
Enum& operator|=(Enum& a, Enum b) { return a = SIZE_AS_ENUM(Enum, OR_ENUMS(Enum, a, b)); }
