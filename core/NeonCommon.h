#pragma once
#if defined(_WIN32) || defined(_WIN64)
    #define NEON_PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define NEON_PLATFORM_MAC
#elif defined(__linux__)
    #define NEON_PLATFORM_LINUX
#else
    #error "Unsupported platform"
#endif

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <filesystem>

#ifdef NEON_PLATFORM_WINDOWS
    #include <windows.h>
    #define NEON_EXPORT __declspec(dllexport)
#else
    #include <dlfcn.h>
    #define NEON_EXPORT __attribute__((visibility("default")))
#endif

#define NEON_LOG_INFO(x)   std::cout << "[INFO] " << x << std::endl
#define NEON_LOG_WARN(x)   std::cout << "[WARN] " << x << std::endl
#define NEON_LOG_ERROR(x)  std::cerr << "[ERROR] " << x << std::endl
