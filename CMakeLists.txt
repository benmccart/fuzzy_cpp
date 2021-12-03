# CMakeList.txt : CMake project for fuzzy_cpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

project ("fuzzy_cpp_all")

# Add source to this project's executable.
# add_executable (fuzzy_cpp "fuzzy_cpp.cpp" "fuzzy_cpp.h")
add_subdirectory(fuzzy)
add_subdirectory(test)

# TODO: Add tests and install targets if needed.
