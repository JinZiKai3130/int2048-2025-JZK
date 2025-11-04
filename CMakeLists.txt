cmake_minimum_required(VERSION 3.10)
project(Int2048Project)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(src/include)

# 创建int2048静态库
add_library(int2048 STATIC src/int2048.cpp)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 打印调试信息
message(STATUS "项目根目录: ${CMAKE_SOURCE_DIR}")
message(STATUS "正在搜索 Integer1 和 Integer2 目录...")

# 使用更可靠的文件搜索方法
file(GLOB INTEGER1_FILES RELATIVE ${CMAKE_SOURCE_DIR} "data/Integer1/*.cpp")
file(GLOB INTEGER2_FILES RELATIVE ${CMAKE_SOURCE_DIR} "data/Integer2/*.cpp")

# 打印找到的文件
message(STATUS "找到的 Integer1 文件:")
foreach(file ${INTEGER1_FILES})
    message(STATUS "  - ${file}")
endforeach()

message(STATUS "找到的 Integer2 文件:")
foreach(file ${INTEGER2_FILES})
    message(STATUS "  - ${file}")
endforeach()

# 编译 Integer1 文件
foreach(source_file ${INTEGER1_FILES})
    get_filename_component(file_name ${source_file} NAME_WE)
    set(target_name "Integer1_${file_name}")
    
    message(STATUS "添加目标: ${target_name} <- ${source_file}")
    add_executable(${target_name} ${source_file})
    target_link_libraries(${target_name} int2048)
    
    # 设置输出到对应子目录
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Integer1"
    )
endforeach()

# 编译 Integer2 文件
foreach(source_file ${INTEGER2_FILES})
    get_filename_component(file_name ${source_file} NAME_WE)
    set(target_name "Integer2_${file_name}")
    
    message(STATUS "添加目标: ${target_name} <- ${source_file}")
    add_executable(${target_name} ${source_file})
    target_link_libraries(${target_name} int2048)
    
    # 设置输出到对应子目录
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Integer2"
    )
endforeach()

# 创建目录（确保输出目录存在）
file(MAKE_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Integer1")
file(MAKE_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Integer2")

# 创建聚合目标
add_custom_target(all_integer1 DEPENDS ${INTEGER1_TARGETS})
add_custom_target(all_integer2 DEPENDS ${INTEGER2_TARGETS})
add_custom_target(all_programs DEPENDS all_integer1 all_integer2)

message(STATUS "")
message(STATUS "=== 配置完成 ===")
message(STATUS "Integer1 目标数: ${INTEGER1_COUNT}")
message(STATUS "Integer2 目标数: ${INTEGER2_COUNT}")