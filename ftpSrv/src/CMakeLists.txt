# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)

# 添加同级 include 目录为包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(CCMODE PROGRAM)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall ${MACRO}")
set(INCLUDES -I/opt/libevent/include/)
set(TARGET ftpSrv)
file(GLOB SRCS *.cpp)
set(LIBS -L/opt/libevent/lib/ -levent -lpthread)

if(CCMODE STREQUAL "PROGRAM")
    add_executable(${TARGET} ${SRCS})
    target_include_directories(${TARGET} PRIVATE ${INCLUDES})
    target_link_libraries(${TARGET} PRIVATE ${LIBS})
endif() 