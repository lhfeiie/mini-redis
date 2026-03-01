cmake_minimum_required(VERSION 3.10)

project(mini-redis)

# 使用C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# 添加调试信息（-g 选项）
set(CMAKE_BUILD_TYPE Debug)

# 包含 src 目录下的所有 .cpp 文件
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 生成可执行文件
add_executable(mini-redis ${SOURCES})

# 把src/ 加入头文件搜索路径，之后 #include 可以用相对路径
target_include_directories(mini-redis PRIVATE src)