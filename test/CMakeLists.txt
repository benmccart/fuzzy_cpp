# CMakeList.txt : CMake project for fuzzy_cpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

project ("test")

find_package(Catch2 CONFIG REQUIRED)


# Add source to this project's executable.
add_executable (test "test.cpp" "static_test.cpp")

set_property(TARGET test PROPERTY CXX_STANDARD 20)
target_link_libraries(test PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
target_link_libraries(test PRIVATE fuzzy_cpp)

include(Catch)
catch_discover_tests(test)


