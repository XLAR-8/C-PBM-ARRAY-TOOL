cmake_minimum_required(VERSION 3.0)

project(tool)
execute_process(COMMAND magick ../data1.pbm -monochrome  -threshold 25%  apertus_logo_part_1.xbm)
execute_process(COMMAND magick ../data2.pbm -monochrome  -threshold 25%  apertus_logo_part_2.xbm)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_executable(
    tool
    tool.cpp
    )
