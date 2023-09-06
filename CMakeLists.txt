cmake_minimum_required(VERSION 3.10)
project(nocp LANGUAGES CXX)

# MinGW can work too, but it's a crap
# setting these explicitly so that gha works easily
set(CMAKE_SYSTEM_NAME Windows)
set(TOOLCHAIN_PREFIX x86)
set(CMAKE_C_COMPILER cl)
set(CMAKE_CXX_COMPILER cl)
set(CMAKE_GENERATOR_PLATFORM Win32)
set(CMAKE_GENERATOR_TOOLSET "host=x86")
set(CMAKE_VS_PLATFORM_NAME "x86")

set(CMAKE_SHARED_LIBRARY_PREFIX "")
add_library(${PROJECT_NAME} SHARED main.cpp)
