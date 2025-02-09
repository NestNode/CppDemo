# Build

## 通用部分

更多的通用的C++项目编译流程，见我个人官网文档库中的 《How to build cpp》 笔记

这里仅是一些需要补充的部分 (已经一些常用操作的备注)，通用部分不再赘述

## (二选一) 依赖方案 - vcpkg

vs建议用vcpkg方案，clion兼容似乎没那么好 (应该要25版本及以后才支持好些)，用传统的

### 安装依赖

项目创建于 https://github.com/LincDemo/CMakeVcpkgTemplate 模板，编译方法也可以去看该仓库

### 兼容问题

VS工具链和生成器对vcpkg兼容要更好，纯终端也行。在CLion上似乎兼容不太好

否则使用MinGW工具链应该会报错 `error: building spdlog:x64-windows failed with: BUILD_FAILED`
vcpkg install的操作应修改为：`./vcpkg/vcpkg install --triplet x64-mingw-dynamic --host-triplet x64-mingw-dynamic`

## (二选一) 依赖方案 - git

但如果你依赖包使用过程中，由于IDE或编译链工具版本过旧或不匹配导致失败，则可以尝试使用这里的方案

### cpp-httplib

https://github.com/LincZero/cpp-httplib fork https://github.com/yhirose/cpp-httplib

(1) 纯头文件版本

这里无需git clone，该库为纯头文件库，只要用到一个文件，下载就好 (Linux和Windows都能使用wget或curl)。以下命令四选一：

- Linux
  - `mkdir libs && wget -O ./libs/httplib.h https://raw.githubusercontent.com/LincZero/cpp-httplib/master/benchmark/cpp-httplib-base/httplib.h`
  - `mkdir libs && curl -o ./libs/httplib.h https://raw.githubusercontent.com/LincZero/cpp-httplib/master/benchmark/cpp-httplib-base/httplib.h`
- Windows
  - `mkdir libs; wget -O ./libs/httplib.h https://raw.githubusercontent.com/LincZero/cpp-httplib/master/benchmark/cpp-httplib-base/httplib.h`
  - `mkdir libs; curl -o ./libs/httplib.h https://raw.githubusercontent.com/LincZero/cpp-httplib/master/benchmark/cpp-httplib-base/httplib.h`

CMakeList.txt

```js
include_directories(${CMAKE_SOURCE_DIR}/libs)
```

(2) clone版本 (废弃)

这个就需要clone整个库了，他那个 `FindBrotli.cmake` 和 `httplibConfig.cmake.in` 文件在repo/cmake文件夹里

Linux

```bash
cd libs
git clone --depth 1 https://github.com/yhirose/cpp-httplib.git
```

CMakeList.txt

```cmake
find_package(httplib CONFIG REQUIRED PATHS "${PROJECT_SOURCE_DIR}/libs/cpp-httplib/")
target_link_libraries(${PROJECT_NAME} PRIVATE httplib::httplib)
```

### spdlog

https://github.com/gabime/spdlog

(1) Linux

```bash
cd libs
git clone --depth 1 https://github.com/gabime/spdlog.git
cd spdlog && mkdir build && cd build
cmake .. && cmake --build .
```

(2) Windows

```bash
cd libs
git clone --depth 1 https://github.com/gabime/spdlog.git
cd spdlog; mkdir build; cd build
cmake ..; cmake --build .
```

(3) 然后搜包路径改一下

```cmake
# 这个是原来用vcpkg的写法
find_package(spdlog CONFIG REQUIRED)

# 修改成直接指定搜包路径
find_package(spdlog CONFIG REQUIRED PATHS "${PROJECT_SOURCE_DIR}/libs/spdlog/build/")

# 或者添加该语句 (整体添加搜包路径)
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/libs/spdlog/build/")

# 或者添加该语句 (整体设置搜包路径)
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/libs/spdlog/build/")
```

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
