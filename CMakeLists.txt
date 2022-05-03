cmake_minimum_required(VERSION 3.21)
project(Hospital)

set(CMAKE_CXX_STANDARD 14)

add_executable(Hospital main.cpp Patient.cpp User.cpp Compare.cpp maps.cpp)
