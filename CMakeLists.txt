cmake_minimum_required(VERSION 4.1)
project(RV2)

set(CMAKE_CXX_STANDARD 20)

add_executable(RV2 main.cpp
        NGramAnalyzer.h
        ModelBuilder.h
        Model.h
        Util.h)
