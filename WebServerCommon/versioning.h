/*
Copyright 2018 Jesse Laning
*/

#pragma once

#include <cstdint>
#include <string>

#define MAKE_VER_NUM(major, minor, patch) (major << 16) | (minor << 8) | (patch)

#define MAKE_VER_CSTR(major, minor, patch) #major "." #minor "." #patch

#define DECL_VERSION(prefix, major, minor, patch)                          \
  constexpr uint16_t prefix##_MAJOR = major;                               \
  constexpr uint8_t prefix##_MINOR = minor;                                \
  constexpr uint8_t prefix##_PATCH = patch;                                \
  constexpr uint32_t prefix##_VER_NUM = MAKE_VER_NUM(major, minor, patch); \
  constexpr const char* prefix##_VER_CSTR =                                \
      MAKE_VER_CSTR(major, minor, patch);                                  \
  static const std::string prefix##_VER_STR =                              \
      MAKE_VER_CSTR(major, minor, patch);
