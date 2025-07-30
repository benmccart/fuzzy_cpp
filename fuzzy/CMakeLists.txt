# CMakeList.txt : CMake project for fuzzy_cpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

project ("fuzzy_cpp")

add_library(fuzzy_cpp INTERFACE)
set_property(TARGET fuzzy_cpp PROPERTY CXX_STANDARD 20)
target_include_directories(fuzzy_cpp INTERFACE include/)

set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})


