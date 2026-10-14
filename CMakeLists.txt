cmake_minimum_required(VERSION 3.10)
project(PenugasanModul2 CXX)

set(CMAKE_CXX_STANDARD 17)

# Mengarahkan include ke folder rapidjson
include_directories(rapidjson/include)

add_executable(PenugasanModul2
    src/main.cpp
)