cmake_minimum_required (VERSION 2.6)
project (cpp_hw2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-ggdb -Wall -pedantic-errors")

add_executable(main Main.cpp Delivery.cpp Date.cpp Edge.cpp Port.cpp)

