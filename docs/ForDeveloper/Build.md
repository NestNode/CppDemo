# Build

## 通用部分

更多的通用的C++项目编译流程，见我个人官网文档库中的笔记: [《How to build cpp》](https://linczero.github.io/MdNote_Public/01.%20DesignAndDevelop/Develop/03.%20Tools/02.%20%E5%BC%80%E5%8F%91%E5%B1%82/Build%20Tools/How%20to%20build%20cpp/)
也可以参考工作流文件中的流程

这里仅是一些需要补充的部分 (已经一些常用操作的备注)，通用部分不再赘述

- (1) 准备环境 (IDE等)
- (2) 下载项目，并检查通用环境
- (3) 安装依赖 (多种方式)
- (4) 编译 (多种方式)

## 我的环境

- CLion 2024.1.2
- VSCode 1.96.2
- 我通常使用下面的环境三
- (环境一，CLion使用捆绑，不可用)
  - CMake、gcc、g++ 等用CLion捆绑的环境
  - MinGW 11.0 w64
  - CMake 3.28.1 (默认Ninja)
  - gdb 14.1
- (环境二，通常VSCode使用，也是环境变量)
  - CMake 3.31.2 (默认VS 2022工具链)
  - Ninja 1.12.1
  - gcc 14.2.0
  - g++ 14.2.0
  - gdb 15.2
- (环境三，msys2的ucrt64，也是环境变量)
  - ToolChain 13.0 w64
  - CMake 3.31.2
  - gdb MinGW-w64 15.2
