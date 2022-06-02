cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME lab10)
project("${PROJECT_NAME}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


include_directories("inc/")

add_executable("${PROJECT_NAME}" main.cpp inc/bmp.hpp inc/mathlib/matrix.hpp src/bmp.cpp)

file(COPY "in.bmp" DESTINATION "/")