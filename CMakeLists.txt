cmake_minimum_required(VERSION 3.20)
project(NeonPlatform LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \/bin/\$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY \/bin/\$<CONFIG>/plugins)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY \/bin/\$<CONFIG>/lib)

add_subdirectory(interfaces)
add_subdirectory(core)
add_subdirectory(plugins)
add_subdirectory(apps)

set_property(DIRECTORY \ PROPERTY VS_STARTUP_PROJECT AppExample)
