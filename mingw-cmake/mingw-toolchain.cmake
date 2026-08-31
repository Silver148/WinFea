set(CMAKE_SYSTEM_NAME Windows)

set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)

find_program(FOUND_GCC_PATH NAMES ${TOOLCHAIN_PREFIX}-gcc)

if(NOT FOUND_GCC_PATH)
    message(FATAL_ERROR "${TOOLCHAIN_PREFIX}-gcc not found")
endif()

get_filename_component(MINGW_BIN_DIR "${FOUND_GCC_PATH}" DIRECTORY)

get_filename_component(MINGW_ROOT "${MINGW_BIN_DIR}" DIRECTORY)

set(CMAKE_C_COMPILER   ${MINGW_BIN_DIR}/${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${MINGW_BIN_DIR}/${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_RC_COMPILER  ${MINGW_BIN_DIR}/${TOOLCHAIN_PREFIX}-windres)

set(CMAKE_FIND_ROOT_PATH ${MINGW_ROOT}/${TOOLCHAIN_PREFIX})

# Allow CMake to resolve dependencies installed outside the MinGW sysroot,
# such as a local SDL3 package downloaded for Windows cross-compilation.
set(SDL3_ROOT "$ENV{SDL3_ROOT}")
if(NOT SDL3_ROOT)
    foreach(_candidate
        "${CMAKE_CURRENT_LIST_DIR}/../deps/SDL3/x86_64-w64-mingw32"
        "${CMAKE_CURRENT_LIST_DIR}/../deps/SDL3/i686-w64-mingw32"
        "${CMAKE_CURRENT_LIST_DIR}/../deps/SDL3")
        if(EXISTS "${_candidate}/include/SDL3/SDL.h")
            set(SDL3_ROOT "${_candidate}")
            break()
        endif()
    endforeach()
endif()

if(SDL3_ROOT)
    list(PREPEND CMAKE_PREFIX_PATH "${SDL3_ROOT}")
    list(PREPEND CMAKE_FIND_ROOT_PATH "${SDL3_ROOT}")
    include_directories(SYSTEM "${SDL3_ROOT}/include")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${SDL3_ROOT}/include")
endif()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)