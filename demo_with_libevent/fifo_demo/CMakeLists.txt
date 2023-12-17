cmake_minimum_required(VERSION 3.0)
project(fifo_example)

# 设置编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# 添加可执行文件 read
add_executable(read read_fifo.c)

# 添加可执行文件 write
add_executable(write write_fifo.c)

# 链接 libevent 库
find_library(LIBEVENT_LIB NAMES event)
target_link_libraries(read ${LIBEVENT_LIB})
target_link_libraries(write ${LIBEVENT_LIB})