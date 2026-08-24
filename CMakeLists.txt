cmake_minimum_required(VERSION 3.16)
project(athena LANGUAGES CXX C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(VOLK REQUIRED volk)
find_package(PNG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/decoder/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/decoder)
link_libraries(athena_core volk PNG::PNG)

add_executable(run main.cpp)
