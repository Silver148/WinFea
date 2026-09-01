cmake_minimum_required(VERSION 3.14)
project(WinFea VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)


add_library(WinFea SHARED 
    src/winfea.cpp
    src/winfea_images.cpp
)

set_target_properties(WinFea PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON) # DLL for Windows

target_include_directories(WinFea 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(WinFea PUBLIC
    SDL3::SDL3
    SDL3_image::SDL3_image
)

add_executable(Test test/test.cpp)
target_link_libraries(Test PRIVATE WinFea)