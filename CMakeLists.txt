cmake_minimum_required(VERSION 3.15...3.31)
project(gitlab-artifact-downloader VERSION 1.0.0 LANGUAGES CXX)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

# Enable compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add UTF-8 support and C++20 for MSVC
if(MSVC)
    add_compile_options(/utf-8 /std:c++20)
endif()

# Include CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find required packages
find_package(jsoncpp CONFIG REQUIRED)
find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# If you want to suppress the deprecation warnings
if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

# Add subdirectories
add_subdirectory(src)