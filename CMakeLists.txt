cmake_minimum_required(VERSION 3.16)
project(athena LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
find_package(rtlsdr REQUIRED) # WARNING
find_package(PNG REQUIRED)

pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0>=4.10)
pkg_check_modules(VOLK REQUIRED IMPORTED_TARGET volk)
pkg_check_modules(FFTW3F IMPORTED_TARGET REQUIRED fftw3f)

find_package(PNG REQUIRED)

add_library(core STATIC IMPORTED)

set_target_properties(core PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libs/decoder/libathena_decoder.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/libs/decoder/include"
)

target_link_libraries(core INTERFACE 
    PkgConfig::VOLK 
    PNG::PNG
    PkgConfig::FFTW3F
    rtlsdr
)

add_executable(run main.cpp)

target_link_libraries(run PRIVATE core)
