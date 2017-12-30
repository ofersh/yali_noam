cmake_minimum_required (VERSION 2.6)
project (cpp_hw2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-std=c++0x -ggdb -Wall -pedantic-errors")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(ship_sim ./Elements/Civil_ship.cpp
./Elements/Cruise_Ship.cpp
./Elements/Cruiser.cpp
./Elements/Freighter.cpp
./Elements/MarineElement.cpp
./Elements/Port.cpp
./Elements/SevenSeas.cpp
./Elements/Ship.cpp
./Elements/Shipyard.cpp
./Main.cpp
./MVC/Controller.cpp
./MVC/Model.cpp
./MVC/View.cpp
./Utilities/BadInputException.cpp
./Utilities/CommandFactory.cpp
./Utilities/CommandInfo.cpp
./Utilities/Geometry.cpp
./Utilities/Scouter.cpp)

