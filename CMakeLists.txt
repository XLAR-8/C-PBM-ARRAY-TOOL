cmake_minimum_required(VERSION 3.0)


project(tool)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(
     tool  
     2.0_TOOL.cpp  
   )
