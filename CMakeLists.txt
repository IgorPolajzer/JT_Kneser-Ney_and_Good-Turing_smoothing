cmake_minimum_required(VERSION 4.1)
project(RV2)

set(CMAKE_CXX_STANDARD 20)

add_executable(RV2 main.cpp
        headers/NGramAnalyzer.h
        headers/ModelBuilder.h
        headers/Model.h
        headers/Util.h
        headers/Predictor.h
        headers/NGram.h
)
