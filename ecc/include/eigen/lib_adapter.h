#ifndef ___ECS_LIB_ADAPTER___
#define ___ECS_LIB_ADAPTER___

#if defined(__unix__) || defined(__linux__)
#include "linuxlib.hpp"
#elif defined(__APPLE__)
#include "osxlib.hpp"
#elif defined(_WIN32)
#include "winlib.hpp"
#else
#error "no lib_adapter available for given OS"
#endif

#endif // ___ECS_LIB_ADAPTER___
