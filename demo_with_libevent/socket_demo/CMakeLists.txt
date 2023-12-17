cmake_minimum_required(VERSION 3.0)
project(MyProject)

set(CMAKE_C_STANDARD 11)

# 添加 server 可执行文件的编译规则
add_executable(server server.c)
target_link_libraries(server event)

# 添加 client 可执行文件的编译规则
add_executable(client client.c)
target_link_libraries(client event)