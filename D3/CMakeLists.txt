cmake_minimum_required(VERSION 3.14)

project(D3 LANGUAGES CXX VERSION 1.0)

add_executable(gear gear.cpp)

target_link_libraries(gear PRIVATE PkgConfig::RE2 fmt::fmt)
