cmake_minimum_required(VERSION 3.10)

project(mini-redis)

# 使用C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# 生成可执行文件
add_executable(mini-redis main.cpp)