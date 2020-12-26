cmake_minimum_required(VERSION 2.8)  # 依赖 cmake 的最低版本
project(hello)                       # 项目名称

set(CMAKE_CXX_COMPILER "/usr/bin/g++")     # 编译器
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11   -g")  # 编译参数
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")  #产物目录

aux_source_directory(src DIR_SRCS)  # 源文件目录
include_directories("${PROJECT_SOURCE_DIR}/include")  #头文件目录

add_executable(main ${DIR_SRCS})  # 将哪些源文件 构建成 什么名字的可执行文件