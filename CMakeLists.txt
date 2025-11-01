cmake_minimum_required(VERSION 3.10)
project(BigIntProject)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含目录
include_directories(src/include)

# 创建int2048静态库
add_library(int2048 STATIC src/int2048.cpp)

# 手动添加Integer1目录中的目标
add_executable(Integer1_program1 data/Integer1/1.cpp)
target_link_libraries(Integer1_program1 int2048)

add_executable(Integer1_program2 data/Integer1/2.cpp) 
target_link_libraries(Integer1_program2 int2048)

# 手动添加Integer2目录中的目标
add_executable(Integer2_program1 data/Integer2/1.cpp)
target_link_libraries(Integer2_program1 int2048)

add_executable(Integer2_program2 data/Integer2/2.cpp)
target_link_libraries(Integer2_program2 int2048)

# 设置输出目录
set_target_properties(
    Integer1_program1 Integer1_program2 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Integer1
)

set_target_properties(
    Integer2_program1 Integer2_program2
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Integer2
)