# Build

## 依赖方案 - git/curl/wget

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
# find_package(spdlog CONFIG REQUIRED)

# 修改成直接指定搜包路径
find_package(spdlog CONFIG REQUIRED PATHS "${PROJECT_SOURCE_DIR}/libs/spdlog/build/")

# 或者添加该语句 (整体添加搜包路径)
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/libs/spdlog/build/")

# 或者添加该语句 (整体设置搜包路径)
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/libs/spdlog/build/")
```

### nlohmann/json

```bash
cd libs
git clone --depth 1 https://github.com/nlohmann/json.git
cd json && mkdir build && cd build
cmake .. && cmake --build .
```

可以发现include文件夹里的是 `.hpp`，所以可以用头文件方式使用

```cmake
include_directories(${CMAKE_SOURCE_DIR}/libs/json/include/)
```
