cmake_minimum_required(VERSION 3.14)

project(D2 LANGUAGES CXX VERSION 1.0)

add_executable(cube cube.cpp)

target_link_libraries(cube PRIVATE PkgConfig::RE2 fmt::fmt)
