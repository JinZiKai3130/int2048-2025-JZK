cmake_minimum_required(VERSION 3.10)
project(Int2048Project)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译器警告
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# 包含头文件目录
include_directories(src/include)

# 创建int2048静态库
add_library(int2048 STATIC src/int2048.cpp)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 首先检查目录结构
message(STATUS "当前源目录: ${CMAKE_SOURCE_DIR}")
message(STATUS "检查 data/Integer1 目录...")

# 使用更可靠的方法查找文件
file(GLOB INTEGER1_FILES "data/Integer1/*.cpp")
file(GLOB INTEGER2_FILES "data/Integer2/*.cpp")

message(STATUS "找到的 Integer1 文件: ${INTEGER1_FILES}")
message(STATUS "找到的 Integer2 文件: ${INTEGER2_FILES}")

# 编译找到的所有 Integer1 文件
foreach(source_file ${INTEGER1_FILES})
    get_filename_component(file_name ${source_file} NAME_WE)
    set(target_name "Integer1_${file_name}")
    add_executable(${target_name} ${source_file})
    target_link_libraries(${target_name} int2048)
    message(STATUS "添加目标: ${target_name} <- ${source_file}")
endforeach()

# 编译找到的所有 Integer2 文件
foreach(source_file ${INTEGER2_FILES})
    get_filename_component(file_name ${source_file} NAME_WE)
    set(target_name "Integer2_${file_name}")
    add_executable(${target_name} ${source_file})
    target_link_libraries(${target_name} int2048)
    message(STATUS "添加目标: ${target_name} <- ${source_file}")
endforeach()

# 创建快捷目标
add_custom_target(all_programs)

# 显示总结信息
message(STATUS "")
message(STATUS "=== 项目配置总结 ===")
message(STATUS "Integer1 程序数量: ${INTEGER1_FILES_COUNT}")
message(STATUS "Integer2 程序数量: ${INTEGER2_FILES_COUNT}")
message(STATUS "输出目录: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "====================")