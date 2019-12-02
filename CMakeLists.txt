cmake_minimum_required(VERSION 3.15)
project(assignment2)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++14")

add_executable(assignment2 main.cpp City.cpp City.hpp Tour.cpp Tour.hpp GeneticAlgorithm.cpp GeneticAlgorithm.hpp)