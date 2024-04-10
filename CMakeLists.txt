if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

cmake_minimum_required(VERSION 3.10)

project(RayTracing VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(RayTracing src/main.cpp headers/FastPrinting.h headers/STLheaders.h headers/Tracing.h headers/Tracing.cpp)