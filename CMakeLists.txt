cmake_minimum_required(VERSION 3.21)

project(bragi LANGUAGES CXX VERSION 1.0)

if (NOT CMAKE_CXX_STANDARD )
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(includes ${CMAKE_CURRENT_SOURCE_DIR}/include)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS "-fexperimental-library")


include(cmake/PreventInSourceBuilds.cmake)
include(Dependencies.cmake)
include(Macros.cmake)

add_library(warnings INTERFACE)


include(cmake/CompilerWarnings.cmake)
set_project_warnings(
warnings
OFF
""
""
""
""
"nope"
)

include(cmake/Cache.cmake)
enable_cache()

setup_dependencies()

set(INCLUDE ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE})
set(UTILS ${INCLUDE}/utils.hpp)

#################
# PkgConfig     #
#################
find_package(PkgConfig REQUIRED)
pkg_search_module(RE2 REQUIRED re2 IMPORTED_TARGET)

#################
#  Fmt          #
#################
find_package(fmt 10 REQUIRED )



add_subdirectory(D1)
add_subdirectory(D2)
add_subdirectory(D3)
