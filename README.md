## Myftp介绍
    Myftp是一个基于libevent的FTP服务端和基于QT的客户端

## 1. 项目目录说明
`ftpSrv/` #  项目头文件和源码<br>
`libevent-2.1.12-stable/`   # 本项目中使用到的三方库<br>
`demo_with_libevent/`   # 完整测试目录<br>

## 2. 使用Modern CMake对Myftp进行编译，安装
- `cmake -S . -B build`<br>
- `cmake --build build --parallel 16`<br>

## 3. 运行
> 待补充

## 4. 调试方法
> 待补充

## 5. 运行环境基线
- 主机操作系统：Windows 11 家庭中文版 22621.1105
- 虚拟机：WSL 2
- 虚拟机操作系统版本：Ubuntu 22.04.1 LTS
- Linux内核版本：Linux version 5.15.79.1-microsoft-standard-WSL2
- gcc/g++版本：11.3.0
- clang/clang++版本：17.0.0
- CMake版本：3.22.1