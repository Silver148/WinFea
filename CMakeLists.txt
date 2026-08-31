cmake_minimum_required(VERSION 3.14)
project(WinFea VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)

add_library(WinFea SHARED 
    src/winfea.cpp
)

target_include_directories(WinFea 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(WinFea PRIVATE SDL3::SDL3)

add_executable(Test test/test.cpp)
target_link_libraries(Test PRIVATE WinFea)