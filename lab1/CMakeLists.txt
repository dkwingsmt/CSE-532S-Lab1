cmake_minimum_required(VERSION 2.8)
project(lab1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    common/common.cpp
    common/common.h
    configs/empty-but-one.txt
    configs/empty-play.txt
    configs/hamlet-34.txt
    configs/hamlet_act_ii_scene_2.txt
    lab1/main.cpp
    lab1/Play.cpp
    lab1/Play.h
    lab1/Player.cpp
    lab1/Player.h
    )

add_executable(lab1 ${SOURCE_FILES} lab1/Player.cpp lab1/Player.h)
