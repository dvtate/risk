cmake_minimum_required(VERSION 3.19)
project(risk)

set(CMAKE_CXX_STANDARD 20)

add_executable(risk main.cpp territory.cpp territory.hpp globe.cpp globe.hpp map.cpp map.hpp player.cpp player.hpp)