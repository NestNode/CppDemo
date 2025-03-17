# Build

## (二选一) 依赖方案 - vcpkg

vs建议用vcpkg方案，clion兼容似乎没那么好 (应该要25版本及以后才支持好些)，用传统的

### 安装依赖

项目创建于 https://github.com/LincDemo/CMakeVcpkgTemplate 模板，编译方法也可以去看该仓库

### 兼容问题

VS工具链和生成器对vcpkg兼容要更好，纯终端也行。在CLion上似乎兼容不太好

否则使用MinGW工具链应该会报错 `error: building spdlog:x64-windows failed with: BUILD_FAILED`
vcpkg install的操作应修改为：`./vcpkg/vcpkg install --triplet x64-mingw-dynamic --host-triplet x64-mingw-dynamic`
