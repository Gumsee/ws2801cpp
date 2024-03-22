cmake_minimum_required (VERSION 3.0...3.9)
project(ws2801cpp)
cmake_policy(SET CMP0072 NEW)
cmake_policy(SET CMP0090 NEW)
set(CMAKE_EXPORT_PACKAGE_REGISTRY TRUE)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

option(BUILD_EXAMPLES "Should the exampleprojects be build" ON)

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)
set (INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE}/bin/")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g3 -Wall -fdiagnostics-color=always")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wno-unused-parameter -Wno-reorder -Wno-pedantic")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fPIC") #-Og

set(CMAKE_INSTALL_FULL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR})
set(CMAKE_INSTALL_FULL_LIBDIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

message(STATUS "${PROJECT_NAME}: CXXFLAGS: ${CMAKE_CXX_FLAGS}")


add_subdirectory(src)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
