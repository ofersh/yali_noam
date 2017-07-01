cmake_minimum_required (VERSION 2.6)
project (cpp_hw2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-ggdb -Wall -pedantic-errors")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(boggieLever Main.cpp Delivery.cpp Date.cpp Edge.cpp EdgeCargo.cpp EdgeTime.cpp Port.cpp Clerk.cpp BoogieLever.cpp )

