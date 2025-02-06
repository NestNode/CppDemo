# Build

## 通用部分

该软件跨平台，可编译成多个版本

通用的C++项目编译流程，见我个人官网文档库中的 《How to build cpp》 笔记

这里仅补充额外注意要项

## 其他依赖

该项目使用 vcpkg 的 清单模式 (manifest模式) 进行依赖管理。你需要安装 vcpkg，然后执行:

```shell
vcpkg install
```

## 旧，废弃

### cpp-httplib

https://github.com/LincZero/cpp-httplib fork https://github.com/yhirose/cpp-httplib

这里无需git clone，该库为纯头文件库，只要用到一个文件，下载就好 (Linux和Windows都能使用wget或curl)。以下命令四选一：

- Linux
  - `mkdir lib && wget -O ./lib/httplib.h https://raw.githubusercontent.com/LincZero/cpp-httplib/master/benchmark/cpp-httplib-base/httplib.h`
  - `mkdir lib && curl -o ./lib/httplib.h https://raw.githubusercontent.com/LincZero/cpp-httplib/master/benchmark/cpp-httplib-base/httplib.h`
- Windows
  - `mkdir lib && wget -O ./lib/httplib.h https://raw.githubusercontent.com/LincZero/cpp-httplib/master/benchmark/cpp-httplib-base/httplib.h`
  - `mkdir lib && curl -o ./lib/httplib.h https://raw.githubusercontent.com/LincZero/cpp-httplib/master/benchmark/cpp-httplib-base/httplib.h`
