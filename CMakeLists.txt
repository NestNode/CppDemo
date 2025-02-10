# Env
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)


# Var
set(PROJECT_NAME LincTool)
set(PROJECT_VERSION 1.0.0)
project(${PROJECT_NAME}) # VERSION ${PROJECT_VERSION}


# Project
# Project - Cpp/Bin
file(GLOB_RECURSE SRCS src/*.cpp src/*.c)
add_executable(${PROJECT_NAME} ${SRCS})
# Project - H
function(include_sub_directories_recursively root_dir) # Contains all header files under the specified file
    if (IS_DIRECTORY ${root_dir})
        message("Include dir: " ${root_dir})
        include_directories(${root_dir})
    endif ()
    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*)
    foreach (sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub})
        endif ()
    endforeach ()
endfunction()
include_sub_directories_recursively(${PROJECT_SOURCE_DIR}/src)


# Depend (b1. vcpkg)
#find_package(spdlog CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
#find_package(httplib CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE httplib::httplib)
# Depend (b2. build)
#list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/libs/spdlog/build/")
#find_package(spdlog CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
# Depend (b2. onlyHeader)
include_directories(${CMAKE_SOURCE_DIR}/libs/spdlog/include/)
include_directories(${CMAKE_SOURCE_DIR}/libs/)
# Depend (Platform)
if (WIN32)
    # (Windows, httplib需要这个)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32 ws2_32
    )
endif()


# Message
message("Compile Info")
message("    Compile Platform")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message("        Linux")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    message("        Windows")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    message("        MacOS")
else()
    message(WARNING, "        Other")
endif()
message("    Compile ToolChain")
if (MINGW)
    message("        MINGW")
elseif (MSVC)
    message("        MSVC")
else ()
    message(WARNING, "        Other")
endif ()
message("    Compiler Version")
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    message("        MSVC ${CMAKE_CXX_COMPILER_VERSION}")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    message("        GCC ${CMAKE_CXX_COMPILER_VERSION}")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message("        Clang ${CMAKE_CXX_COMPILER_VERSION}")
else()
    message(WARNING, "        Other ${CMAKE_CXX_COMPILER_VERSION}")
endif()
