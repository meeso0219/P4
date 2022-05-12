cmake_minimum_required(VERSION 3.21)
project(P4)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++17")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
add_executable(P4 p4.cpp gridFlea.cpp gridFlea.h inFest.cpp inFest.h)

